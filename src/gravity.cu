#include "gravity.hpp"
#include <cmath>
#include <thrust/host_vector.h>
#include <thrust/execution_policy.h>
#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>


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
    GravityWell newWell {x, y, mass};
    wells.push_back(newWell);
}

void GravityField::computeVectorField() {
    GravityVectorFieldFunctor func;
    func.width = totalWidth;
    func.accelX = thrust::raw_pointer_cast(accelerationFieldXcomponent.data()) ;
    func.accelY = thrust::raw_pointer_cast(accelerationFieldYcomponent.data()) ;
    func.gravWells = thrust::raw_pointer_cast(wells.data());
    func.numberOfWells = wells.size();

    int totalCalculations = totalWidth * totalHeight;
    thrust::for_each(thrust::device, thrust::make_counting_iterator(0), thrust::make_counting_iterator(totalCalculations), func);

}


GravityWell::GravityWell (int x, int y, float givenMass):
    positionX {x}, positionY {y}, mass {givenMass} {
}

