#include "simulation.hpp"
#include <iostream>

Simulation::Simulation (Renderer & newRend, GravityField & newGrav) :
    renderer{newRend}, gravity {newGrav} {

}


void Simulation::updateParticles(float timeInterval) {

    for (Particle& par : particles) {
        
        renderer.deletePixel(static_cast<int>(par.positionX), static_cast<int>(par.positionY));
        par.updateVelocity(timeInterval, gravity);
        par.updatePosition(timeInterval);
        renderer.setPixel (static_cast<int>(par.positionX), static_cast<int>(par.positionY), 0xFFFFFFFF);

    }

}
void Simulation::addParticle (float posX, float posY, float velX, float velY) {
    particles.emplace_back(posX, posY, velX, velY, 1);
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