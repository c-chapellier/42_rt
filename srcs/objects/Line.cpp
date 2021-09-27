#include "Line.hpp"

Line::Line(double px, double py, double pz, double vx, double vy, double vz)
{
    this->p = new Point(px, py, pz);
    this->v = new Vector(vx, vy, vz);
}

Line::~Line()
{
    delete(this->p);
    delete(this->v);
}

std::ostream& operator<< (std::ostream& out, const Line& line)
{
    out << "Line : {" << std::endl
    << "\tpoint: " << *line.p << std::endl
    << "\tvector: " << *line.v << std::endl
    << '}' << std::endl;
    return out;
}