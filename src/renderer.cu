#include "renderer.hpp"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>

Renderer::Renderer(int width, int height, int scale) {
    fileName = "test";
    frameDirectory = "frames/";
    frameNumber = 0;
    widthRatio = width;
    heightRatio = height;
    videoScale = scale;
    pixelMap.resize(widthRatio * heightRatio * videoScale * videoScale);
    
}

void Renderer::setPixel(int x, int y, uint32_t color) {
    if (x >= widthRatio * videoScale || y >= heightRatio * videoScale ||
        x < 0 || y < 0) {
        return;
    }
    pixelMap [x + (videoScale * widthRatio * y)] = color;
}

void Renderer::deletePixel (int x, int y) {
    if (x >= widthRatio * videoScale || y >= heightRatio * videoScale ||
        x < 0 || y < 0) {
        return;
    }

    pixelMap [x + (widthRatio * videoScale * y)] = 0;
}

void Renderer::resetPixelMap () {
    std::fill(pixelMap.begin(), pixelMap.end(), 0);    
}

void Renderer::setPixelMap (const std::vector<uint32_t> & newMap) {
    pixelMap = newMap;
}

void Renderer::drawFrame () {
    std::fstream file;

    //using ostringstream due to std::format not being implemented by nvcc
    std::ostringstream oss;
    oss << frameDirectory << fileName << std::setw(5) << std::setfill('0') << frameNumber << ".ppm";

    std::string fullPath = oss.str();

    file.open(fullPath , std::ios::out | std::ios::binary);
    
    int width = widthRatio * videoScale;
    int height = heightRatio * videoScale;

    file << "P6\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; ++ y) {
        for (int x = 0; x < width; ++ x) {
            if (pixelMap [x + width * y]) {
                uint32_t colorData = pixelMap[x + width * y];
                uint8_t intensity = static_cast<uint8_t>((colorData>>24) & 0xFF);

                uint8_t red = static_cast<uint8_t>(static_cast<int>((colorData >> 16) & 0xFF) * intensity/255);
                uint8_t green = static_cast<uint8_t>(static_cast<int>((colorData >> 8) & 0xFF) * intensity/255);
                uint8_t blue = static_cast<uint8_t>(static_cast<int>(colorData & 0xFF) * intensity/255);

                file.put(red);
                file.put(green);
                file.put(blue);
                
            } else  {
                file.put (0x00);
                file.put (0x00);
                file.put (0x00);
            } 
        }
    }

    file.close();
    frameNumber ++;
}