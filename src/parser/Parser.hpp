#pragma once

#include "../header.hpp"

class Camera;
class Config;
class ColorManager;
class BlackObject;
class Light;

class Parser
{
    private:
        nlohmann::json j;
        ColorManager *colorManager;
        std::map<std::string, char> texture_map;

        Texture getTexture(nlohmann::json json);
        void setTransform(Object *obj, nlohmann::json json);
        void initTextureMap();
    public:
        Parser(std::string config_file);
        ~Parser();

        std::list<Object *> getObjects();
        std::list<Camera *> getCameras();
        std::list<Light *> getLights();
        std::list<BlackObject *> getBlackObjects();
        Config getConfig();
};
