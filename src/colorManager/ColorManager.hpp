#pragma once

#include "../header.hpp"
#include "../../include/nlohmann/json.hpp"

class ColorManager
{
private:
    std::map<std::string, Color *> colors;
public:
    ColorManager(nlohmann::json colors);
    ~ColorManager();

    Color *getColor(std::string color);
};
