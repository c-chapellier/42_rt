#pragma once

#include "../header.hpp"

class NoInterException : public std::exception
{
private:
    std::string msg;

public:
    NoInterException(const std::string &msg) : msg(msg) {}

    virtual const char *what() const noexcept override
    {
        return this->msg.c_str();
    }
};
