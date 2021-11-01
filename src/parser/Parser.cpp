#include "Parser.hpp"

Parser::Parser(std::string config_file)
{
    std::ifstream f(config_file);
    f >> this->j;

    this->colorManager = new ColorManager(this->j["colors"]);
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
                plane->addColor(*this->colorManager->getColor(color));

            plane->setTexture(Texture(obj["texture"]["type"], obj["texture"]["values"][0], obj["texture"]["values"][1]));
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
                quadratic->addColor(*this->colorManager->getColor(color));
            }
            quadratic->setTexture(Texture(obj["texture"]["type"], obj["texture"]["values"][0], obj["texture"]["values"][1]));
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
                polygon->addColor(*this->colorManager->getColor(color));
            }
            polygon->setTexture(Texture(obj["texture"]["type"], obj["texture"]["values"][0], obj["texture"]["values"][1]));
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
                    shape[i]->addColor(*this->colorManager->getColor(color));
                }
                shape[i]->setTexture(Texture(obj["texture"]["type"], obj["texture"]["values"][0], obj["texture"]["values"][1]));
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
            light["coordinates"][2],
            this->colorManager->getColor(light["color"])
        ));
    }
    return lights;
}

std::list<BlackObject *> Parser::getBlackObjects()
{
    std::list<BlackObject *> objects;

    for (auto const& sphere : this->j["blackObjects"]["blackSpheres"]) {
        objects.push_back(new BlackSphere(
            sphere["coordinates"][0],
            sphere["coordinates"][1],
            sphere["coordinates"][2],
            sphere["radius"]
        ));
    }

    for (auto const& cylinder : this->j["blackObjects"]["blackCylinders"]) {
        objects.push_back(new BlackCylinder(
            cylinder["coordinates"][0],
            cylinder["coordinates"][1],
            cylinder["coordinates"][2],
            cylinder["direction"][0],
            cylinder["direction"][1],
            cylinder["direction"][2],
            cylinder["radius"]
        ));
    }

    return objects;
}

Config *Parser::getConfig()
{
    Config *config = new Config();

    config->setHeight(this->j["height"]);
    config->setWidth(this->j["width"]);
    config->setPrecision(this->j["precision"]);
    config->setAmbientColor(this->colorManager->getColor(this->j["ambient"]));
    config->setBlur(this->j["blur"]);
    config->setFilter(this->j["filter"]);
    config->setPerlinNoise(this->j["perlinNoise"]);
    return config;
}
