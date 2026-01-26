#pragma once
#include <string>


class renderer {
    public:
        renderer();
        void drawFrame();

    private:
        size_t frameNumber;
        std::string fileName;
        std::string frameDirectory;
        int widthRatio;  
        int heightRatio;
        int videoScale; 

};

