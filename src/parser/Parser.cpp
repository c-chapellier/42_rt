#include "Parser.hpp"

Parser::Parser(std::string config_file)
{
    std::ifstream f(config_file);
    f >> this->j;

    this->colorManager = new ColorManager(this->j["colors"]);
}

Parser::~Parser() {}

Texture Parser::getTexture(nlohmann::json json) {
    nlohmann::json t = json["texture"];
    if (t == nullptr) {
        std::cout << "no texture" << std::endl;
        Texture texture;
        return texture;
    } else if (t["type"] == "Image") {
        Texture texture(
            t["type"],
            (std::string)t["file"]
        );
        try { texture.setHOffset(t["hOffset"]); } catch(...) { texture.setHOffset(0); }
        try { texture.setWOffset(t["wOffset"]); } catch(...) { texture.setWOffset(0); }
        try { texture.setSpeed(t["speed"]); } catch(...) { texture.setSpeed(1); }
        return texture;
    } else {
        Texture texture(
            t["type"],
            t["values"][0],
            t["values"][1]
        );
        return texture;
    }
}

std::list<Object*> Parser::getObjects()
{
    std::list<Object *> objects;

    for (auto const& obj : this->j["objects"])
    {
        if (obj["type"] == "Plane") {
            Plane *plane = new Plane(
                obj["point"][0], 
                obj["point"][1], 
                obj["point"][2], 
                obj["normal"][0], 
                obj["normal"][1], 
                obj["normal"][2]
            );

            for (auto const& color : obj["colors"])
                plane->addColor(*this->colorManager->getColor(color));

            plane->setTexture(getTexture(obj));
            objects.push_back(plane);

        } else if (obj["type"] == "Sphere") {
            Sphere *sp = new Sphere(
                obj["coordinates"][0], 
                obj["coordinates"][1], 
                obj["coordinates"][2], 
                obj["radius"]
            );

            for (auto const& color : obj["colors"])
                sp->addColor(*this->colorManager->getColor(color));

            sp->setTexture(getTexture(obj));
            objects.push_back(sp);

        } else if (obj["type"] == "Quadratic") {
            Point coordinates(
                obj["coordinates"][0], 
                obj["coordinates"][1], 
                obj["coordinates"][2]
            );
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
            for(auto const& color : obj["colors"])
                quadratic->addColor(*this->colorManager->getColor(color));

            quadratic->setTexture(getTexture(obj));
            objects.push_back(quadratic);

        } else if (obj["type"] == "Polygon") {
            Point coordinates(
                obj["coordinates"][0], 
                obj["coordinates"][1], 
                obj["coordinates"][2]
            );
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
            for(auto const& color : obj["colors"])
                polygon->addColor(*this->colorManager->getColor(color));

            polygon->setTexture(getTexture(obj));
            objects.push_back(polygon);

        } else if (obj["type"] == "Shape") {
            Point coordinates(
                obj["coordinates"][0], 
                obj["coordinates"][1], 
                obj["coordinates"][2]
            );
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
                shape[i]->setTexture(getTexture(obj));
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
    config->setAmbientColor(this->colorManager->getColor(this->j["ambient"]));
    try { config->setPrecision(this->j["precision"]); } catch(...) { config->setPrecision(1); }
    try { config->setBlur(this->j["blur"]); } catch(...) { config->setBlur(0); }
    try { config->setFilter(this->j["filter"]); } catch(...) { config->setFilter("None"); }
    try { config->setPerlinNoise(this->j["perlinNoise"]); } catch(...) { config->setPerlinNoise(false); }
    return config;
}
