
#include "BMP.hpp"

void BMP::write(const std::vector< std::vector<Vec3> > &pixels, const std::string &saveFile)
{
    int d, height = pixels.size(), width = pixels[0].size();
    unsigned short s;

    char file[26 + (width * height * 3)];

    memcpy(&file[0], "BM", 2);
    d = 26 + (width * height * 3);
    memcpy(&file[2], &d, 4);
    d = 0;
    memcpy(&file[6], &d, 4);
    d = 26;
    memcpy(&file[10], &d, 4);

    d = 12;
    memcpy(&file[14], &d, 4);
    s = width;
    memcpy(&file[18], &s, 2);
    s = height;
    memcpy(&file[20], &s, 2);
    s = 1;
    memcpy(&file[22], &s, 2);
    s = 24;
    memcpy(&file[24], &s, 2);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int color = (int(255.99 * pixels[i][j].r()) << 16) + (int(255.99 * pixels[i][j].g()) << 8) + int(255.99 * pixels[i][j].b());
            memcpy(&file[26 + ((i * width + j) * 3)], &color, 3);
        }
    }

    std::ofstream outfile(saveFile, std::ofstream::binary);
    outfile.write(file, 26 + (width * height * 3));
    outfile.close();
}
