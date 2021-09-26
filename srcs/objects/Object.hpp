#pragma once

#include <iostream>

class Object
{
private:
    const std::string name;
public:
    Object(std::string name);
    ~Object();

    friend std::ostream& operator<<(std::ostream& out, const Object& obj);
};