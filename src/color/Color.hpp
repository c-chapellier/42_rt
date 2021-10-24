#pragma once

#include <stdlib.h>
#include <iostream>

class Color
{
    private:
        int r;
        int g;
        int b;
        int o;

        void generateRandomColor();
        int getByO(int c);
    public:
        Color();
        Color(int o);
        Color(int r, int g, int b);
        Color(int r, int g, int b, int o);
        ~Color();

        int getR() const;
        int getG() const;
        int getB() const;
        int getO() const;
        double getPR() const;
        double getPG() const;
        double getPB() const;
        double getP() const;

        void setR(int r);
        void setG(int g);
        void setB(int b);
        void setO(int o);

        Color *reduceOf(double ratio);
        Color *add(Color *c);

        friend std::ostream& operator<<(std::ostream& out, const Color& color);
};