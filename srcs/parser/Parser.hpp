#pragma once

#include "../header.hpp"

class Camera;
class Config;
class ColorManager;
class BlackObject;


class Parser
{
    private:
        nlohmann::json j;
        ColorManager *colorManager;
    public:
        Parser(std::string config_file);
        ~Parser();

        std::list<Object *> getObjects();
        std::list<Camera *> getCameras();
        std::list<Light *> getLights();
        std::list<BlackObject *> getBlackObjects();
        Config *getConfig();
};
