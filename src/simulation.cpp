#include "simulation.hpp"
#include <iostream>

Simulation::Simulation (Renderer & newRend) :
    renderer{newRend} {


}


void Simulation::updateParticles(float timeInterval) {

    for (Particle& par : particles) {
        renderer.deletePixel(static_cast<int>(par.positionX), static_cast<int>(par.positionY));
        par.updatePosition(timeInterval);
        renderer.setPixel (static_cast<int>(par.positionX), static_cast<int>(par.positionY), 0xFFFFFFFF);

    }

}
void Simulation::addParticle (float posX, float posY, float velX, float velY) {
    particles.emplace_back(posX, posY, velX, velY);
    renderer.setPixel(static_cast<int>(posX), static_cast<int>(posY), 0xFFFFFFFF);
}

void Simulation::runSimulation(float timeInterval, int intervals) {
    for (int i = 0; i < intervals; ++i) {
        std::cerr << "\r\033[2KRunning Iteration " << i ;
        renderer.drawFrame();
        updateParticles(timeInterval);
    }
    std::cerr<< "\n";
}