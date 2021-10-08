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