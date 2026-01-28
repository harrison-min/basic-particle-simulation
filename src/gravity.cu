#include "gravity.hpp"
#include <cmath>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/execution_policy.h>

GravityField::GravityField(int width, int height) {
    totalWidth = width;
    totalHeight = height;
    accelerationFieldXcomponent.resize(width * height);
    accelerationFieldYcomponent.resize(width * height);

}


void GravityField::testGPU () {

    thrust::host_vector<int> cpuTestVector;
    cpuTestVector.resize(100);
    for (int i = 0; i < 100; i ++) {
        cpuTestVector[i] = i;
    }
    thrust::device_vector<int> gpuTestVector = cpuTestVector;

    thrust::for_each (thrust::device, gpuTestVector.begin(), gpuTestVector.end(), 
        [] __device__ (int val) {std::printf("Hello from gpu at index: %d\n", val); });

    cudaDeviceSynchronize();
}

void GravityField::addGravityWell(int x, int y, float mass) {
    wells.emplace_back(x, y, mass);
}

void GravityField::computeVectorField() {
    for (int y = 0; y < totalHeight; ++y) {
        for (int x = 0; x < totalWidth; ++x) {
            int index = x + y * totalWidth;
            double xComponent = 0;
            double yComponent = 0;
            
            for (GravityWell g: wells) {
                double minimumDistance = 10; //To prevent 0 distance
                double horizontalDistance =  g.positionX - x;
                double verticalDistance = g.positionY - y;
                double distanceSquared = horizontalDistance * horizontalDistance + verticalDistance * verticalDistance + minimumDistance;
                double distance = std::sqrt(distanceSquared);
                double G = 6.67/ 100000000000; //writing constant for compilier optimization

                double gravitationalAccelerationScalar = G * g.mass / (distanceSquared);

                xComponent += gravitationalAccelerationScalar * (horizontalDistance/distance);
                yComponent += gravitationalAccelerationScalar * (verticalDistance/distance);
            }

            accelerationFieldXcomponent[index] = xComponent;
            accelerationFieldYcomponent[index] = yComponent;

        }
    }
}


GravityWell::GravityWell (int x, int y, float givenMass):
    positionX {x}, positionY {y}, mass {givenMass} {
    
}
