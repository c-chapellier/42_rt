#include "Complex.hpp"

Complex::Complex() {
    this->real = 0;
    this->imaginary = 0;
}

Complex::Complex(float real, float imaginary) {
    this->real = real;
    this->imaginary = imaginary;
}

Complex::Complex(Complex const &c) {
    this->real = c.real;
    this->imaginary = c.imaginary;
}

void Complex::operator=(Complex const &c) {
    this->real = c.real;
    this->imaginary = c.imaginary;
}

Complex::~Complex() {};

Complex Complex::pow(int p) {
    Complex tmp(*this);

    while(p > 1) {
        tmp = tmp * *this;
        --p;
    }
    return tmp;
}

Complex operator+(Complex const &c1, Complex const &c2) {
    return Complex(c1.real + c2.real, c1.imaginary + c2.imaginary);
}

Complex operator+(Complex const &c1, float const f) {
    return Complex(c1.real + f, c1.imaginary);
}

Complex operator-(Complex const &c1, Complex const &c2) {
    return Complex(c1.real - c2.real, c1.imaginary - c2.imaginary);
}

Complex operator-(Complex const &c1, float const f) {
    return Complex(c1.real - f, c1.imaginary);
}

Complex operator*(Complex const &c1, Complex const &c2) {
    return Complex(
        (c1.real * c2.real) - (c1.imaginary * c2.imaginary), 
        (c1.real * c2.imaginary) + (c1.imaginary * c2.real)
    );
}

Complex operator*(Complex const &c1, float const f) {
    return Complex(c1.real * f, c1.imaginary * f);
}

Complex operator/(Complex const &c1, Complex const &c2) {
    return Complex(
        ((c1.real * c2.real) + (c1.imaginary * c2.imaginary)) / (pow(c2.real, 2) + pow(c2.imaginary, 2)),
        ((c1.imaginary * c2.real) - (c1.real * c2.imaginary)) / (pow(c2.real, 2) + pow(c2.imaginary, 2))
    );
}

Complex operator/(Complex const &c1, float const f) {
    return Complex(c1.real / f, c1.imaginary / f);
}