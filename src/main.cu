#include "simulation.hpp"
#include <chrono>
#include <iostream>
#include <cmath>
int main () {
    int widthRatio = 16;
    int heightRatio = 9;
    int videoScale = 100;

    Renderer myRender(widthRatio, heightRatio, videoScale);
    GravityField myGravity(widthRatio * videoScale, heightRatio * videoScale);
    myGravity.testGPU();

    Simulation mySim (myRender, myGravity);

    myGravity.addGravityWell(800, 450, pow(10, 15) );
    myGravity.addGravityWell(1000, 600, pow(10, 15) );
    for (int i = 0; i < videoScale; i ++) {
        for (int j = 0; j < videoScale; j ++) {
            mySim.addParticle(i*widthRatio, j * heightRatio, rand()%2-1, rand()%2-1);
        }
    }


    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    mySim.runSimulation(.1, 500);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cerr << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    std::cerr << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
}