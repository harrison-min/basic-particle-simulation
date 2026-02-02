#include "simulation.hpp"
#include <iostream>
#include <limits>


#include <thrust/host_vector.h>
#include <thrust/execution_policy.h>
#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>

Simulation::Simulation (Renderer & newRend, GravityField & newGrav) :
    renderer{newRend}, gravity {newGrav} {
        pixelMap.resize(gravity.totalHeight * gravity.totalWidth);
        closestZDistancePixelMap.resize(gravity.totalHeight * gravity.totalWidth);
}


void Simulation::updateParticles(float timeInterval) {
    renderer.resetPixelMap();

    updateVelocity(timeInterval);
    updatePosition(timeInterval);
    updatePixelMap();   
    
}

void Simulation::updatePixelMap () {
    std::fill(closestZDistancePixelMap.begin(), closestZDistancePixelMap.end(), std::numeric_limits<float>::max());
    std::fill(pixelMap.begin(), pixelMap.end(), 0);
    thrust::host_vector<Particle> temp = particles; 


    for (const Particle& par : temp) {
        int centerX = static_cast<int>(par.positionX);
        int centerY = static_cast<int>(par.positionY);
        float currentZ = par.positionZ;
        float radius = par.radius;

        for (int dy = static_cast<int>(-radius); dy <= static_cast<int>(radius); ++dy) {
            for (int dx = static_cast<int>(-radius); dx <= static_cast<int>(radius); ++dx) {
                
                if (dx * dx + dy * dy > static_cast<int>(radius * radius)) {
                    continue;
                }

                int px = centerX - dx;
                int py = centerY -dy;

                if (px>=0 && px < gravity.totalWidth && py >= 0 && py < gravity.totalHeight) {
                    int index = py * gravity.totalWidth + px;

                    if (currentZ < closestZDistancePixelMap[index] && currentZ >= 0) {
                        closestZDistancePixelMap[index] = currentZ;

                        pixelMap[index] = par.color;
                    }
                }
            }
        }
    }


    renderer.setPixelMap(pixelMap);
}

void Simulation::updatePosition(float timeInterval) {
    int numberOfParticles = particles.size();    
    ParticlePositionUpdater pos;

    pos.timeInterval = timeInterval;
    pos.particles = thrust::raw_pointer_cast(particles.data());
    thrust::for_each(thrust::device, thrust::make_counting_iterator(0), thrust::make_counting_iterator(numberOfParticles), pos);

}

void Simulation::updateVelocity(float timeInterval) {
    int numberOfParticles = particles.size();    
    ParticleVelocityUpdater vel;        
    
    vel.timeInterval = timeInterval;
    vel.particles = thrust::raw_pointer_cast(particles.data());
    vel.wells = thrust::raw_pointer_cast(gravity.wells.data());
    vel.numberOfWells = gravity.wells.size();
    vel.totalWidth = gravity.totalWidth;
    vel.totalHeight = gravity.totalHeight; 
    vel.totalDepth = gravity.totalDepth;
    thrust::for_each(thrust::device, thrust::make_counting_iterator(0), thrust::make_counting_iterator(numberOfParticles), vel);
 
}

void Simulation::setParticles (const std::vector<Particle> & cpuParticles) {
    particles = cpuParticles; 
    updatePixelMap();
}


void Simulation::runSimulation(float timeInterval, int intervals) {
    
    for (int i = 1; i <= intervals; ++i) {
        std::cerr << "\r\033[2KRunning Iteration " << i ;
        renderer.drawFrame();
        updateParticles(timeInterval);
    }
    std::cerr<< "\n";
}