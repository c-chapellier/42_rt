#include "Object.hpp"

Object::Object(std::string name) : name(name)
{
}

Object::~Object()
{
}

std::ostream& operator<< (std::ostream& out, const Object& obj)
{
    out << "Object(" << obj.name << ')';
    return out;
}