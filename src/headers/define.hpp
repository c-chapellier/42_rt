#pragma once

#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ios>

#define RADIAN(n) ((n) * (2 * M_PI / 360))
#define DEGREE(n) (n * (360 / (2 * M_PI)))

#define CLOCK_WISE 1
#define ANTI_CLOCK_WISE 0

double neg(double x);
double pos(double x);
double mod(double x, double z);

int rgbToInt(int r, int g, int b);

std::string itohex(int n);

void outputHex(std::ofstream *outfile, std::string hex);
void output(std::ofstream *outfile, std::string str);
