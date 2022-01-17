
#include "XmlSceneParser.hpp"

XmlSceneParser::XmlSceneParser(const std::string &file)
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> *scene;

	std::ifstream theFile (file);
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	scene = doc.first_node("scene");

    this->height = std::stoi(scene->first_node("height")->value());
    this->width = std::stoi(scene->first_node("width")->value());
    this->precision = std::stoi(scene->first_node("precision")->value());

    Vec3 position = this->xml_to_vec3(scene->first_node("camera")->first_node("position"));
    Vec3 direction = this->xml_to_vec3(scene->first_node("camera")->first_node("direction"));
    Vec3 up = this->xml_to_vec3(scene->first_node("camera")->first_node("up"));
    int aperture = std::stoi(scene->first_node("camera")->first_attribute("aperture")->value());

    this->camera = Camera(
        position, direction, up,
        aperture,
        this->height * this->precision,
        this->width * this->precision
    );

    rapidxml::xml_node<> *colors = scene->first_node("colors");
	for (rapidxml::xml_node<> *color = colors->first_node("color"); color; color = color->next_sibling())
	{
        this->color_map.insert(
            std::pair<std::string, Vec3>(
                color->first_attribute("name")->value(),
                this->xml_to_color(color)
            )
        );
	}

	for (
        rapidxml::xml_node<> *object = scene->first_node("objects")->first_node();
        object;
        object = object->next_sibling())
	{
        if (std::string(object->name()) == "sphere")
        {
            this->objects.push_back(new Sphere(
                this->xml_to_transform(object),
                this->xml_to_material(object),
                this->xml_to_texture(object, object->name())
            ));
        }
        else if (std::string(object->name()) == "torus")
        {
            this->objects.push_back(new Torus(
                this->xml_to_transform(object->first_node("base")),
                this->xml_to_material(object->first_node("base")),
                this->xml_to_texture(object->first_node("base"), object->name()),
                std::stod(object->first_node("R")->value()),
                std::stod(object->first_node("r")->value())
            ));
        }
        else if (std::string(object->name()) == "plane")
        {
            this->objects.push_back(new Plane(
                this->xml_to_transform(object),
                this->xml_to_material(object),
                this->xml_to_texture(object, object->name())
            ));
        }
        else if (std::string(object->name()) == "mobiustape")
        {
            this->objects.push_back(new MobiusTape(
                this->xml_to_transform(object),
                this->xml_to_material(object),
                this->xml_to_texture(object, object->name())
            ));
        }
        else
        {
            throw "Bad object";
        }
	}
}

Vec3 XmlSceneParser::xml_to_vec3(rapidxml::xml_node<> *v) const
{
    return Vec3(
        std::stod(v->first_attribute("x")->value()),
        std::stod(v->first_attribute("y")->value()),
        std::stod(v->first_attribute("z")->value())
    );
}

Vec3 XmlSceneParser::xml_to_color(rapidxml::xml_node<> *v) const
{
    return Vec3(
        ((double)std::stoi(v->first_attribute("r")->value())) / 255,
        ((double)std::stoi(v->first_attribute("g")->value())) / 255,
        ((double)std::stoi(v->first_attribute("b")->value())) / 255
    );
}

Transform XmlSceneParser::xml_to_transform(rapidxml::xml_node<> *v) const
{
    return Transform(
        this->xml_to_vec3(v->first_node("translation")),
        this->xml_to_vec3(v->first_node("rotation")) * M_PI / 180,
        this->xml_to_vec3(v->first_node("scale"))
    );
}

Material *XmlSceneParser::xml_to_material(rapidxml::xml_node<> *v) const
{
	rapidxml::xml_node<> *material;

    material = v->first_node("diffuse");
    if (material)
        return new Diffuse();

    material = v->first_node("metal");
    if (material)
        return new Metal();

    material = v->first_node("mirror");
    if (material)
        return new Mirror();

    throw "material not good";
}

Texture *XmlSceneParser::xml_to_texture(rapidxml::xml_node<> *v, const std::string &shape)
{
	rapidxml::xml_node<> *texture;

    texture = v->first_node("uniform");
    if (texture)
        return new Uniform(color_map[texture->first_attribute("color")->value()]);

    texture = v->first_node("chessboard");
    if (texture)
    {
        return new ChessBoard(
            color_map[texture->first_attribute("color1")->value()],
            color_map[texture->first_attribute("color2")->value()],
            this->shape_map[shape]
        );
    }

    throw "texture not good";
}