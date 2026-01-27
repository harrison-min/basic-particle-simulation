#pragma once
#include <vector>


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
        std::vector<float> accelerationFieldXcomponent; 
        std::vector<float> accelerationFieldYcomponent;    
        int totalWidth;
        int totalHeight;
    private:
        std::vector<GravityWell> wells; 
};

