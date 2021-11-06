#include "ColorManager.hpp"

ColorManager::ColorManager(nlohmann::json colors)
{
    for (auto it = colors.begin(); it != colors.end(); ++it)
    {
        this->colors[it.key()] = Color(it.value()[0], it.value()[1], it.value()[2], it.value()[3]);
    }
}

ColorManager::~ColorManager()
{

}

Color ColorManager::getColor(const std::string &color)
{
    return this->colors[color];
}
