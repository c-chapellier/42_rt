#include "MobiusTape.hpp"

MobiusTape::MobiusTape(double x, double y, double z)
{
    this->p = new Point(x, y, z);
    this->t = -1;
    this->v = 0;
}

MobiusTape::~MobiusTape()
{
    delete(this->p);
}

std::ostream& operator<< (std::ostream& out, const MobiusTape& mb)
{
    out << "MobiusTape : {" << std::endl
    << "\tpoint: " << *mb.p << std::endl
    << "\tt: " << mb.t << std::endl
    << "\tv: " << mb.v << std::endl
    << '}' << std::endl;
    return out;
}