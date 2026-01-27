#include "renderer.hpp"
#include <fstream>
#include <format>
Renderer::Renderer() {
    fileName = "test";
    frameDirectory = "frames/";
    frameNumber = 0;
    widthRatio = 16;
    heightRatio = 9;
    videoScale = 100;
    pixelMap.resize(widthRatio * videoScale);
    for (size_t i = 0; i < pixelMap.size(); i ++) {
        pixelMap[i].resize(heightRatio * videoScale);
    }
}

void Renderer::setPixel(int width, int height, uint32_t color) {
    if (width >= widthRatio * videoScale || height >= heightRatio * videoScale ||
        width < 0 || height < 0) {
        return;
    }
    pixelMap [width] [height] = color;
}

void Renderer::deletePixel (int x, int y) {
    if (x >= widthRatio * videoScale || y >= heightRatio * videoScale ||
        x < 0 || y < 0) {
        return;
    }


    pixelMap [x] [y] = 0;
}

void Renderer::resetPixelMap () {
    for (size_t i = 0; i < widthRatio * videoScale; ++ i) {
        for (size_t j = 0; j < heightRatio * videoScale; ++j) {
            pixelMap [i] [j] = 0;
        }
    }
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
            if (pixelMap [x] [y]) {
                uint32_t colorData = pixelMap[x] [y];
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