#pragma once

#include "./../../solver/Matrix.hpp"
#include "./Point.hpp"

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

        Matrix &getForwardMatrix();
        Matrix getForwardMatrix() const;
        Matrix &getBackwardMatrix();
        Matrix getBackwardMatrix() const;

};