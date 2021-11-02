#pragma once

#include <math.h>

class Complex
{
    private:
        float real;
        float imaginary;
    public:
        Complex();
        Complex(float real, float imaginary);
        Complex(Complex const &c);
        void operator=(Complex const &c);
        ~Complex();

        Complex pow(int p);
        friend Complex operator+(Complex const &c1, Complex const &c2);
        friend Complex operator+(Complex const &c1, float const f);
        friend Complex operator-(Complex const &c1, Complex const &c2);
        friend Complex operator-(Complex const &c1, float const f);
        friend Complex operator*(Complex const &c1, Complex const &c2);
        friend Complex operator*(Complex const &c1, float const f);
        friend Complex operator/(Complex const &c1, Complex const &c2);
        friend Complex operator/(Complex const &c1, float const f);
};