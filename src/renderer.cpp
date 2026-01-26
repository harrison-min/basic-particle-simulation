#include "renderer.hpp"
#include <fstream>
#include <format>

renderer::renderer() {
    fileName = "test";
    frameDirectory = "frames/";
    frameNumber = 0;
    widthRatio = 16;
    heightRatio = 9;
    videoScale = 100;

}


void renderer::drawFrame () {
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
            if ( ((x+frameNumber)/videoScale + (y+frameNumber)/videoScale) % 2 ) {
                file.put (0xFF);
                file.put (0x00);
                file.put (0x00);
            } else {
                file.put (0x00);
                file.put (0x00);
                file.put (0xFF);
            } 
        }
    }

    file.close();
    frameNumber ++;
}