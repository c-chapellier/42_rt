#pragma once

#include <iostream>
#include <array>
#include "Vec3.hpp"

class Matrix
{
private:
    double a[4][4];

public:
    Matrix();
    Matrix(std::array<double, 4> a0, std::array<double, 4> a1, std::array<double, 4> a2, std::array<double, 4> a3);
    Matrix(double a[4][4]);
    Matrix(double *a);
    inline const double *operator[](int i) const { return a[i]; }

    Matrix inverse() const;

    friend Vec3 operator*(const Matrix &m, const Vec3 &v);
    friend Matrix operator*(const Matrix &m, const Matrix &m2);
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m);

private:
    void getCofactor(const double A[4][4], double temp[4][4], int p, int q, int n) const;
    double determinant(const double A[4][4], int n) const;
    void adjoint(const double A[4][4], double adj[4][4]) const;

};


