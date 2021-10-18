#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include "./../header.hpp"
#include "./../../include/nlohmann/json.hpp"
#include "./../visuals/Camera.hpp"

// for convenience
using json = nlohmann::json;

class Camera;
class Config;

class Parser
{
    private:
        json j;
    public:
        Parser(std::string config_file);
        ~Parser();

        std::list<Object *> getObjects();
        std::list<Camera *> getCameras();
        std::list<Light *> getLights();
        Config *getConfig();
};
