#pragma once

#include <vector>
#include <ostream>
#include <iostream>

class Matrix
{
    private:
        std::vector<std::vector<double>> vectors;

        bool isSquare() const;
        Matrix getSubMatrixRowed(int n) const;
        Matrix getSubMatrix(int c, int r) const;
    public:
        Matrix(int cols, int rows);
        Matrix(const Matrix &m);
        Matrix &operator=(const Matrix &m);
        ~Matrix();

        int getNbCols() const;
        int getNbRows() const;
        double getDeterminant() const;

        void unit();
        void transpose();
        void adjugate();
        void inverse();

        std::vector<double> &operator[](int i);
        std::vector<double> operator[](int i) const;

        friend Matrix operator+(const Matrix &m1, const Matrix &m2);
        friend Matrix operator-(const Matrix &m1, const Matrix &m2);
        friend Matrix operator*(const Matrix &m1, const Matrix &m2);
        friend Matrix operator*(const Matrix &m, const double &d);
        friend Matrix operator*(const double &d, const Matrix &m);

        friend std::ostream& operator<<(std::ostream& out, const Matrix &m);
};