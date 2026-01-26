#include <iostream>
#include <fstream>
#include <string>

int main () {
    std::string filename = "example.ppm";

    std::fstream file;
    file.open(filename, std::ios::out | std::ios::binary);
    
    int width = 16 * 60;
    int height = 9 * 60;

    file << "P6\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; ++ y) {
        for (int x = 0; x < width; ++ x) {
            file.put(0xFF);
            file.put(0x00);
            file.put(0x00);

        }
    }

    file.close();

}