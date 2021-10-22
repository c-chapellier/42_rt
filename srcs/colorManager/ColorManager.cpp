#include "ColorManager.hpp"

ColorManager::ColorManager(nlohmann::json colors)
{
    for (auto it = colors.begin(); it != colors.end(); ++it)
    {
        this->colors[it.key()] = new Color(it.value()[0], it.value()[1], it.value()[2], it.value()[3]);
    }
}

ColorManager::~ColorManager()
{

}

Color *ColorManager::getColor(std::string color)
{
    Color *c = this->colors[color];
    if (c == NULL)
        throw "ColorManager::getColor: color not in map";
    return c;
}
