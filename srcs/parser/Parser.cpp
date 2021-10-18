#include "Parser.hpp"

Parser::Parser(std::string config_file)
{
    std::ifstream f(config_file);
    f >> this->j;
}

Parser::~Parser()
{
}

std::list<Object*> Parser::getObjects()
{
    std::list<Object *> objects;

    for (auto const& obj : this->j["objects"]) {
        if(obj["type"] == "Quadratic") {
            Point coordinates(obj["coordinates"][0], obj["coordinates"][1], obj["coordinates"][2]);
            objects.push_back(new Quadratic(
                coordinates,
                obj["values"][0],
                obj["values"][1],
                obj["values"][2],
                obj["values"][3],
                obj["values"][4],
                obj["values"][5],
                obj["values"][6],
                obj["values"][7],
                obj["values"][8],
                obj["values"][9],
                new Color(obj["color"][0], obj["color"][1], obj["color"][2], obj["color"][3])
            ));
        } else if (obj["type"] == "Polygon") {
            Point coordinates(obj["coordinates"][0], obj["coordinates"][1], obj["coordinates"][2]);
            objects.push_back(PolygoneFactory::createPolygone(
                obj["name"],
                coordinates,
                obj["values"][0],
                obj["values"][1],
                obj["values"][2],
                obj["values"][3],
                obj["rotation"][0],
                obj["rotation"][1],
                obj["rotation"][2],
                new Color(obj["color"][0], obj["color"][1], obj["color"][2], obj["color"][3])
            ));
        } else {
            throw "Object is not supported";
        }
    }
    return objects;
}

std::list<Camera*> Parser::getCameras()
{
    std::list<Camera*> cameras;

    for (auto const& cam : this->j["cameras"]) {
        cameras.push_back(new Camera(
            cam["coordinates"][0],
            cam["coordinates"][1],
            cam["coordinates"][2],
            cam["direction"][0],
            cam["direction"][1],
            cam["direction"][2],
            cam["aperture"]
        ));
    }
    return cameras;
}

std::list<Light *> Parser::getLights()
{
    std::list<Light *> lights;

    for (auto const& light : this->j["lights"]) {
        lights.push_back(new Light(
            light["coordinates"][0],
            light["coordinates"][1],
            light["coordinates"][2]
        ));
    }
    return lights;
}

Config *Parser::getConfig()
{
    Config *config = new Config();

    config->setHeight(this->j["height"]);
    config->setWidth(this->j["width"]);
    config->setPrecision(this->j["precision"]);
    config->setAmbientColor(this->j["ambient"][0], this->j["ambient"][1], this->j["ambient"][2], this->j["ambient"][3]);
    return config;
}