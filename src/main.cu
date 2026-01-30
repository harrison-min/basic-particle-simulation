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

    Simulation mySim (myRender, myGravity);

    myGravity.addGravityWell(rand()%(widthRatio * videoScale) , rand()%(heightRatio * videoScale), pow(10, 15) );
    myGravity.addGravityWell(rand()%(widthRatio * videoScale) , rand()%(heightRatio * videoScale), pow(10, 15) );
    for (int i = 5; i < videoScale*3-5; i ++) {
        for (int j = 5; j < videoScale*3-5; j ++) {
            mySim.addParticle(i*widthRatio/3, j * heightRatio/3, .05f *(rand()%20-10), .05f *(rand()%20-10));
        }
    }


    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    mySim.runSimulation(.1, 500);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cerr << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    std::cerr << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
}