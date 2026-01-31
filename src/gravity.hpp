#pragma once
#include <vector>
#include <thrust/device_vector.h>

class GravityWell {
    public:
        float positionX;
        float positionY;
        float positionZ;
        float mass;
        GravityWell (float x, float y, float z, float givenMass);

};

class GravityField {
    public:
        GravityField(int width, int height, int depth);
        void addGravityWell(float x, float y, float z, float mass); 
        int totalWidth;
        int totalHeight;
        int totalDepth;
        thrust::device_vector<GravityWell> wells; 
};

