#include "define.hpp"

double neg(double x){
    return x < 0 ? (x) : (-x);
}

double pos(double x){
    return x > 0 ? (x) : (-x);
}

double mod(double x, double z){
    double i = x / z;
    i = (int)i;
    x = x - (i * z);
    return x;
}

int rgbToInt(int r, int g, int b)
{
    int c = 0;

    c = r * pow(16, 4);
    c += g * pow(16, 2);
    c += b;
    return c;
}

std::string itohex(int n) {
    std::string res;
    char hex_string[20];
    sprintf(hex_string, "%X", n);

    int size = strlen(hex_string);
    for (int i = size; i < 8; ++i) {
        res += "0";
    }
    res += hex_string;
    return res;
}

void outputHex(std::ofstream *outfile, std::string hex)
{
    char buf[3];
    std::stringstream input(hex);

    while (input)
    {
        buf[0] = 0;
        buf[1] = 0;
        buf[2] = 0;
        input >> buf[0] >> buf[1];
        long val = strtol(buf, nullptr, 16);
        if(input)
            *outfile << static_cast<unsigned char>(val);
    }
}

void output(std::ofstream *outfile, std::string str)
{
    *outfile << str;
}