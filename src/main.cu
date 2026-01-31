#include "simulation.hpp"
#include <chrono>
#include <iostream>
#include <cmath>

int main () {
    int widthRatio = 16;
    int heightRatio = 9;
    int depthRatio = 10;
    int videoScale = 100;

    Renderer myRender(widthRatio, heightRatio, videoScale);
    GravityField myGravity(widthRatio * videoScale, heightRatio * videoScale, depthRatio * videoScale);

    Simulation mySim (myRender, myGravity);
    for (int i = 0; i < 20; i ++) {
        myGravity.addGravityWell(rand()%(widthRatio * videoScale), rand()%(heightRatio * videoScale), 
            rand()%(depthRatio * videoScale), pow(10, 15));
    }
    std::vector<Particle> myParticles;
    for (int i = 0; i < videoScale*3; i ++) {
        for (int j = 0; j < videoScale*3; j ++) {
            myParticles.emplace_back(i * widthRatio/3, j * heightRatio/3, 1, 0, 0, 0, 1);
        }
    }

    mySim.setParticles(myParticles);


    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    mySim.runSimulation(.1, 1000);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cerr << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    std::cerr << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
}