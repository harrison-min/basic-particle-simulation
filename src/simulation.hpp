#pragma once
#include "particle.hpp"
#include <vector>
#include "renderer.hpp"
#include "gravity.hpp"

class Simulation {
    public:
        Simulation(Renderer& newRend, GravityField& newGrav);
        void addParticle (float posX, float posY, float velX, float velY);
        void runSimulation(float timeInterval, int intervals);  
    private:
        std::vector<Particle> particles;
        Renderer & renderer;
        void updateParticles(float timeInterval);
        GravityField& gravity;
};