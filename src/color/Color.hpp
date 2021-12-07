#pragma once

#include <stdlib.h>
#include <iostream>
#include <fstream>

class Color
{
    private:
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char o;

        void generateRandomColor();
        int getByO(int c);
    public:
        Color();
        Color(int r, int g, int b);
        Color(int r, int g, int b, int o);
        ~Color();

        unsigned char getR() const;
        unsigned char getG() const;
        unsigned char getB() const;
        unsigned char getO() const;
        double getPR() const;
        double getPG() const;
        double getPB() const;
        double getP() const;

        void setR(int r);
        void setG(int g);
        void setB(int b);
        void setO(int o);

        Color reduceOf(double ratio) const;
        Color add(const Color &c);

        Color &operator=(const Color &p);

        friend std::ostream& operator<<(std::ostream& out, const Color& color);
};