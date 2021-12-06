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

void Parser::setTransform(Object *obj, nlohmann::json json)
{
    try { obj->setAlpha(json["alpha"]); } catch(...){}
    try { obj->setBeta(json["beta"]); } catch(...){}
    try { obj->setGama(json["gama"]); } catch(...){}
    try { obj->setTranslation(json["coordinates"][0], json["coordinates"][1], json["coordinates"][2]); } catch(...){}
    try { obj->setScaling(json["scaling"][0], json["scaling"][1], json["scaling"][2]); } catch(...){}
    obj->updateMatrix();
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
            setTransform(plane, tmp);
            try { plane->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(plane);

        } else if (obj["type"] == "Sphere") {
            Sphere *sphere = new Sphere(
                obj["radius"]
            );

            for (auto const& color : obj["colors"])
                sphere->addColor(this->colorManager->getColor(color));

            sphere->setTexture(getTexture(obj));
            
            nlohmann::json tmp = obj;
            setTransform(sphere, tmp);
            try { sphere->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(sphere);

        } else if (obj["type"] == "Cylinder") {
            Cylinder *cylinder = new Cylinder(
                obj["radius"]
            );

            for (auto const& color : obj["colors"])
                cylinder->addColor(this->colorManager->getColor(color));

            cylinder->setTexture(getTexture(obj));
            
            nlohmann::json tmp = obj;
            setTransform(cylinder, tmp);
            try { cylinder->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(cylinder);

        } else if (obj["type"] == "Cone") {
            Cone *cone = new Cone(
                obj["angle"]
            );

            for (auto const& color : obj["colors"])
                cone->addColor(this->colorManager->getColor(color));

            cone->setTexture(getTexture(obj));
            
            nlohmann::json tmp = obj;
            setTransform(cone, tmp);
            try { cone->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(cone);

        } else if (obj["type"] == "Circle") {
            Circle *circle = new Circle(
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
                circle->addColor(this->colorManager->getColor(color));

            circle->setTexture(getTexture(obj));

            nlohmann::json tmp = obj;
            setTransform(circle, tmp);
            try { circle->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(circle);

        } else if (obj["type"] == "MobiusTape") {
            MobiusTape *mobiusTape = new MobiusTape(
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
                mobiusTape->addColor(this->colorManager->getColor(color));

            mobiusTape->setTexture(getTexture(obj));

            nlohmann::json tmp = obj;
            setTransform(mobiusTape, tmp);
            try { mobiusTape->setReflexion(tmp["reflection"]); } catch(...) {}
            
            objects.push_back(mobiusTape);

        } else if (obj["type"] == "QuadraticSurface") {
            QuadraticSurface *quadratic = new QuadraticSurface(
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
            setTransform(quadratic, tmp);
            try { quadratic->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(quadratic);

        } else if (obj["type"] == "CubicSurface") {
            CubicSurface *cubicSurface = new CubicSurface(
                obj["coordinates"][0], 
                obj["coordinates"][1], 
                obj["coordinates"][2]
            );
            nlohmann::json tmp = obj;
            setTransform(cubicSurface, tmp);
            try { cubicSurface->setX3(tmp["x3"]); } catch (...) {}
            try { cubicSurface->setY3(tmp["y3"]); } catch (...) {}
            try { cubicSurface->setZ3(tmp["z3"]); } catch (...) {}
            try { cubicSurface->setX2Y(tmp["x2y"]); } catch (...) {}
            try { cubicSurface->setX2Z(tmp["x2z"]); } catch (...) {}
            try { cubicSurface->setY2X(tmp["y2x"]); } catch (...) {}
            try { cubicSurface->setY2Z(tmp["y2z"]); } catch (...) {}
            try { cubicSurface->setZ2X(tmp["z2x"]); } catch (...) {}
            try { cubicSurface->setZ2Y(tmp["z2y"]); } catch (...) {}
            try { cubicSurface->setXYZ(tmp["xyz"]); } catch (...) {}
            try { cubicSurface->setX2(tmp["x2"]); } catch (...) {}
            try { cubicSurface->setY2(tmp["y2"]); } catch (...) {}
            try { cubicSurface->setZ2(tmp["z2"]); } catch (...) {}
            try { cubicSurface->setXY(tmp["xy"]); } catch (...) {}
            try { cubicSurface->setXZ(tmp["xz"]); } catch (...) {}
            try { cubicSurface->setYZ(tmp["yz"]); } catch (...) {}
            try { cubicSurface->setX(tmp["x"]); } catch (...) {}
            try { cubicSurface->setY(tmp["y"]); } catch (...) {}
            try { cubicSurface->setZ(tmp["z"]); } catch (...) {}
            try { cubicSurface->setK(tmp["k"]); } catch (...) {}

            for(auto const& color : obj["colors"])
                cubicSurface->addColor(this->colorManager->getColor(color));

            cubicSurface->setTexture(getTexture(obj));
            try { cubicSurface->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(cubicSurface);

        } else if (obj["type"] == "QuarticSurface") {
            QuarticSurface *quarticSurface = new QuarticSurface(
                obj["coordinates"][0], 
                obj["coordinates"][1], 
                obj["coordinates"][2]
            );
            nlohmann::json tmp = obj;
            setTransform(quarticSurface, tmp);
            try { quarticSurface->setX4(tmp["x4"]); } catch (...) {}
            try { quarticSurface->setY4(tmp["y4"]); } catch (...) {}
            try { quarticSurface->setZ4(tmp["z4"]); } catch (...) {}
            try { quarticSurface->setX3Y(tmp["x3y"]); } catch (...) {}
            try { quarticSurface->setX3Z(tmp["x3z"]); } catch (...) {}
            try { quarticSurface->setY3X(tmp["y3x"]); } catch (...) {}
            try { quarticSurface->setY3Z(tmp["y3z"]); } catch (...) {}
            try { quarticSurface->setZ3X(tmp["z3x"]); } catch (...) {}
            try { quarticSurface->setZ3Y(tmp["z3y"]); } catch (...) {}
            try { quarticSurface->setX2YZ(tmp["x2yz"]); } catch (...) {}
            try { quarticSurface->setY2XZ(tmp["y2xz"]); } catch (...) {}
            try { quarticSurface->setZ2XY(tmp["z2yx"]); } catch (...) {}
            try { quarticSurface->setX2Y2(tmp["x2y2"]); } catch (...) {}
            try { quarticSurface->setX2Z2(tmp["x2z2"]); } catch (...) {}
            try { quarticSurface->setY2Z2(tmp["y2z2"]); } catch (...) {}
            try { quarticSurface->setX3(tmp["x3"]); } catch (...) {}
            try { quarticSurface->setY3(tmp["y3"]); } catch (...) {}
            try { quarticSurface->setZ3(tmp["z3"]); } catch (...) {}
            try { quarticSurface->setX2Y(tmp["x2y"]); } catch (...) {}
            try { quarticSurface->setX2Z(tmp["x2z"]); } catch (...) {}
            try { quarticSurface->setY2X(tmp["y2x"]); } catch (...) {}
            try { quarticSurface->setY2Z(tmp["y2z"]); } catch (...) {}
            try { quarticSurface->setZ2X(tmp["z2x"]); } catch (...) {}
            try { quarticSurface->setZ2Y(tmp["z2y"]); } catch (...) {}
            try { quarticSurface->setXYZ(tmp["xyz"]); } catch (...) {}
            try { quarticSurface->setX2(tmp["x2"]); } catch (...) {}
            try { quarticSurface->setY2(tmp["y2"]); } catch (...) {}
            try { quarticSurface->setZ2(tmp["z2"]); } catch (...) {}
            try { quarticSurface->setXY(tmp["xy"]); } catch (...) {}
            try { quarticSurface->setXZ(tmp["xz"]); } catch (...) {}
            try { quarticSurface->setYZ(tmp["yz"]); } catch (...) {}
            try { quarticSurface->setX(tmp["x"]); } catch (...) {}
            try { quarticSurface->setY(tmp["y"]); } catch (...) {}
            try { quarticSurface->setZ(tmp["z"]); } catch (...) {}
            try { quarticSurface->setK(tmp["k"]); } catch (...) {}

            for(auto const& color : obj["colors"])
                quarticSurface->addColor(this->colorManager->getColor(color));

            quarticSurface->setTexture(getTexture(obj));
            try { quarticSurface->setReflexion(tmp["reflection"]); } catch(...) {}

            objects.push_back(quarticSurface);

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
            setTransform(polygon, tmp);
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
