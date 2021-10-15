#include "Parser.hpp"

Parser::Parser(std::string config_file)
{
    this->file = config_file;
}

Parser::~Parser()
{
}

std::list<Object*> Parser::getObjects()
{
    std::ifstream f(this->file);
    json j;
    f >> j;

    std::list<Object *> objects;

    for (auto const& obj : j["objects"]) {
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
                obj["values"][9]
            ));
        } else if (obj["type"] == "Polygon") {
            Point coordinates(obj["coordinates"][0], obj["coordinates"][1], obj["coordinates"][2]);
            objects.push_back(PolygoneFactory::createPolygone(
                obj["name"],
                coordinates,
                obj["values"][0],
                obj["values"][1],
                obj["values"][2],
                obj["values"][3]
            ));
        } else {
            throw "Object is not supported";
        }
    }
    return objects;
}

std::list<Camera*> Parser::getCameras()
{
    std::ifstream f(this->file);
    json j;
    f >> j;

    std::list<Camera*> cameras;
    for (auto const& cam : j["cameras"]) {
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

Config *Parser::getConfig()
{
    std::ifstream f(this->file);
    json j;
    f >> j;

    Config *config = new Config();
    config->setHeight(j["height"]);
    config->setWidth(j["width"]);
    config->setAmbientColor(j["ambient"][0], j["ambient"][1], j["ambient"][2], j["ambient"][3]);
    return config;
}