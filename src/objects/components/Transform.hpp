#pragma once

#include "./../../headers/define.hpp"
#include "./../../solver/Matrix.hpp"
#include "./Point.hpp"
#include "./Vector.hpp"
#include "./Line.hpp"

class Transform
{
    private:
        Matrix forward_matrix;
        Matrix backward_matrix;

    public:
        Transform();
        ~Transform();

        void updateMatrices(
            double alpha, 
            double beta, 
            double gama, 
            double scaling_x, 
            double scaling_y, 
            double scaling_z, 
            double translation_x,
            double translation_y,
            double translation_z
        );

        Point apply(const Point &p, int type) const;
        Vector apply(const Vector &v, int type) const;
        Line apply(const Line &l, int type) const;
};