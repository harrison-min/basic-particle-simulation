#include "renderer.hpp"

int main () {
    renderer myRender;
    for (size_t i = 0; i < 60; i ++) {
        myRender.drawFrame();
    }
}