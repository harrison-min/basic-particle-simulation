#include "renderer.hpp"
#include <fstream>
#include <format>
#include <algorithm>

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

void Renderer::drawFrame () {
    std::fstream file;

    
    std::string fullPath = std::format (
        "{}{}{:05}.ppm",
        frameDirectory,
        fileName, 
        frameNumber
    );

    file.open(fullPath , std::ios::out | std::ios::binary);
    
    int width = widthRatio * videoScale;
    int height = heightRatio * videoScale;

    file << "P6\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; ++ y) {
        for (int x = 0; x < width; ++ x) {
            if (pixelMap [x + width * y]) {
                uint32_t colorData = pixelMap[x + width * y];
                uint8_t red = (colorData >> 16) & 0xFF;
                uint8_t green = (colorData >> 8) & 0xFF;
                uint8_t blue =  (colorData) & 0xFF;

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