#pragma once
#include <vector>
#include <thrust/device_vector.h>

class GravityWell {
    public:
        int positionX;
        int positionY;
        float mass;
        GravityWell (int x, int y, float givenMass);

};

class GravityField {
    public:
        GravityField(int width, int height);
        void addGravityWell(int x, int y, float mass); 
        void computeVectorField();
        void testGPU();
        thrust::device_vector<float> accelerationFieldXcomponent; 
        thrust::device_vector<float> accelerationFieldYcomponent;    
        int totalWidth;
        int totalHeight;
    private:
        thrust::device_vector<GravityWell> wells; 
};


struct GravityVectorFieldFunctor  {
    int width;
    float * accelX;
    float * accelY;
    GravityWell * gravWells;
    int numberOfWells;

    __device__ void operator () (int index) {
        int x = index % width;
        int y = index / width;
        float xComponent = 0;
        float yComponent = 0;
        float minimumDistance = 1.0f;

        for (int i = 0; i < numberOfWells; ++ i) {
            float horizontalDistance = gravWells[i].positionX - x;
            float verticalDistance = gravWells[i].positionY - y;

            float distanceSquared = horizontalDistance * horizontalDistance + verticalDistance * verticalDistance + minimumDistance;
            float distance = sqrtf(distanceSquared);

            float G = 6.67e-11f;
            float gravitationalAccelerationScalar = G * gravWells[i].mass / (distanceSquared);

            xComponent += gravitationalAccelerationScalar * (horizontalDistance/distance);
            yComponent += gravitationalAccelerationScalar * (verticalDistance/distance);


        }

        accelX [index] = xComponent;
        accelY [index] = yComponent;

    }

};