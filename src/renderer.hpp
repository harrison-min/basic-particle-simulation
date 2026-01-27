#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>

class Renderer {

    public:
        Renderer(int width, int height, int scale);
        void drawFrame();
        void setPixel(int x, int y, uint32_t color);
        void deletePixel(int x, int y);

    private:
        size_t frameNumber;
        std::string fileName;
        std::string frameDirectory;
        int widthRatio;  
        int heightRatio;
        int videoScale; 
        std::vector<uint32_t> pixelMap;
        void resetPixelMap();

};


