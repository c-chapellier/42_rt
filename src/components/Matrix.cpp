
#include "Matrix.hpp"

Matrix::Matrix()
{

}

Matrix::Matrix(std::array<double, 4> a0, std::array<double, 4> a1, std::array<double, 4> a2, std::array<double, 4> a3)
{
    this->a[0][0] = a0[0];
    this->a[0][1] = a0[1];
    this->a[0][2] = a0[2];
    this->a[0][3] = a0[3];
    this->a[1][0] = a1[0];
    this->a[1][1] = a1[1];
    this->a[1][2] = a1[2];
    this->a[1][3] = a1[3];
    this->a[2][0] = a2[0];
    this->a[2][1] = a2[1];
    this->a[2][2] = a2[2];
    this->a[2][3] = a2[3];
    this->a[3][0] = a3[0];
    this->a[3][1] = a3[1];
    this->a[3][2] = a3[2];
    this->a[3][3] = a3[3];
}

Matrix::Matrix(double a[4][4])
{
    this->a[0][0] = a[0][0];
    this->a[0][1] = a[0][1];
    this->a[0][2] = a[0][2];
    this->a[0][3] = a[0][3];
    this->a[1][0] = a[1][0];
    this->a[1][1] = a[1][1];
    this->a[1][2] = a[1][2];
    this->a[1][3] = a[1][3];
    this->a[2][0] = a[2][0];
    this->a[2][1] = a[2][1];
    this->a[2][2] = a[2][2];
    this->a[2][3] = a[2][3];
    this->a[3][0] = a[3][0];
    this->a[3][1] = a[3][1];
    this->a[3][2] = a[3][2];
    this->a[3][3] = a[3][3];
}

Matrix::Matrix(double *a)
{
    this->a[0][0] = a[0];
    this->a[0][1] = a[1];
    this->a[0][2] = a[2];
    this->a[0][3] = a[3];
    this->a[1][0] = a[4];
    this->a[1][1] = a[5];
    this->a[1][2] = a[6];
    this->a[1][3] = a[7];
    this->a[2][0] = a[8];
    this->a[2][1] = a[9];
    this->a[2][2] = a[10];
    this->a[2][3] = a[11];
    this->a[3][0] = a[12];
    this->a[3][1] = a[13];
    this->a[3][2] = a[14];
    this->a[3][3] = a[15];
}

Matrix Matrix::inverse() const
{
    int det = this->determinant(this->a, 4);
    if (det == 0) throw "Cannot inverse matrix";

    double adj[4][4];
    this->adjoint(this->a, adj);

    double inv[4][4];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            inv[i][j] = adj[i][j] / float(det);

    return Matrix(inv);
}

void Matrix::getCofactor(const double A[4][4], double temp[4][4], int p, int q, int n) const
{
    int i = 0, j = 0;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double Matrix::determinant(const double A[4][4], int n) const
{
    double D = 0;

    if (n == 1) return A[0][0];

    double temp[4][4];

    int sign = 1;

    for (int f = 0; f < n; f++)
    {
        this->getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] *  this->determinant(temp, n - 1);
        sign = -sign;
    }

    return D;
}

void Matrix::adjoint(const double A[4][4], double adj[4][4]) const
{
    int sign = 1;
    double temp[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->getCofactor(A, temp, i, j, 4);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = sign *  this->determinant(temp, 3);
        }
    }
}

std::vector<double> operator*(const Matrix &m, const std::vector<double> &v)
{
    std::vector<double> a(4, 0);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
                a[i] += m[i][j] * v[j];
        }
    }

    return a;
}

Matrix operator*(const Matrix &m, const Matrix &m2)
{
    double a[4][4] = { { 0 } };

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                a[i][j] += m[i][k] * m2[k][j];
            }
        }
    }

    return Matrix(a);
}

std::ostream &operator<<(std::ostream &os, const Matrix &m)
{
    os << "matrix [" << std::endl;
    for (int i = 0; i < 4; ++i)
    {
        os << "\t";
        for (int j = 0; j < 4; ++j)
        {
            os << m[i][j] << "\t";
        }
        os << std::endl;
    }
    os << "]" << std::endl;
    return os;
}
