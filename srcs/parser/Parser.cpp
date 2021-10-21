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

    for (auto const& obj : this->j["objects"])
    {
        if (obj["type"] == "Plane")
        {
            Plane *plane = new Plane(obj["point"][0], obj["point"][1], obj["point"][2], obj["normal"][0], obj["normal"][1], obj["normal"][2]);

            for (auto const& color : obj["colors"])
                plane->addColor(new Color(color[0], color[1], color[2], color[3]));

            plane->setTexture(new Texture(obj["texture"]["type"], obj["texture"]["values"][0], obj["texture"]["values"][1]));
            objects.push_back(plane);
        }
        else if (obj["type"] == "Quadratic") {
            Point coordinates(obj["coordinates"][0], obj["coordinates"][1], obj["coordinates"][2]);
            Quadratic *quadratic = new Quadratic(
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
            );
            for(auto const& color : obj["colors"]) {
                quadratic->addColor(new Color(color[0], color[1], color[2], color[3]));
            }
            quadratic->setTexture(new Texture(obj["texture"]["type"], obj["texture"]["values"][0], obj["texture"]["values"][1]));
            objects.push_back(quadratic);
        } else if (obj["type"] == "Polygon")
        {
            Point coordinates(obj["coordinates"][0], obj["coordinates"][1], obj["coordinates"][2]);
            Polygone *polygon = PolygoneFactory::createPolygone(
                obj["name"],
                coordinates,
                obj["values"][0],
                obj["values"][1],
                obj["values"][2],
                obj["values"][3],
                obj["rotation"][0],
                obj["rotation"][1],
                obj["rotation"][2]
            );
            for(auto const& color : obj["colors"]) {
                polygon->addColor(new Color(color[0], color[1], color[2], color[3]));
            }
            polygon->setTexture(new Texture(obj["texture"]["type"], obj["texture"]["values"][0], obj["texture"]["values"][1]));
            objects.push_back(polygon);
        } else if (obj["type"] == "Shape") {
            Point coordinates(obj["coordinates"][0], obj["coordinates"][1], obj["coordinates"][2]);
            std::vector<Object *> shape = ShapeFactory::createShape(
                obj["name"],
                coordinates,
                obj["values"][0],
                obj["values"][1],
                obj["values"][2],
                obj["rotation"][0],
                obj["rotation"][1],
                obj["rotation"][2]
            );
            for(int i = 0; i < (int)shape.size(); ++i){
                for(auto const& color : obj["colors"]) {
                    shape[i]->addColor(new Color(color[0], color[1], color[2], color[3]));
                }
                shape[i]->setTexture(new Texture(obj["texture"]["type"], obj["texture"]["values"][0], obj["texture"]["values"][1]));
                objects.push_back(shape[i]);
            }
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
    config->setBlur(this->j["blur"]);
    config->setFilter(this->j["filter"]);
    return config;
}