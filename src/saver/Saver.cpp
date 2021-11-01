#include "Saver.hpp"

Saver::Saver(){}

Saver::~Saver(){}

void Saver::saveToBMP(int height, int width, std::vector<std::vector<Pixel>> pixels) {
    int r = rand();
    int d = 0;
    unsigned short s = 0;
    mkdir("savedPictures",0777);
    std::string file_name = "savedPictures/save_" + std::to_string(r) + ".bmp";

    std::ofstream outfile (file_name, std::ofstream::binary);

    // write header
    outfile.write("BM", 2);
    d = 26 + (width * height * 3);
    outfile.write((char*)((void*)&d), 4);
    d = 0;
    outfile.write((char*)((void*)&d), 4);
    d = 26;
    outfile.write((char*)((void*)&d), 4);

    // write dib
    d = 12;
    outfile.write((char*)((void*)&d), 4);
    s = width;
    outfile.write((char*)((void*)&s), 2);
    s = height;
    outfile.write((char*)((void*)&s), 2);
    s = 1;
    outfile.write((char*)((void*)&s), 2);
    s = 24;
    outfile.write((char*)((void*)&s), 2);

    // write data
    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            int color = rgbToInt(
                pixels[h][w].getColor().getR(), 
                pixels[h][w].getColor().getG(), 
                pixels[h][w].getColor().getB());
            outfile.write((char*)((void*)&color), 3);
        }
    }

    outfile.close();

    std::cout << "Image saved in: " << file_name << std::endl;
}