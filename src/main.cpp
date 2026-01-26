#include "renderer.hpp"

int main () {
    renderer myRender;
    for (size_t i = 0; i < 60; i ++) {
        for (size_t i = 0; i < 20; i ++) {
            int x = rand()%1600;
            int y = rand()%900;
            int color = rand()%UINT32_MAX;
            myRender.setPixel (x, y, color);
        }
        
        myRender.drawFrame();

    }
}