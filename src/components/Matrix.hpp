#pragma once

// #include "../header.hpp"

#include <iostream>
#include <array>
#include <vector>

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

    friend std::vector<double> operator*(const Matrix &m, const std::vector<double> &v);
    friend Matrix operator*(const Matrix &m, const Matrix &m2);
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m);

private:
    void getCofactor(const double A[4][4], double temp[4][4], int p, int q, int n) const;
    double determinant(const double A[4][4], int n) const;
    void adjoint(const double A[4][4], double adj[4][4]) const;

};


