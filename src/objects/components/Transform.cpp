#include "Transform.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

Transform::Transform()
    : forward_matrix(4, 4), backward_matrix(4, 4)
{
}
Transform::~Transform() {}

/* * * * * * * * * * * * * * * * * * * * *

*                SETTER                  *

* * * * * * * * * * * * * * * * * * * * */

void Transform::updateMatrices(
    double alpha, 
    double beta, 
    double gama, 
    double scaling_x, 
    double scaling_y, 
    double scaling_z,
    double translation_x,
    double translation_y,
    double translation_z
) {
    Matrix m_trans(4, 4);
    m_trans.unit();
    m_trans[3][0] = translation_x;
    m_trans[3][1] = translation_y;
    m_trans[3][2] = translation_z;

    Matrix m_scale(4, 4);
    m_scale.unit();
    m_scale[0][0] = scaling_x;
    m_scale[1][1] = scaling_y;
    m_scale[2][2] = scaling_z;

    Matrix m_rotate_x(4, 4);
    m_rotate_x.unit();
    m_rotate_x[1][1] = cos(RADIAN(alpha));
    m_rotate_x[2][1] = -sin(RADIAN(alpha));
    m_rotate_x[1][2] = sin(RADIAN(alpha));
    m_rotate_x[2][2] = cos(RADIAN(alpha));

    Matrix m_rotate_y(4, 4);
    m_rotate_y.unit();
    m_rotate_y[0][0] = cos(RADIAN(beta));
    m_rotate_y[2][0] = sin(RADIAN(beta));
    m_rotate_y[0][2] = -sin(RADIAN(beta));
    m_rotate_y[2][2] = cos(RADIAN(beta));

    Matrix m_rotate_z(4, 4);
    m_rotate_z.unit();
    m_rotate_z[0][0] = cos(RADIAN(gama));
    m_rotate_z[1][0] = -sin(RADIAN(gama));
    m_rotate_z[0][1] = sin(RADIAN(gama));
    m_rotate_z[1][1] = cos(RADIAN(gama));

    forward_matrix = m_trans * m_scale * m_rotate_z * m_rotate_y * m_rotate_x;
    backward_matrix = forward_matrix;
    backward_matrix.inverse();
}

/* * * * * * * * * * * * * * * * * * * * *

*              FUNCTIONS                 *

* * * * * * * * * * * * * * * * * * * * */

Vector Transform::apply(const Vector &v, int type) const
{
    Matrix m_p1(1, 4);
    m_p1[0][0] = v.getX();
    m_p1[0][1] = v.getY();
    m_p1[0][2] = v.getZ();
    m_p1[0][3] = 1;

    Matrix m1(1, 4);
    if(type == TO_LOCAL) {
        m1 = this->backward_matrix * m_p1;
    } else {
        m1 = this->forward_matrix * m_p1;
    }

    return Vector(m1[0][0], m1[0][1], m1[0][2]);
}

Point Transform::apply(const Point &p, int type) const
{
    Matrix m_p1(1, 4);
    m_p1[0][0] = p.getX();
    m_p1[0][1] = p.getY();
    m_p1[0][2] = p.getZ();
    m_p1[0][3] = 1;

    Matrix m1(1, 4);
    if(type == TO_LOCAL) {
        m1 = this->backward_matrix * m_p1;
    } else {
        m1 = this->forward_matrix * m_p1;
        
    }

    return Point(m1[0][0], m1[0][1], m1[0][2]);
}

Line Transform::apply(const Line &l, int type) const
{
    return Line(apply(l.getP(), type), apply(l.getV(), type));
}