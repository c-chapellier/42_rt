
#include "Saver.hpp"

void Saver::toBMP(const std::string &file, const std::vector< std::vector<Vec3> > &pixels)
{
    int d, height = pixels.size(), width = pixels[0].size();
    unsigned short s;

    std::ofstream outfile(file, std::ofstream::binary);

    outfile.write("BM", 2);
    d = 26 + (width * height * 3);
    outfile.write((char *)&d, 4);
    d = 0;
    outfile.write((char*)&d, 4);
    d = 26;
    outfile.write((char*)&d, 4);

    d = 12;
    outfile.write((char*)&d, 4);
    s = width;
    outfile.write((char*)&s, 2);
    s = height;
    outfile.write((char*)&s, 2);
    s = 1;
    outfile.write((char*)&s, 2);
    s = 24;
    outfile.write((char*)&s, 2);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int color = int(255.99 * pixels[i][j].r()) * pow(16, 4) + int(255.99 * pixels[i][j].g()) * pow(16, 2) + int(255.99 * pixels[i][j].b());
            outfile.write((char*)((void*)&color), 3);
        }
    }

    outfile.close();
}