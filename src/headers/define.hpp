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

#define TO_REAL 1
#define TO_LOCAL 2

#define UNIFORM 1
#define GRADIENT 2
#define GRID 3
#define VERTICAL_LINED 4
#define HORIZONTAL_LINED 5
#define IMAGE 6

double neg(double x);
double pos(double x);
double mod(double x, double z);

int rgbToInt(int r, int g, int b);

std::string itohex(int n);

void outputHex(std::ofstream *outfile, std::string hex);
void output(std::ofstream *outfile, std::string str);
