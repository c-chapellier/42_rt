#pragma once

#include "./../../headers/define.hpp"
#include "./../../solver/Matrix.hpp"
#include "./Point.hpp"
#include "./Vector.hpp"

class Transform
{
    private:
        double alpha;
        double beta;
        double gama;
        Point translation;
        Point scaling;
        Matrix forward_matrix;
        Matrix backward_matrix;

    public:
        Transform();
        ~Transform();

        void setAlpha(double alpha);
        void setBeta(double beta);
        void setGama(double gama);
        void setTranslation(double x, double y, double z);
        void setScaling(double x, double y, double z);

        void updateMatrices();

        Point getTranslation() const;

        Vector apply(const Vector &v, int type) const;
        Point apply(const Point &p, int type) const;

};