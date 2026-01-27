#pragma once
#include "particle.hpp"
#include <vector>
#include "renderer.hpp"

class Simulation {
    private:
        std::vector<Particle> particles;
        Renderer & renderer;
        void updateParticles(float timeInterval);
    public:
        Simulation(Renderer& newRend);
        void addParticle (float posX, float posY, float velX, float velY);
        void runSimulation(float timeInterval, int intervals);  
};