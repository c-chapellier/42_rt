#include "Matrix.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*              CONSTRUCTOR               *

* * * * * * * * * * * * * * * * * * * * */

Matrix::Matrix(int cols, int rows)
{
    for (int i = 0; i < cols; ++i) {
        std::vector<double> tmp;
        for (int j = 0; j < rows; ++j) {
            tmp.push_back(0);
        }
        this->vectors.push_back(tmp);
    }
}

Matrix::Matrix(const Matrix &m)
{
    for (int i = 0; i < m.getNbCols(); ++i) {
        std::vector<double> tmp;
        for (int j = 0; j < m.getNbRows(); ++j) {
            tmp.push_back(m[i][j]);
        }
        this->vectors.push_back(tmp);
    }
}

Matrix &Matrix::operator=(const Matrix &m)
{
    this->vectors.clear();
    for (int i = 0; i < m.getNbCols(); ++i) {
        std::vector<double> tmp;
        for (int j = 0; j < m.getNbRows(); ++j) {
            tmp.push_back(m[i][j]);
        }
        this->vectors.push_back(tmp);
    }
    return *this;
}

Matrix::~Matrix() {}

bool Matrix::isSquare() const
{
    return this->getNbCols() == this->getNbRows();
}

Matrix Matrix::getSubMatrixRowed(int n) const
{
    Matrix m(this->getNbCols() - 1, this->getNbRows() - 1);

    for (int i = 1; i < this->getNbCols(); ++i) {
        for (int j = 0; j < this->getNbRows(); ++j) {
            if (j < n)
                m[i - 1][j] = this->vectors[i][j];
            else if (j == n) {

            } else {
                m[i - 1][j - 1] = this->vectors[i][j];
            }
        }
    }
    return m;
}

Matrix Matrix::getSubMatrix(int c, int r) const
{
    Matrix m(this->getNbCols() - 1, this->getNbRows() - 1);

    int c_offset = 0;
    int r_offset = 0;
    for (int i = 0; i < this->getNbCols(); ++i) {
        for (int j = 0; j < this->getNbRows(); ++j) {
            c_offset = i < c ? (0) : (-1);
            r_offset = j < r ? (0) : (-1);
            if (i != c && j != r)
                m[i + c_offset][j + r_offset] = this->vectors[i][j];
        }
    }
    return m;
}

int Matrix::getNbCols() const
{
    return this->vectors.size();
}

int Matrix::getNbRows() const 
{
    if (this->vectors.size() == 0)
        throw "Matrix is empty";
    return this->vectors[0].size();
}

double Matrix::getDeterminant() const
{
    if (this->isSquare() == false)
        throw "Matrix must be squared to get the determinant";

    int n = this->getNbCols();
    if(n == 0)
        return 0;
    else if (n == 1)
        return this->vectors[0][0];
    else if (n == 2) {
        return (this->vectors[0][0] * this->vectors[1][1]) - (this->vectors[0][1] * this->vectors[1][0]);
    } else {
        double det = 0;
        for (int i = 0; i < n; ++ i) {
            double sign = (i % 2 == 0 ? (1) : (-1));
            Matrix subMatrix = this->getSubMatrixRowed(i);
            det += sign * subMatrix.getDeterminant() * this->vectors[0][i];
        }
        return det;
    }
}

void Matrix::unit()
{
    if (this->getNbCols() != this->getNbRows())
        throw "Matrix can not be unitary";

    for (int i = 0; i < this->getNbCols(); ++i) {
        for (int j = 0; j < this->getNbRows(); ++j) {
            this->vectors[i][j] = i == j ? (1) : (0);
        }
    }    
}

void Matrix::transpose()
{
    Matrix m(this->getNbRows(), this->getNbCols());

    for (int i = 0; i < this->getNbCols(); ++i) {
        for (int j = 0; j < this->getNbRows(); ++j) {
            m[j][i] = this->vectors[i][j];
        }
    }
    *this = m;
}

void Matrix::adjugate()
{
    if (this->getNbCols() != this->getNbRows())
        throw "Matrix can not be adjugate";

    Matrix m(this->getNbCols(), this->getNbRows());

    for (int i = 0; i < this->getNbCols(); ++i) {
        for (int j = 0; j < this->getNbRows(); ++j) {
            double sign = (i + j) % 2 == 0 ? (1) : (-1);
            Matrix subMatrix = getSubMatrix(i, j);
            m[i][j] = sign * subMatrix.getDeterminant();
        }
    }
    m.transpose();
    *this = m;
}

void Matrix::inverse()
{
    Matrix m1(*this);
    m1.adjugate();
    double det = this->getDeterminant();
    if (det == 0)
        throw "Matrix can not be reverse";
    Matrix m2 = (1.0 / det) * m1;
    *this = m2;
}

/* * * * * * * * * * * * * * * * * * * * *

*            ACCESS OPERATORS            *

* * * * * * * * * * * * * * * * * * * * */

std::vector<double> &Matrix::operator[](int i)
{
    return this->vectors[i];
}

std::vector<double> Matrix::operator[](int i) const
{
    return this->vectors[i];
}

/* * * * * * * * * * * * * * * * * * * * *

*           ARITHMETIC OPERATORS         *

* * * * * * * * * * * * * * * * * * * * */

Matrix operator+(const Matrix &m1, const Matrix &m2)
{
    if (m1.getNbCols() != m2.getNbCols() || m1.getNbRows() != m2.getNbRows())
        throw "Addition operator can not be apply on 2 different matrices";
    
    Matrix m(m1.getNbCols(), m1.getNbRows());
    for (int i = 0; i < m1.getNbCols(); ++i) {
        for (int j = 0; j < m1.getNbRows(); ++i) {
            m[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return m;
}

Matrix operator-(const Matrix &m1, const Matrix &m2)
{
    if (m1.getNbCols() != m2.getNbCols() || m1.getNbRows() != m2.getNbRows())
        throw "Addition operator can not be apply on 2 different matrices";
    
    Matrix m(m1.getNbCols(), m1.getNbRows());
    for (int i = 0; i < m1.getNbCols(); ++i) {
        for (int j = 0; j < m1.getNbRows(); ++i) {
            m[i][j] = m1[i][j] - m2[i][j];
        }
    }
    return m;
}

Matrix operator*(const Matrix &m1, const Matrix &m2)
{   
    int cols = m2.getNbCols();
    int rows = m1.getNbRows(); 
    Matrix m(cols, rows);
    for (int i = 0; i < m.getNbCols(); ++i) {
        for (int j = 0; j < m.getNbRows(); ++j) {
            for (int x = 0; x < m1.getNbCols(); ++x) {
                m[i][j] += m1[x][j] * m2[i][x];
            }
        }
    }
    return m;
}

Matrix operator*(const Matrix &m, const double &d)
{
    Matrix ret(m.getNbCols(), m.getNbRows());
    for (int i = 0; i < m.getNbCols(); ++i) {
        for (int j = 0; j < m.getNbRows(); ++j) {
            ret[i][j] = m[i][j] * d;
        }
    }
    return ret;
}

Matrix operator*(const double &d, const Matrix &m)
{
    Matrix ret(m.getNbCols(), m.getNbRows());
    for (int i = 0; i < m.getNbCols(); ++i) {
        for (int j = 0; j < m.getNbRows(); ++j) {
            ret[i][j] = m[i][j] * d;
        }
    }
    return ret;
}

/* * * * * * * * * * * * * * * * * * * * *

*             STREAM OPERATORS           *

* * * * * * * * * * * * * * * * * * * * */

std::ostream& operator<<(std::ostream& out, const Matrix &m)
{
    for (int i = 0; i < m.getNbCols(); ++i) {
        for (int j = 0; j < m.getNbRows(); ++j) {
            out << m[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}