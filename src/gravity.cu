#include "gravity.hpp"
#include <cmath>
#include <thrust/host_vector.h>
#include <thrust/execution_policy.h>
#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>


GravityField::GravityField(int width, int height, int depth) {
    totalWidth = width;
    totalHeight = height;
    totalDepth = depth;
}


void GravityField::addGravityWell(float x, float y, float z, float mass) {
    GravityWell newWell {x, y, z, mass};
    wells.push_back(newWell);
}

GravityWell::GravityWell (float x, float y, float z, float givenMass):
    positionX {x}, positionY {y}, positionZ {z}, mass {givenMass} {
}

