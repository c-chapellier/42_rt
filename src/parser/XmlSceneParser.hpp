#pragma once

#include "../global.hpp"

#include "rapidxml/rapidxml.hpp"

#include "../camera/Camera.hpp"

#include "../objects/Sphere.hpp"
#include "../objects/Torus.hpp"
#include "../objects/Plane.hpp"
#include "../objects/MobiusTape.hpp"

#include "../materials/Diffuse.hpp"
#include "../materials/Metal.hpp"
#include "../materials/Mirror.hpp"
#include "../materials/Refractive.hpp"

#include "../textures/Uniform.hpp"
#include "../textures/ChessBoard.hpp"
#include "../textures/FromFile.hpp"

class XmlSceneParser
{
private:    
    std::map<const std::string, Vec3> color_map;

public:
    int height, width, precision;
    Camera camera;
    std::vector<Object *> objects;

    XmlSceneParser(const std::string &file);
    ~XmlSceneParser();

private:
    void init_color_map();
    Vec3 xml_to_vec3(rapidxml::xml_node<> *v) const;
    Vec3 xml_to_color(rapidxml::xml_node<> *v) const;
    Transform xml_to_transform(rapidxml::xml_node<> *v) const;
    Material *xml_to_material(rapidxml::xml_node<> *v) const;
    Texture *xml_to_texture(rapidxml::xml_node<> *v);
};
