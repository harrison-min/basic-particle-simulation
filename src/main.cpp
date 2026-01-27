#include "simulation.hpp"
#include <chrono>
#include <iostream>

int main () {
    Renderer myRender;
    Simulation mySim (myRender);

    for (size_t i = 0; i < 50; ++ i) {
        mySim.addParticle(rand()%1600, rand()%900, rand()%20 - 10, rand()%20 - 10);
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    mySim.runSimulation(.1, 500);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cerr << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    std::cerr << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
}