#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>

class renderer {

    public:
        renderer();
        void drawFrame();
        void setPixel(int width, int height, uint32_t color);
        void deletePixel(int x, int y);

    private:
        size_t frameNumber;
        std::string fileName;
        std::string frameDirectory;
        int widthRatio;  
        int heightRatio;
        int videoScale; 
        std::vector<std::vector<uint32_t>> pixelMap;

};

