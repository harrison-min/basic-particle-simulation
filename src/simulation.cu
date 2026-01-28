#include "simulation.hpp"
#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/execution_policy.h>
#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>

Simulation::Simulation (Renderer & newRend, GravityField & newGrav) :
    renderer{newRend}, gravity {newGrav} {

}


void Simulation::updateParticles(float timeInterval) {
    renderer.resetPixelMap();
    int numberOfParticles = particles.size();    

    ParticlePositionUpdater pos;

    pos.timeInterval = timeInterval;
    pos.particles = thrust::raw_pointer_cast(particles.data());
    thrust::for_each(thrust::device, thrust::make_counting_iterator(0), thrust::make_counting_iterator(numberOfParticles), pos);
 
    ParticleVelocityUpdater vel;        
    
    vel.timeInterval = timeInterval;
    vel.particles = thrust::raw_pointer_cast(particles.data());
    vel.accelX = thrust::raw_pointer_cast(gravity.accelerationFieldXcomponent.data());
    vel.accelY = thrust::raw_pointer_cast(gravity.accelerationFieldYcomponent.data());
    vel.totalWidth = gravity.totalWidth;
    vel.totalHeight = gravity.totalHeight; 
    thrust::for_each(thrust::device, thrust::make_counting_iterator(0), thrust::make_counting_iterator(numberOfParticles), vel);
    
    thrust::host_vector<Particle> temp = particles;
    for (Particle par: temp) {
        renderer.setPixel(static_cast<int>(par.positionX), static_cast<int>(par.positionY), 0xFFFFFFFF);
    }
}
void Simulation::addParticle (float posX, float posY, float velX, float velY) {
    Particle newParticle {posX, posY, velX, velY, 1};
    particles.push_back(newParticle);
    renderer.setPixel(static_cast<int>(posX), static_cast<int>(posY), 0xFFFFFFFF);
}

void Simulation::runSimulation(float timeInterval, int intervals) {
    gravity.computeVectorField();
    for (int i = 1; i <= intervals; ++i) {
        std::cerr << "\r\033[2KRunning Iteration " << i ;
        renderer.drawFrame();
        updateParticles(timeInterval);
    }
    std::cerr<< "\n";
}