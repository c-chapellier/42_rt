#include "Parser.hpp"

Parser::Parser(std::string config_file)
{
    std::ifstream f(config_file);
    f >> this->j;

    this->colorManager = new ColorManager(this->j["colors"]);
}

Parser::~Parser()
{
    delete this->colorManager;
}

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
        try { texture.setOpacity(t["opacity"]); } catch(...) { }
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

std::list<Object *> Parser::getObjects()
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
                plane->addColor(this->colorManager->getColor(color));

            plane->setTexture(getTexture(obj));

            nlohmann::json tmp = obj;
            try { plane->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(plane);

        } else if (obj["type"] == "Sphere") {
            Sphere *sp = new Sphere(
                obj["coordinates"][0], 
                obj["coordinates"][1], 
                obj["coordinates"][2], 
                obj["radius"]
            );

            for (auto const& color : obj["colors"])
                sp->addColor(this->colorManager->getColor(color));

            sp->setTexture(getTexture(obj));
            
            nlohmann::json tmp = obj;
            try { sp->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(sp);

        } else if (obj["type"] == "Cylinder") {
            Cylinder *cl = new Cylinder(
                obj["radius"]
            );

            for (auto const& color : obj["colors"])
                cl->addColor(this->colorManager->getColor(color));

            cl->setTexture(getTexture(obj));
            
            nlohmann::json tmp = obj;
            try { cl->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(cl);

        } else if (obj["type"] == "Circle") {
            Circle *c = new Circle(
                obj["coordinates"][0], 
                obj["coordinates"][1], 
                obj["coordinates"][2],
                obj["normal"][0], 
                obj["normal"][1], 
                obj["normal"][2],
                obj["externRadius"],
                obj["internRadius"]
            );

            for (auto const& color : obj["colors"])
                c->addColor(this->colorManager->getColor(color));

            c->setTexture(getTexture(obj));

            nlohmann::json tmp = obj;
            try { c->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(c);

        } else if (obj["type"] == "MobiusTape") {
            MobiusTape *mt = new MobiusTape(
                obj["coordinates"][0], 
                obj["coordinates"][1], 
                obj["coordinates"][2],
                obj["values"][0],
                obj["values"][1],
                obj["values"][2],
                obj["values"][3],
                obj["values"][4],
                obj["values"][5],
                obj["values"][6]
            );

            for (auto const& color : obj["colors"])
                mt->addColor(this->colorManager->getColor(color));

            mt->setTexture(getTexture(obj));

            nlohmann::json tmp = obj;
            try { mt->setReflexion(tmp["reflection"]); } catch(...) {}
            
            objects.push_back(mt);

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
                quadratic->addColor(this->colorManager->getColor(color));

            quadratic->setTexture(getTexture(obj));

            nlohmann::json tmp = obj;
            try { quadratic->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(quadratic);

        } else if (obj["type"] == "CubicSurface") {
            CubicSurface *cs = new CubicSurface(
                obj["coordinates"][0], 
                obj["coordinates"][1], 
                obj["coordinates"][2]
            );
            nlohmann::json tmp = obj;
            try { cs->setX3(tmp["x3"]); } catch (...) {}
            try { cs->setY3(tmp["y3"]); } catch (...) {}
            try { cs->setZ3(tmp["z3"]); } catch (...) {}
            try { cs->setX2Y(tmp["x2y"]); } catch (...) {}
            try { cs->setX2Z(tmp["x2z"]); } catch (...) {}
            try { cs->setY2X(tmp["y2x"]); } catch (...) {}
            try { cs->setY2Z(tmp["y2z"]); } catch (...) {}
            try { cs->setZ2X(tmp["z2x"]); } catch (...) {}
            try { cs->setZ2Y(tmp["z2y"]); } catch (...) {}
            try { cs->setXYZ(tmp["xyz"]); } catch (...) {}
            try { cs->setX2(tmp["x2"]); } catch (...) {}
            try { cs->setY2(tmp["y2"]); } catch (...) {}
            try { cs->setZ2(tmp["z2"]); } catch (...) {}
            try { cs->setXY(tmp["xy"]); } catch (...) {}
            try { cs->setXZ(tmp["xz"]); } catch (...) {}
            try { cs->setYZ(tmp["yz"]); } catch (...) {}
            try { cs->setX(tmp["x"]); } catch (...) {}
            try { cs->setY(tmp["y"]); } catch (...) {}
            try { cs->setZ(tmp["z"]); } catch (...) {}
            try { cs->setK(tmp["k"]); } catch (...) {}

            for(auto const& color : obj["colors"])
                cs->addColor(this->colorManager->getColor(color));

            cs->setTexture(getTexture(obj));
            try { cs->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(cs);

        } else if (obj["type"] == "QuarticSurface") {
            QuarticSurface *qs = new QuarticSurface(
                obj["coordinates"][0], 
                obj["coordinates"][1], 
                obj["coordinates"][2]
            );
            nlohmann::json tmp = obj;
            try { qs->setX4(tmp["x4"]); } catch (...) {}
            try { qs->setY4(tmp["y4"]); } catch (...) {}
            try { qs->setZ4(tmp["z4"]); } catch (...) {}
            try { qs->setX3Y(tmp["x3y"]); } catch (...) {}
            try { qs->setX3Z(tmp["x3z"]); } catch (...) {}
            try { qs->setY3X(tmp["y3x"]); } catch (...) {}
            try { qs->setY3Z(tmp["y3z"]); } catch (...) {}
            try { qs->setZ3X(tmp["z3x"]); } catch (...) {}
            try { qs->setZ3Y(tmp["z3y"]); } catch (...) {}
            try { qs->setX2YZ(tmp["x2yz"]); } catch (...) {}
            try { qs->setY2XZ(tmp["y2xz"]); } catch (...) {}
            try { qs->setZ2XY(tmp["z2yx"]); } catch (...) {}
            try { qs->setX2Y2(tmp["x2y2"]); } catch (...) {}
            try { qs->setX2Z2(tmp["x2z2"]); } catch (...) {}
            try { qs->setY2Z2(tmp["y2z2"]); } catch (...) {}
            try { qs->setX3(tmp["x3"]); } catch (...) {}
            try { qs->setY3(tmp["y3"]); } catch (...) {}
            try { qs->setZ3(tmp["z3"]); } catch (...) {}
            try { qs->setX2Y(tmp["x2y"]); } catch (...) {}
            try { qs->setX2Z(tmp["x2z"]); } catch (...) {}
            try { qs->setY2X(tmp["y2x"]); } catch (...) {}
            try { qs->setY2Z(tmp["y2z"]); } catch (...) {}
            try { qs->setZ2X(tmp["z2x"]); } catch (...) {}
            try { qs->setZ2Y(tmp["z2y"]); } catch (...) {}
            try { qs->setXYZ(tmp["xyz"]); } catch (...) {}
            try { qs->setX2(tmp["x2"]); } catch (...) {}
            try { qs->setY2(tmp["y2"]); } catch (...) {}
            try { qs->setZ2(tmp["z2"]); } catch (...) {}
            try { qs->setXY(tmp["xy"]); } catch (...) {}
            try { qs->setXZ(tmp["xz"]); } catch (...) {}
            try { qs->setYZ(tmp["yz"]); } catch (...) {}
            try { qs->setX(tmp["x"]); } catch (...) {}
            try { qs->setY(tmp["y"]); } catch (...) {}
            try { qs->setZ(tmp["z"]); } catch (...) {}
            try { qs->setK(tmp["k"]); } catch (...) {}

            for(auto const& color : obj["colors"])
                qs->addColor(this->colorManager->getColor(color));

            qs->setTexture(getTexture(obj));
            try { qs->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(qs);

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
                polygon->addColor(this->colorManager->getColor(color));

            polygon->setTexture(getTexture(obj));

            nlohmann::json tmp = obj;
            try { polygon->setReflexion(tmp["reflection"]); } catch(...) {}

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

            nlohmann::json tmp = obj;
            for(int i = 0; i < (int)shape.size(); ++i){
                for(auto const& color : obj["colors"]) {
                    shape[i]->addColor(this->colorManager->getColor(color));
                }
                shape[i]->setTexture(getTexture(obj));

                
                try { shape[i]->setReflexion(tmp["reflection"]); } catch(...) {}

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
            cam["up"][0],
            cam["up"][1],
            cam["up"][2],
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

Config Parser::getConfig()
{
    Config config = Config();

    config.setHeight(this->j["height"]);
    config.setWidth(this->j["width"]);
    config.setAmbientColor(this->colorManager->getColor(this->j["ambient"]));
    try { config.setPrecision(this->j["precision"]); } catch(...) { config.setPrecision(1); }
    try { config.setBlur(this->j["blur"]); } catch(...) { config.setBlur(0); }
    try { config.setFilter(this->j["filter"]); } catch(...) { config.setFilter("None"); }
    try { config.setPerlinNoise(this->j["perlinNoise"]); } catch(...) { config.setPerlinNoise(false); }
    try { config.setMaxReflection(this->j["maxReflection"]); } catch(...) { config.setMaxReflection(2); }
    return config;
}
