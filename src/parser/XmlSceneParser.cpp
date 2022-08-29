
#include "XmlSceneParser.hpp"

XmlSceneParser::XmlSceneParser(const std::string &file)
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> *scene;

	std::ifstream theFile(file);
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());

    if (buffer.size() == 0) throw "File est empty";
    
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

    this->init_color_map();

    rapidxml::xml_node<> *colors = scene->first_node("colors");
	for (rapidxml::xml_node<> *color = colors->first_node("color"); color; color = color->next_sibling())
	{
        this->color_map[color->first_attribute("name")->value()] = this->xml_to_color(color);
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
                this->xml_to_texture(object)
            ));
        }
        else if (std::string(object->name()) == "torus")
        {
            this->objects.push_back(new Torus(
                this->xml_to_transform(object->first_node("base")),
                this->xml_to_material(object->first_node("base")),
                this->xml_to_texture(object->first_node("base")),
                std::stod(object->first_node("R")->value()),
                std::stod(object->first_node("r")->value())
            ));
        }
        else if (std::string(object->name()) == "plane")
        {
            this->objects.push_back(new Plane(
                this->xml_to_transform(object),
                this->xml_to_material(object),
                this->xml_to_texture(object)
            ));
        }
        else if (std::string(object->name()) == "mobiustape")
        {
            this->objects.push_back(new MobiusTape(
                this->xml_to_transform(object),
                this->xml_to_material(object),
                this->xml_to_texture(object)
            ));
        }
        else if (std::string(object->name()) == "box")
        {
            this->objects.push_back(new Box(
                this->xml_to_transform(object),
                this->xml_to_material(object),
                this->xml_to_texture(object)
            ));
        }
        else if (std::string(object->name()) == "tanglecube")
        {
            this->objects.push_back(new TangleCube(
                this->xml_to_transform(object),
                this->xml_to_material(object),
                this->xml_to_texture(object)
            ));
        }
        else if (std::string(object->name()) == "fresnelsurface")
        {
            this->objects.push_back(new FresnelElasticitySurface(
                this->xml_to_transform(object->first_node("base")),
                this->xml_to_material(object->first_node("base")),
                this->xml_to_texture(object->first_node("base")),
                std::stod(object->first_node("a")->value()),
                std::stod(object->first_node("b")->value()),
                std::stod(object->first_node("c")->value())
            ));
        }
        else if (std::string(object->name()) == "dupincyclide")
        {
            this->objects.push_back(new DupinCyclide(
                this->xml_to_transform(object->first_node("base")),
                this->xml_to_material(object->first_node("base")),
                this->xml_to_texture(object->first_node("base")),
                std::stod(object->first_node("a")->value()),
                std::stod(object->first_node("b")->value()),
                std::stod(object->first_node("c")->value()),
                std::stod(object->first_node("d")->value())
            ));
        }
        else
        {
            throw "Bad object";
        }
	}
}

XmlSceneParser::~XmlSceneParser()
{
    for (auto object: this->objects) delete object;
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

    material = v->first_node("refractive");
    if (material)
        return new Refractive(std::stod(material->first_attribute("n")->value()));

    throw "material not good";
}

Texture *XmlSceneParser::xml_to_texture(rapidxml::xml_node<> *v)
{
	rapidxml::xml_node<> *texture;

    texture = v->first_node("uniform");
    if (texture)
        return new Uniform(color_map[texture->first_attribute("color")->value()]);

    texture = v->first_node("texturefromfile");
    if (texture)
    {
        return new FromFile(
            texture->first_attribute("filename")->value()
        );
    }

    texture = v->first_node("chessboard");
    if (texture)
    {
        return new ChessBoard(
            color_map[texture->first_attribute("color1")->value()],
            color_map[texture->first_attribute("color2")->value()]
        );
    }

    throw "texture not good";
}

void XmlSceneParser::init_color_map()
{
    this->color_map["air_force_blue_raf"] = Vec3(93. / 255, 138. / 255, 168. / 255);
    this->color_map["air_force_blue_usaf"] = Vec3(0. / 255, 48. / 255, 143. / 255);
    this->color_map["air_superiority_blue"] = Vec3(114. / 255, 160. / 255, 193. / 255);
    this->color_map["alabama_crimson"] = Vec3(163. / 255, 38. / 255, 56. / 255);
    this->color_map["alice_blue"] = Vec3(240. / 255, 248. / 255, 255. / 255);
    this->color_map["alizarin_crimson"] = Vec3(227. / 255, 38. / 255, 54. / 255);
    this->color_map["alloy_orange"] = Vec3(196. / 255, 98. / 255, 16. / 255);
    this->color_map["almond"] = Vec3(239. / 255, 222. / 255, 205. / 255);
    this->color_map["amaranth"] = Vec3(229. / 255, 43. / 255, 80. / 255);
    this->color_map["amber"] = Vec3(255. / 255, 191. / 255, 0. / 255);
    this->color_map["amber_sae_ece"] = Vec3(255. / 255, 126. / 255, 0. / 255);
    this->color_map["american_rose"] = Vec3(255. / 255, 3. / 255, 62. / 255);
    this->color_map["amethyst"] = Vec3(153. / 255, 102. / 255, 204. / 255);
    this->color_map["android_green"] = Vec3(164. / 255, 198. / 255, 57. / 255);
    this->color_map["anti_flash_white"] = Vec3(242. / 255, 243. / 255, 244. / 255);
    this->color_map["antique_brass"] = Vec3(205. / 255, 149. / 255, 117. / 255);
    this->color_map["antique_fuchsia"] = Vec3(145. / 255, 92. / 255, 131. / 255);
    this->color_map["antique_ruby"] = Vec3(132. / 255, 27. / 255, 45. / 255);
    this->color_map["antique_white"] = Vec3(250. / 255, 235. / 255, 215. / 255);
    this->color_map["ao_english"] = Vec3(0. / 255, 128. / 255, 0. / 255);
    this->color_map["apple_green"] = Vec3(141. / 255, 182. / 255, 0. / 255);
    this->color_map["apricot"] = Vec3(251. / 255, 206. / 255, 177. / 255);
    this->color_map["aqua"] = Vec3(0. / 255, 255. / 255, 255. / 255);
    this->color_map["aquamarine"] = Vec3(127. / 255, 255. / 255, 212. / 255);
    this->color_map["army_green"] = Vec3(75. / 255, 83. / 255, 32. / 255);
    this->color_map["arsenic"] = Vec3(59. / 255, 68. / 255, 75. / 255);
    this->color_map["arylide_yellow"] = Vec3(233. / 255, 214. / 255, 107. / 255);
    this->color_map["ash_grey"] = Vec3(178. / 255, 190. / 255, 181. / 255);
    this->color_map["asparagus"] = Vec3(135. / 255, 169. / 255, 107. / 255);
    this->color_map["atomic_tangerine"] = Vec3(255. / 255, 153. / 255, 102. / 255);
    this->color_map["auburn"] = Vec3(165. / 255, 42. / 255, 42. / 255);
    this->color_map["aureolin"] = Vec3(253. / 255, 238. / 255, 0. / 255);
    this->color_map["aurometalsaurus"] = Vec3(110. / 255, 127. / 255, 128. / 255);
    this->color_map["avocado"] = Vec3(86. / 255, 130. / 255, 3. / 255);
    this->color_map["azure"] = Vec3(0. / 255, 127. / 255, 255. / 255);
    this->color_map["azure_mist_web"] = Vec3(240. / 255, 255. / 255, 255. / 255);
    this->color_map["baby_blue"] = Vec3(137. / 255, 207. / 255, 240. / 255);
    this->color_map["baby_blue_eyes"] = Vec3(161. / 255, 202. / 255, 241. / 255);
    this->color_map["baby_pink"] = Vec3(244. / 255, 194. / 255, 194. / 255);
    this->color_map["ball_blue"] = Vec3(33. / 255, 171. / 255, 205. / 255);
    this->color_map["banana_mania"] = Vec3(250. / 255, 231. / 255, 181. / 255);
    this->color_map["banana_yellow"] = Vec3(255. / 255, 225. / 255, 53. / 255);
    this->color_map["barn_red"] = Vec3(124. / 255, 10. / 255, 2. / 255);
    this->color_map["battleship_grey"] = Vec3(132. / 255, 132. / 255, 130. / 255);
    this->color_map["bazaar"] = Vec3(152. / 255, 119. / 255, 123. / 255);
    this->color_map["beau_blue"] = Vec3(188. / 255, 212. / 255, 230. / 255);
    this->color_map["beaver"] = Vec3(159. / 255, 129. / 255, 112. / 255);
    this->color_map["beige"] = Vec3(245. / 255, 245. / 255, 220. / 255);
    this->color_map["big_dip_o_ruby"] = Vec3(156. / 255, 37. / 255, 66. / 255);
    this->color_map["bisque"] = Vec3(255. / 255, 228. / 255, 196. / 255);
    this->color_map["bistre"] = Vec3(61. / 255, 43. / 255, 31. / 255);
    this->color_map["bittersweet"] = Vec3(254. / 255, 111. / 255, 94. / 255);
    this->color_map["bittersweet_shimmer"] = Vec3(191. / 255, 79. / 255, 81. / 255);
    this->color_map["black"] = Vec3(0. / 255, 0. / 255, 0. / 255);
    this->color_map["black_bean"] = Vec3(61. / 255, 12. / 255, 2. / 255);
    this->color_map["black_leather_jacket"] = Vec3(37. / 255, 53. / 255, 41. / 255);
    this->color_map["black_olive"] = Vec3(59. / 255, 60. / 255, 54. / 255);
    this->color_map["blanched_almond"] = Vec3(255. / 255, 235. / 255, 205. / 255);
    this->color_map["blast_off_bronze"] = Vec3(165. / 255, 113. / 255, 100. / 255);
    this->color_map["bleu_de_france"] = Vec3(49. / 255, 140. / 255, 231. / 255);
    this->color_map["blizzard_blue"] = Vec3(172. / 255, 229. / 255, 238. / 255);
    this->color_map["blond"] = Vec3(250. / 255, 240. / 255, 190. / 255);
    this->color_map["blue"] = Vec3(0. / 255, 0. / 255, 255. / 255);
    this->color_map["blue_bell"] = Vec3(162. / 255, 162. / 255, 208. / 255);
    this->color_map["blue_crayola"] = Vec3(31. / 255, 117. / 255, 254. / 255);
    this->color_map["blue_gray"] = Vec3(102. / 255, 153. / 255, 204. / 255);
    this->color_map["blue_green"] = Vec3(13. / 255, 152. / 255, 186. / 255);
    this->color_map["blue_munsell"] = Vec3(0. / 255, 147. / 255, 175. / 255);
    this->color_map["blue_ncs"] = Vec3(0. / 255, 135. / 255, 189. / 255);
    this->color_map["blue_pigment"] = Vec3(51. / 255, 51. / 255, 153. / 255);
    this->color_map["blue_ryb"] = Vec3(2. / 255, 71. / 255, 254. / 255);
    this->color_map["blue_sapphire"] = Vec3(18. / 255, 97. / 255, 128. / 255);
    this->color_map["blue_violet"] = Vec3(138. / 255, 43. / 255, 226. / 255);
    this->color_map["blush"] = Vec3(222. / 255, 93. / 255, 131. / 255);
    this->color_map["bole"] = Vec3(121. / 255, 68. / 255, 59. / 255);
    this->color_map["bondi_blue"] = Vec3(0. / 255, 149. / 255, 182. / 255);
    this->color_map["bone"] = Vec3(227. / 255, 218. / 255, 201. / 255);
    this->color_map["boston_university_red"] = Vec3(204. / 255, 0. / 255, 0. / 255);
    this->color_map["bottle_green"] = Vec3(0. / 255, 106. / 255, 78. / 255);
    this->color_map["boysenberry"] = Vec3(135. / 255, 50. / 255, 96. / 255);
    this->color_map["brandeis_blue"] = Vec3(0. / 255, 112. / 255, 255. / 255);
    this->color_map["brass"] = Vec3(181. / 255, 166. / 255, 66. / 255);
    this->color_map["brick_red"] = Vec3(203. / 255, 65. / 255, 84. / 255);
    this->color_map["bright_cerulean"] = Vec3(29. / 255, 172. / 255, 214. / 255);
    this->color_map["bright_green"] = Vec3(102. / 255, 255. / 255, 0. / 255);
    this->color_map["bright_lavender"] = Vec3(191. / 255, 148. / 255, 228. / 255);
    this->color_map["bright_maroon"] = Vec3(195. / 255, 33. / 255, 72. / 255);
    this->color_map["bright_pink"] = Vec3(255. / 255, 0. / 255, 127. / 255);
    this->color_map["bright_turquoise"] = Vec3(8. / 255, 232. / 255, 222. / 255);
    this->color_map["bright_ube"] = Vec3(209. / 255, 159. / 255, 232. / 255);
    this->color_map["brilliant_lavender"] = Vec3(244. / 255, 187. / 255, 255. / 255);
    this->color_map["brilliant_rose"] = Vec3(255. / 255, 85. / 255, 163. / 255);
    this->color_map["brink_pink"] = Vec3(251. / 255, 96. / 255, 127. / 255);
    this->color_map["british_racing_green"] = Vec3(0. / 255, 66. / 255, 37. / 255);
    this->color_map["bronze"] = Vec3(205. / 255, 127. / 255, 50. / 255);
    this->color_map["brown_traditional"] = Vec3(150. / 255, 75. / 255, 0. / 255);
    this->color_map["brown_web"] = Vec3(165. / 255, 42. / 255, 42. / 255);
    this->color_map["bubble_gum"] = Vec3(255. / 255, 193. / 255, 204. / 255);
    this->color_map["bubbles"] = Vec3(231. / 255, 254. / 255, 255. / 255);
    this->color_map["buff"] = Vec3(240. / 255, 220. / 255, 130. / 255);
    this->color_map["bulgarian_rose"] = Vec3(72. / 255, 6. / 255, 7. / 255);
    this->color_map["burgundy"] = Vec3(128. / 255, 0. / 255, 32. / 255);
    this->color_map["burlywood"] = Vec3(222. / 255, 184. / 255, 135. / 255);
    this->color_map["burnt_orange"] = Vec3(204. / 255, 85. / 255, 0. / 255);
    this->color_map["burnt_sienna"] = Vec3(233. / 255, 116. / 255, 81. / 255);
    this->color_map["byzantine"] = Vec3(189. / 255, 51. / 255, 164. / 255);
    this->color_map["burnt_umber"] = Vec3(138. / 255, 51. / 255, 36. / 255);
    this->color_map["cadet"] = Vec3(83. / 255, 104. / 255, 114. / 255);
    this->color_map["byzantium"] = Vec3(112. / 255, 41. / 255, 99. / 255);
    this->color_map["cadet_grey"] = Vec3(145. / 255, 163. / 255, 176. / 255);
    this->color_map["cadet_blue"] = Vec3(95. / 255, 158. / 255, 160. / 255);
    this->color_map["cadmium_orange"] = Vec3(237. / 255, 135. / 255, 45. / 255);
    this->color_map["cadmium_green"] = Vec3(0. / 255, 107. / 255, 60. / 255);
    this->color_map["cadmium_yellow"] = Vec3(255. / 255, 246. / 255, 0. / 255);
    this->color_map["cadmium_red"] = Vec3(227. / 255, 0. / 255, 34. / 255);
    this->color_map["caf_noir"] = Vec3(75. / 255, 54. / 255, 33. / 255);
    this->color_map["caf_au_lait"] = Vec3(166. / 255, 123. / 255, 91. / 255);
    this->color_map["cambridge_blue"] = Vec3(163. / 255, 193. / 255, 173. / 255);
    this->color_map["cal_poly_green"] = Vec3(30. / 255, 77. / 255, 43. / 255);
    this->color_map["cameo_pink"] = Vec3(239. / 255, 187. / 255, 204. / 255);
    this->color_map["camel"] = Vec3(193. / 255, 154. / 255, 107. / 255);
    this->color_map["canary_yellow"] = Vec3(255. / 255, 239. / 255, 0. / 255);
    this->color_map["camouflage_green"] = Vec3(120. / 255, 134. / 255, 107. / 255);
    this->color_map["candy_pink"] = Vec3(228. / 255, 113. / 255, 122. / 255);
    this->color_map["candy_apple_red"] = Vec3(255. / 255, 8. / 255, 0. / 255);
    this->color_map["caput_mortuum"] = Vec3(89. / 255, 39. / 255, 32. / 255);
    this->color_map["capri"] = Vec3(0. / 255, 191. / 255, 255. / 255);
    this->color_map["caribbean_green"] = Vec3(0. / 255, 204. / 255, 153. / 255);
    this->color_map["cardinal"] = Vec3(196. / 255, 30. / 255, 58. / 255);
    this->color_map["carmine_m_p"] = Vec3(215. / 255, 0. / 255, 64. / 255);
    this->color_map["carmine"] = Vec3(150. / 255, 0. / 255, 24. / 255);
    this->color_map["carmine_red"] = Vec3(255. / 255, 0. / 255, 56. / 255);
    this->color_map["carmine_pink"] = Vec3(235. / 255, 76. / 255, 66. / 255);
    this->color_map["carnelian"] = Vec3(179. / 255, 27. / 255, 27. / 255);
    this->color_map["carnation_pink"] = Vec3(255. / 255, 166. / 255, 201. / 255);
    this->color_map["carrot_orange"] = Vec3(237. / 255, 145. / 255, 33. / 255);
    this->color_map["carolina_blue"] = Vec3(153. / 255, 186. / 255, 221. / 255);
    this->color_map["ceil"] = Vec3(146. / 255, 161. / 255, 207. / 255);
    this->color_map["catalina_blue"] = Vec3(6. / 255, 42. / 255, 120. / 255);
    this->color_map["celadon_blue"] = Vec3(0. / 255, 123. / 255, 167. / 255);
    this->color_map["celadon"] = Vec3(172. / 255, 225. / 255, 175. / 255);
    this->color_map["celeste_colour"] = Vec3(178. / 255, 255. / 255, 255. / 255);
    this->color_map["celadon_green"] = Vec3(47. / 255, 132. / 255, 124. / 255);
    this->color_map["cerise"] = Vec3(222. / 255, 49. / 255, 99. / 255);
    this->color_map["celestial_blue"] = Vec3(73. / 255, 151. / 255, 208. / 255);
    this->color_map["cerulean"] = Vec3(0. / 255, 123. / 255, 167. / 255);
    this->color_map["cerise_pink"] = Vec3(236. / 255, 59. / 255, 131. / 255);
    this->color_map["cerulean_frost"] = Vec3(109. / 255, 155. / 255, 195. / 255);
    this->color_map["cerulean_blue"] = Vec3(42. / 255, 82. / 255, 190. / 255);
    this->color_map["cg_red"] = Vec3(224. / 255, 60. / 255, 49. / 255);
    this->color_map["cg_blue"] = Vec3(0. / 255, 122. / 255, 165. / 255);
    this->color_map["champagne"] = Vec3(250. / 255, 214. / 255, 165. / 255);
    this->color_map["chamoisee"] = Vec3(160. / 255, 120. / 255, 90. / 255);
    this->color_map["charm_pink"] = Vec3(230. / 255, 143. / 255, 172. / 255);
    this->color_map["charcoal"] = Vec3(54. / 255, 69. / 255, 79. / 255);
    this->color_map["chartreuse_web"] = Vec3(127. / 255, 255. / 255, 0. / 255);
    this->color_map["chartreuse_traditional"] = Vec3(223. / 255, 255. / 255, 0. / 255);
    this->color_map["cherry_blossom_pink"] = Vec3(255. / 255, 183. / 255, 197. / 255);
    this->color_map["cherry"] = Vec3(222. / 255, 49. / 255, 99. / 255);
    this->color_map["china_pink"] = Vec3(222. / 255, 111. / 255, 161. / 255);
    this->color_map["chestnut"] = Vec3(205. / 255, 92. / 255, 92. / 255);
    this->color_map["chinese_red"] = Vec3(170. / 255, 56. / 255, 30. / 255);
    this->color_map["china_rose"] = Vec3(168. / 255, 81. / 255, 110. / 255);
    this->color_map["chocolate_web"] = Vec3(210. / 255, 105. / 255, 30. / 255);
    this->color_map["chocolate_traditional"] = Vec3(123. / 255, 63. / 255, 0. / 255);
    this->color_map["cinereous"] = Vec3(152. / 255, 129. / 255, 123. / 255);
    this->color_map["chrome_yellow"] = Vec3(255. / 255, 167. / 255, 0. / 255);
    this->color_map["cinnamon"] = Vec3(210. / 255, 105. / 255, 30. / 255);
    this->color_map["cinnabar"] = Vec3(227. / 255, 66. / 255, 52. / 255);
    this->color_map["classic_rose"] = Vec3(251. / 255, 204. / 255, 231. / 255);
    this->color_map["citrine"] = Vec3(228. / 255, 208. / 255, 10. / 255);
    this->color_map["cocoa_brown"] = Vec3(210. / 255, 105. / 255, 30. / 255);
    this->color_map["cobalt"] = Vec3(0. / 255, 71. / 255, 171. / 255);
    this->color_map["columbia_blue"] = Vec3(155. / 255, 221. / 255, 255. / 255);
    this->color_map["coffee"] = Vec3(111. / 255, 78. / 255, 55. / 255);
    this->color_map["cool_black"] = Vec3(0. / 255, 46. / 255, 99. / 255);
    this->color_map["congo_pink"] = Vec3(248. / 255, 131. / 255, 121. / 255);
    this->color_map["copper"] = Vec3(184. / 255, 115. / 255, 51. / 255);
    this->color_map["cool_grey"] = Vec3(140. / 255, 146. / 255, 172. / 255);
    this->color_map["copper_penny"] = Vec3(173. / 255, 111. / 255, 105. / 255);
    this->color_map["copper_crayola"] = Vec3(218. / 255, 138. / 255, 103. / 255);
    this->color_map["copper_rose"] = Vec3(153. / 255, 102. / 255, 102. / 255);
    this->color_map["copper_red"] = Vec3(203. / 255, 109. / 255, 81. / 255);
    this->color_map["coral"] = Vec3(255. / 255, 127. / 255, 80. / 255);
    this->color_map["coquelicot"] = Vec3(255. / 255, 56. / 255, 0. / 255);
    this->color_map["coral_red"] = Vec3(255. / 255, 64. / 255, 64. / 255);
    this->color_map["coral_pink"] = Vec3(248. / 255, 131. / 255, 121. / 255);
    this->color_map["corn"] = Vec3(251. / 255, 236. / 255, 93. / 255);
    this->color_map["cordovan"] = Vec3(137. / 255, 63. / 255, 69. / 255);
    this->color_map["cornflower_blue"] = Vec3(100. / 255, 149. / 255, 237. / 255);
    this->color_map["cornell_red"] = Vec3(179. / 255, 27. / 255, 27. / 255);
    this->color_map["cosmic_latte"] = Vec3(255. / 255, 248. / 255, 231. / 255);
    this->color_map["cornsilk"] = Vec3(255. / 255, 248. / 255, 220. / 255);
    this->color_map["cream"] = Vec3(255. / 255, 253. / 255, 208. / 255);
    this->color_map["cotton_candy"] = Vec3(255. / 255, 188. / 255, 217. / 255);
    this->color_map["crimson_glory"] = Vec3(190. / 255, 0. / 255, 50. / 255);
    this->color_map["crimson"] = Vec3(220. / 255, 20. / 255, 60. / 255);
    this->color_map["cyan_process"] = Vec3(0. / 255, 183. / 255, 235. / 255);
    this->color_map["cyan"] = Vec3(0. / 255, 255. / 255, 255. / 255);
    this->color_map["dandelion"] = Vec3(240. / 255, 225. / 255, 48. / 255);
    this->color_map["daffodil"] = Vec3(255. / 255, 255. / 255, 49. / 255);
    this->color_map["dark_brown"] = Vec3(101. / 255, 67. / 255, 33. / 255);
    this->color_map["dark_blue"] = Vec3(0. / 255, 0. / 255, 139. / 255);
    this->color_map["dark_candy_apple_red"] = Vec3(164. / 255, 0. / 255, 0. / 255);
    this->color_map["dark_byzantium"] = Vec3(93. / 255, 57. / 255, 84. / 255);
    this->color_map["dark_chestnut"] = Vec3(152. / 255, 105. / 255, 96. / 255);
    this->color_map["dark_cerulean"] = Vec3(8. / 255, 69. / 255, 126. / 255);
    this->color_map["dark_cyan"] = Vec3(0. / 255, 139. / 255, 139. / 255);
    this->color_map["dark_coral"] = Vec3(205. / 255, 91. / 255, 69. / 255);
    this->color_map["dark_goldenrod"] = Vec3(184. / 255, 134. / 255, 11. / 255);
    this->color_map["dark_electric_blue"] = Vec3(83. / 255, 104. / 255, 120. / 255);
    this->color_map["dark_green"] = Vec3(1. / 255, 50. / 255, 32. / 255);
    this->color_map["dark_gray"] = Vec3(169. / 255, 169. / 255, 169. / 255);
    this->color_map["dark_jungle_green"] = Vec3(26. / 255, 36. / 255, 33. / 255);
    this->color_map["dark_imperial_blue"] = Vec3(0. / 255, 65. / 255, 106. / 255);
    this->color_map["dark_lava"] = Vec3(72. / 255, 60. / 255, 50. / 255);
    this->color_map["dark_khaki"] = Vec3(189. / 255, 183. / 255, 107. / 255);
    this->color_map["dark_magenta"] = Vec3(139. / 255, 0. / 255, 139. / 255);
    this->color_map["dark_lavender"] = Vec3(115. / 255, 79. / 255, 150. / 255);
    this->color_map["dark_olive_green"] = Vec3(85. / 255, 107. / 255, 47. / 255);
    this->color_map["dark_midnight_blue"] = Vec3(0. / 255, 51. / 255, 102. / 255);
    this->color_map["dark_orchid"] = Vec3(153. / 255, 50. / 255, 204. / 255);
    this->color_map["dark_orange"] = Vec3(255. / 255, 140. / 255, 0. / 255);
    this->color_map["dark_pastel_green"] = Vec3(3. / 255, 192. / 255, 60. / 255);
    this->color_map["dark_pastel_blue"] = Vec3(119. / 255, 158. / 255, 203. / 255);
    this->color_map["dark_pastel_red"] = Vec3(194. / 255, 59. / 255, 34. / 255);
    this->color_map["dark_pastel_purple"] = Vec3(150. / 255, 111. / 255, 214. / 255);
    this->color_map["dark_powder_blue"] = Vec3(0. / 255, 51. / 255, 153. / 255);
    this->color_map["dark_pink"] = Vec3(231. / 255, 84. / 255, 128. / 255);
    this->color_map["dark_red"] = Vec3(139. / 255, 0. / 255, 0. / 255);
    this->color_map["dark_raspberry"] = Vec3(135. / 255, 38. / 255, 87. / 255);
    this->color_map["dark_scarlet"] = Vec3(86. / 255, 3. / 255, 25. / 255);
    this->color_map["dark_salmon"] = Vec3(233. / 255, 150. / 255, 122. / 255);
    this->color_map["dark_sienna"] = Vec3(60. / 255, 20. / 255, 20. / 255);
    this->color_map["dark_sea_green"] = Vec3(143. / 255, 188. / 255, 143. / 255);
    this->color_map["dark_slate_gray"] = Vec3(47. / 255, 79. / 255, 79. / 255);
    this->color_map["dark_slate_blue"] = Vec3(72. / 255, 61. / 255, 139. / 255);
    this->color_map["dark_tan"] = Vec3(145. / 255, 129. / 255, 81. / 255);
    this->color_map["dark_spring_green"] = Vec3(23. / 255, 114. / 255, 69. / 255);
    this->color_map["dark_taupe"] = Vec3(72. / 255, 60. / 255, 50. / 255);
    this->color_map["dark_tangerine"] = Vec3(255. / 255, 168. / 255, 18. / 255);
    this->color_map["dark_turquoise"] = Vec3(0. / 255, 206. / 255, 209. / 255);
    this->color_map["dark_terra_cotta"] = Vec3(204. / 255, 78. / 255, 92. / 255);
    this->color_map["dark_yellow"] = Vec3(155. / 255, 135. / 255, 12. / 255);
    this->color_map["dark_violet"] = Vec3(148. / 255, 0. / 255, 211. / 255);
    this->color_map["davy_s_grey"] = Vec3(85. / 255, 85. / 255, 85. / 255);
    this->color_map["dartmouth_green"] = Vec3(0. / 255, 112. / 255, 60. / 255);
    this->color_map["deep_carmine"] = Vec3(169. / 255, 32. / 255, 62. / 255);
    this->color_map["debian_red"] = Vec3(215. / 255, 10. / 255, 83. / 255);
    this->color_map["deep_carrot_orange"] = Vec3(233. / 255, 105. / 255, 44. / 255);
    this->color_map["deep_carmine_pink"] = Vec3(239. / 255, 48. / 255, 56. / 255);
    this->color_map["deep_champagne"] = Vec3(250. / 255, 214. / 255, 165. / 255);
    this->color_map["deep_cerise"] = Vec3(218. / 255, 50. / 255, 135. / 255);
    this->color_map["deep_coffee"] = Vec3(112. / 255, 66. / 255, 65. / 255);
    this->color_map["deep_chestnut"] = Vec3(185. / 255, 78. / 255, 72. / 255);
    this->color_map["deep_jungle_green"] = Vec3(0. / 255, 75. / 255, 73. / 255);
    this->color_map["deep_fuchsia"] = Vec3(193. / 255, 84. / 255, 193. / 255);
    this->color_map["deep_magenta"] = Vec3(204. / 255, 0. / 255, 204. / 255);
    this->color_map["deep_lilac"] = Vec3(153. / 255, 85. / 255, 187. / 255);
    this->color_map["deep_pink"] = Vec3(255. / 255, 20. / 255, 147. / 255);
    this->color_map["deep_peach"] = Vec3(255. / 255, 203. / 255, 164. / 255);
    this->color_map["deep_saffron"] = Vec3(255. / 255, 153. / 255, 51. / 255);
    this->color_map["deep_ruby"] = Vec3(132. / 255, 63. / 255, 91. / 255);
    this->color_map["deep_tuscan_red"] = Vec3(102. / 255, 66. / 255, 77. / 255);
    this->color_map["deep_sky_blue"] = Vec3(0. / 255, 191. / 255, 255. / 255);
    this->color_map["desert"] = Vec3(193. / 255, 154. / 255, 107. / 255);
    this->color_map["denim"] = Vec3(21. / 255, 96. / 255, 189. / 255);
    this->color_map["dim_gray"] = Vec3(105. / 255, 105. / 255, 105. / 255);
    this->color_map["desert_sand"] = Vec3(237. / 255, 201. / 255, 175. / 255);
    this->color_map["dogwood_rose"] = Vec3(215. / 255, 24. / 255, 104. / 255);
    this->color_map["dodger_blue"] = Vec3(30. / 255, 144. / 255, 255. / 255);
    this->color_map["drab"] = Vec3(150. / 255, 113. / 255, 23. / 255);
    this->color_map["dollar_bill"] = Vec3(133. / 255, 187. / 255, 101. / 255);
    this->color_map["earth_yellow"] = Vec3(225. / 255, 169. / 255, 95. / 255);
    this->color_map["duke_blue"] = Vec3(0. / 255, 0. / 255, 156. / 255);
    this->color_map["ecru"] = Vec3(194. / 255, 178. / 255, 128. / 255);
    this->color_map["ebony"] = Vec3(85. / 255, 93. / 255, 80. / 255);
    this->color_map["eggshell"] = Vec3(240. / 255, 234. / 255, 214. / 255);
    this->color_map["eggplant"] = Vec3(97. / 255, 64. / 255, 81. / 255);
    this->color_map["electric_blue"] = Vec3(125. / 255, 249. / 255, 255. / 255);
    this->color_map["egyptian_blue"] = Vec3(16. / 255, 52. / 255, 166. / 255);
    this->color_map["electric_cyan"] = Vec3(0. / 255, 255. / 255, 255. / 255);
    this->color_map["electric_crimson"] = Vec3(255. / 255, 0. / 255, 63. / 255);
    this->color_map["electric_indigo"] = Vec3(111. / 255, 0. / 255, 255. / 255);
    this->color_map["electric_green"] = Vec3(0. / 255, 255. / 255, 0. / 255);
    this->color_map["electric_lime"] = Vec3(204. / 255, 255. / 255, 0. / 255);
    this->color_map["electric_lavender"] = Vec3(244. / 255, 187. / 255, 255. / 255);
    this->color_map["electric_ultramarine"] = Vec3(63. / 255, 0. / 255, 255. / 255);
    this->color_map["electric_purple"] = Vec3(191. / 255, 0. / 255, 255. / 255);
    this->color_map["electric_yellow"] = Vec3(255. / 255, 255. / 255, 0. / 255);
    this->color_map["electric_violet"] = Vec3(143. / 255, 0. / 255, 255. / 255);
    this->color_map["english_lavender"] = Vec3(180. / 255, 131. / 255, 149. / 255);
    this->color_map["emerald"] = Vec3(80. / 255, 200. / 255, 120. / 255);
    this->color_map["fallow"] = Vec3(193. / 255, 154. / 255, 107. / 255);
    this->color_map["eton_blue"] = Vec3(150. / 255, 200. / 255, 162. / 255);
    this->color_map["fandango"] = Vec3(181. / 255, 51. / 255, 137. / 255);
    this->color_map["falu_red"] = Vec3(128. / 255, 24. / 255, 24. / 255);
    this->color_map["fawn"] = Vec3(229. / 255, 170. / 255, 112. / 255);
    this->color_map["fashion_fuchsia"] = Vec3(244. / 255, 0. / 255, 161. / 255);
    this->color_map["fern_green"] = Vec3(79. / 255, 121. / 255, 66. / 255);
    this->color_map["feldgrau"] = Vec3(77. / 255, 93. / 255, 83. / 255);
    this->color_map["field_drab"] = Vec3(108. / 255, 84. / 255, 30. / 255);
    this->color_map["ferrari_red"] = Vec3(255. / 255, 40. / 255, 0. / 255);
    this->color_map["firebrick"] = Vec3(178. / 255, 34. / 255, 34. / 255);
    this->color_map["fire_engine_red"] = Vec3(206. / 255, 32. / 255, 41. / 255);
    this->color_map["flamingo_pink"] = Vec3(252. / 255, 142. / 255, 172. / 255);
    this->color_map["flame"] = Vec3(226. / 255, 88. / 255, 34. / 255);
    this->color_map["flax"] = Vec3(238. / 255, 220. / 255, 130. / 255);
    this->color_map["flavescent"] = Vec3(247. / 255, 233. / 255, 142. / 255);
    this->color_map["fluorescent_orange"] = Vec3(255. / 255, 191. / 255, 0. / 255);
    this->color_map["floral_white"] = Vec3(255. / 255, 250. / 255, 240. / 255);
    this->color_map["fluorescent_yellow"] = Vec3(204. / 255, 255. / 255, 0. / 255);
    this->color_map["fluorescent_pink"] = Vec3(255. / 255, 20. / 255, 147. / 255);
    this->color_map["forest_green_traditional"] = Vec3(1. / 255, 68. / 255, 33. / 255);
    this->color_map["folly"] = Vec3(255. / 255, 0. / 255, 79. / 255);
    this->color_map["french_beige"] = Vec3(166. / 255, 123. / 255, 91. / 255);
    this->color_map["forest_green_web"] = Vec3(34. / 255, 139. / 255, 34. / 255);
    this->color_map["french_lilac"] = Vec3(134. / 255, 96. / 255, 142. / 255);
    this->color_map["french_blue"] = Vec3(0. / 255, 114. / 255, 187. / 255);
    this->color_map["french_raspberry"] = Vec3(199. / 255, 44. / 255, 72. / 255);
    this->color_map["french_lime"] = Vec3(204. / 255, 255. / 255, 0. / 255);
    this->color_map["fuchsia"] = Vec3(255. / 255, 0. / 255, 255. / 255);
    this->color_map["french_rose"] = Vec3(246. / 255, 74. / 255, 138. / 255);
    this->color_map["fuchsia_pink"] = Vec3(255. / 255, 119. / 255, 255. / 255);
    this->color_map["fuchsia_crayola"] = Vec3(193. / 255, 84. / 255, 193. / 255);
    this->color_map["fulvous"] = Vec3(228. / 255, 132. / 255, 0. / 255);
    this->color_map["fuchsia_rose"] = Vec3(199. / 255, 67. / 255, 117. / 255);
    this->color_map["gainsboro"] = Vec3(220. / 255, 220. / 255, 220. / 255);
    this->color_map["fuzzy_wuzzy"] = Vec3(204. / 255, 102. / 255, 102. / 255);
    this->color_map["ghost_white"] = Vec3(248. / 255, 248. / 255, 255. / 255);
    this->color_map["gamboge"] = Vec3(228. / 255, 155. / 255, 15. / 255);
    this->color_map["glaucous"] = Vec3(96. / 255, 130. / 255, 182. / 255);
    this->color_map["ginger"] = Vec3(176. / 255, 101. / 255, 0. / 255);
    this->color_map["gold_metallic"] = Vec3(212. / 255, 175. / 255, 55. / 255);
    this->color_map["glitter"] = Vec3(230. / 255, 232. / 255, 250. / 255);
    this->color_map["golden_brown"] = Vec3(153. / 255, 101. / 255, 21. / 255);
    this->color_map["gold_web_golden"] = Vec3(255. / 255, 215. / 255, 0. / 255);
    this->color_map["golden_yellow"] = Vec3(255. / 255, 223. / 255, 0. / 255);
    this->color_map["golden_poppy"] = Vec3(252. / 255, 194. / 255, 0. / 255);
    this->color_map["granny_smith_apple"] = Vec3(168. / 255, 228. / 255, 160. / 255);
    this->color_map["goldenrod"] = Vec3(218. / 255, 165. / 255, 32. / 255);
    this->color_map["gray_asparagus"] = Vec3(70. / 255, 89. / 255, 69. / 255);
    this->color_map["gray"] = Vec3(128. / 255, 128. / 255, 128. / 255);
    this->color_map["gray_x11_gray"] = Vec3(190. / 255, 190. / 255, 190. / 255);
    this->color_map["gray_html_css_gray"] = Vec3(128. / 255, 128. / 255, 128. / 255);
    this->color_map["green_crayola"] = Vec3(28. / 255, 172. / 255, 120. / 255);
    this->color_map["green_color_wheel_x11_green"] = Vec3(0. / 255, 255. / 255, 0. / 255);
    this->color_map["green_munsell"] = Vec3(0. / 255, 168. / 255, 119. / 255);
    this->color_map["green_html_css_green"] = Vec3(0. / 255, 128. / 255, 0. / 255);
    this->color_map["green_pigment"] = Vec3(0. / 255, 165. / 255, 80. / 255);
    this->color_map["green_ncs"] = Vec3(0. / 255, 159. / 255, 107. / 255);
    this->color_map["green_yellow"] = Vec3(173. / 255, 255. / 255, 47. / 255);
    this->color_map["green_ryb"] = Vec3(102. / 255, 176. / 255, 50. / 255);
    this->color_map["guppie_green"] = Vec3(0. / 255, 255. / 255, 127. / 255);
    this->color_map["grullo"] = Vec3(169. / 255, 154. / 255, 134. / 255);
    this->color_map["han_blue"] = Vec3(68. / 255, 108. / 255, 207. / 255);
    this->color_map["halay_be"] = Vec3(102. / 255, 56. / 255, 84. / 255);
    this->color_map["hansa_yellow"] = Vec3(233. / 255, 214. / 255, 107. / 255);
    this->color_map["han_purple"] = Vec3(82. / 255, 24. / 255, 250. / 255);
    this->color_map["harvard_crimson"] = Vec3(201. / 255, 0. / 255, 22. / 255);
    this->color_map["harlequin"] = Vec3(63. / 255, 255. / 255, 0. / 255);
    this->color_map["heart_gold"] = Vec3(128. / 255, 128. / 255, 0. / 255);
    this->color_map["harvest_gold"] = Vec3(218. / 255, 145. / 255, 0. / 255);
    this->color_map["hollywood_cerise"] = Vec3(244. / 255, 0. / 255, 161. / 255);
    this->color_map["heliotrope"] = Vec3(223. / 255, 115. / 255, 255. / 255);
    this->color_map["honolulu_blue"] = Vec3(0. / 255, 127. / 255, 191. / 255);
    this->color_map["honeydew"] = Vec3(240. / 255, 255. / 255, 240. / 255);
    this->color_map["hot_magenta"] = Vec3(255. / 255, 29. / 255, 206. / 255);
    this->color_map["hooker_s_green"] = Vec3(73. / 255, 121. / 255, 107. / 255);
    this->color_map["hunter_green"] = Vec3(53. / 255, 94. / 255, 59. / 255);
    this->color_map["hot_pink"] = Vec3(255. / 255, 105. / 255, 180. / 255);
    this->color_map["icterine"] = Vec3(252. / 255, 247. / 255, 94. / 255);
    this->color_map["iceberg"] = Vec3(113. / 255, 166. / 255, 210. / 255);
    this->color_map["inchworm"] = Vec3(178. / 255, 236. / 255, 93. / 255);
    this->color_map["imperial_blue"] = Vec3(0. / 255, 35. / 255, 149. / 255);
    this->color_map["indian_red"] = Vec3(205. / 255, 92. / 255, 92. / 255);
    this->color_map["india_green"] = Vec3(19. / 255, 136. / 255, 8. / 255);
    this->color_map["indigo"] = Vec3(111. / 255, 0. / 255, 255. / 255);
    this->color_map["indian_yellow"] = Vec3(227. / 255, 168. / 255, 87. / 255);
    this->color_map["indigo_web"] = Vec3(75. / 255, 0. / 255, 130. / 255);
    this->color_map["indigo_dye"] = Vec3(0. / 255, 65. / 255, 106. / 255);
    this->color_map["international_orange_aerospace"] = Vec3(255. / 255, 79. / 255, 0. / 255);
    this->color_map["international_klein_blue"] = Vec3(0. / 255, 47. / 255, 167. / 255);
    this->color_map["international_orange_golden_gate_bridge"] = Vec3(192. / 255, 54. / 255, 44. / 255);
    this->color_map["international_orange_engineering"] = Vec3(186. / 255, 22. / 255, 12. / 255);
    this->color_map["isabelline"] = Vec3(244. / 255, 240. / 255, 236. / 255);
    this->color_map["iris"] = Vec3(90. / 255, 79. / 255, 207. / 255);
    this->color_map["ivory"] = Vec3(255. / 255, 255. / 255, 240. / 255);
    this->color_map["islamic_green"] = Vec3(0. / 255, 144. / 255, 0. / 255);
    this->color_map["jasmine"] = Vec3(248. / 255, 222. / 255, 126. / 255);
    this->color_map["jade"] = Vec3(0. / 255, 168. / 255, 107. / 255);
    this->color_map["jazzberry_jam"] = Vec3(165. / 255, 11. / 255, 94. / 255);
    this->color_map["jasper"] = Vec3(215. / 255, 59. / 255, 62. / 255);
    this->color_map["jonquil"] = Vec3(250. / 255, 218. / 255, 94. / 255);
    this->color_map["jet"] = Vec3(52. / 255, 52. / 255, 52. / 255);
    this->color_map["jungle_green"] = Vec3(41. / 255, 171. / 255, 135. / 255);
    this->color_map["june_bud"] = Vec3(189. / 255, 218. / 255, 87. / 255);
    this->color_map["kenyan_copper"] = Vec3(124. / 255, 28. / 255, 5. / 255);
    this->color_map["kelly_green"] = Vec3(76. / 255, 187. / 255, 23. / 255);
    this->color_map["khaki_x11_light_khaki"] = Vec3(240. / 255, 230. / 255, 140. / 255);
    this->color_map["khaki_html_css_khaki"] = Vec3(195. / 255, 176. / 255, 145. / 255);
    this->color_map["la_salle_green"] = Vec3(8. / 255, 120. / 255, 48. / 255);
    this->color_map["ku_crimson"] = Vec3(232. / 255, 0. / 255, 13. / 255);
    this->color_map["lapis_lazuli"] = Vec3(38. / 255, 97. / 255, 156. / 255);
    this->color_map["languid_lavender"] = Vec3(214. / 255, 202. / 255, 221. / 255);
    this->color_map["laurel_green"] = Vec3(169. / 255, 186. / 255, 157. / 255);
    this->color_map["laser_lemon"] = Vec3(254. / 255, 254. / 255, 34. / 255);
    this->color_map["lavender_blue"] = Vec3(204. / 255, 204. / 255, 255. / 255);
    this->color_map["lava"] = Vec3(207. / 255, 16. / 255, 32. / 255);
    this->color_map["lavender_floral"] = Vec3(181. / 255, 126. / 255, 220. / 255);
    this->color_map["lavender_blush"] = Vec3(255. / 255, 240. / 255, 245. / 255);
    this->color_map["lavender_indigo"] = Vec3(148. / 255, 87. / 255, 235. / 255);
    this->color_map["lavender_gray"] = Vec3(196. / 255, 195. / 255, 208. / 255);
    this->color_map["lavender_mist"] = Vec3(230. / 255, 230. / 255, 250. / 255);
    this->color_map["lavender_magenta"] = Vec3(238. / 255, 130. / 255, 238. / 255);
    this->color_map["lavender_purple"] = Vec3(150. / 255, 123. / 255, 182. / 255);
    this->color_map["lavender_pink"] = Vec3(251. / 255, 174. / 255, 210. / 255);
    this->color_map["lavender_web"] = Vec3(230. / 255, 230. / 255, 250. / 255);
    this->color_map["lavender_rose"] = Vec3(251. / 255, 160. / 255, 227. / 255);
    this->color_map["lemon"] = Vec3(255. / 255, 247. / 255, 0. / 255);
    this->color_map["lawn_green"] = Vec3(124. / 255, 252. / 255, 0. / 255);
    this->color_map["lemon_lime"] = Vec3(227. / 255, 255. / 255, 0. / 255);
    this->color_map["lemon_chiffon"] = Vec3(255. / 255, 250. / 255, 205. / 255);
    this->color_map["light_apricot"] = Vec3(253. / 255, 213. / 255, 177. / 255);
    this->color_map["licorice"] = Vec3(26. / 255, 17. / 255, 16. / 255);
    this->color_map["light_brown"] = Vec3(181. / 255, 101. / 255, 29. / 255);
    this->color_map["light_blue"] = Vec3(173. / 255, 216. / 255, 230. / 255);
    this->color_map["light_coral"] = Vec3(240. / 255, 128. / 255, 128. / 255);
    this->color_map["light_carmine_pink"] = Vec3(230. / 255, 103. / 255, 113. / 255);
    this->color_map["light_crimson"] = Vec3(245. / 255, 105. / 255, 145. / 255);
    this->color_map["light_cornflower_blue"] = Vec3(147. / 255, 204. / 255, 234. / 255);
    this->color_map["light_fuchsia_pink"] = Vec3(249. / 255, 132. / 255, 239. / 255);
    this->color_map["light_cyan"] = Vec3(224. / 255, 255. / 255, 255. / 255);
    this->color_map["light_gray"] = Vec3(211. / 255, 211. / 255, 211. / 255);
    this->color_map["light_goldenrod_yellow"] = Vec3(250. / 255, 250. / 255, 210. / 255);
    this->color_map["light_khaki"] = Vec3(240. / 255, 230. / 255, 140. / 255);
    this->color_map["light_green"] = Vec3(144. / 255, 238. / 255, 144. / 255);
    this->color_map["light_pink"] = Vec3(255. / 255, 182. / 255, 193. / 255);
    this->color_map["light_pastel_purple"] = Vec3(177. / 255, 156. / 255, 217. / 255);
    this->color_map["light_salmon"] = Vec3(255. / 255, 160. / 255, 122. / 255);
    this->color_map["light_red_ochre"] = Vec3(233. / 255, 116. / 255, 81. / 255);
    this->color_map["light_sea_green"] = Vec3(32. / 255, 178. / 255, 170. / 255);
    this->color_map["light_salmon_pink"] = Vec3(255. / 255, 153. / 255, 153. / 255);
    this->color_map["light_slate_gray"] = Vec3(119. / 255, 136. / 255, 153. / 255);
    this->color_map["light_sky_blue"] = Vec3(135. / 255, 206. / 255, 250. / 255);
    this->color_map["light_thulian_pink"] = Vec3(230. / 255, 143. / 255, 172. / 255);
    this->color_map["light_taupe"] = Vec3(179. / 255, 139. / 255, 109. / 255);
    this->color_map["lilac"] = Vec3(200. / 255, 162. / 255, 200. / 255);
    this->color_map["light_yellow"] = Vec3(255. / 255, 255. / 255, 224. / 255);
    this->color_map["lime_green"] = Vec3(50. / 255, 205. / 255, 50. / 255);
    this->color_map["lime_color_wheel"] = Vec3(191. / 255, 255. / 255, 0. / 255);
    this->color_map["limerick"] = Vec3(157. / 255, 194. / 255, 9. / 255);
    this->color_map["lime_web_x11_green"] = Vec3(0. / 255, 255. / 255, 0. / 255);
    this->color_map["linen"] = Vec3(250. / 255, 240. / 255, 230. / 255);
    this->color_map["lincoln_green"] = Vec3(25. / 255, 89. / 255, 5. / 255);
    this->color_map["little_boy_blue"] = Vec3(108. / 255, 160. / 255, 220. / 255);
    this->color_map["lion"] = Vec3(193. / 255, 154. / 255, 107. / 255);
    this->color_map["lust"] = Vec3(230. / 255, 32. / 255, 32. / 255);
    this->color_map["liver"] = Vec3(83. / 255, 75. / 255, 79. / 255);
    this->color_map["magenta_dye"] = Vec3(202. / 255, 31. / 255, 123. / 255);
    this->color_map["magenta"] = Vec3(255. / 255, 0. / 255, 255. / 255);
    this->color_map["magic_mint"] = Vec3(170. / 255, 240. / 255, 209. / 255);
    this->color_map["magenta_process"] = Vec3(255. / 255, 0. / 255, 144. / 255);
    this->color_map["mahogany"] = Vec3(192. / 255, 64. / 255, 0. / 255);
    this->color_map["magnolia"] = Vec3(248. / 255, 244. / 255, 255. / 255);
    this->color_map["majorelle_blue"] = Vec3(96. / 255, 80. / 255, 220. / 255);
    this->color_map["maize"] = Vec3(251. / 255, 236. / 255, 93. / 255);
    this->color_map["manatee"] = Vec3(151. / 255, 154. / 255, 170. / 255);
    this->color_map["malachite"] = Vec3(11. / 255, 218. / 255, 81. / 255);
    this->color_map["mantis"] = Vec3(116. / 255, 195. / 255, 101. / 255);
    this->color_map["mango_tango"] = Vec3(255. / 255, 130. / 255, 67. / 255);
    this->color_map["maroon_crayola"] = Vec3(195. / 255, 33. / 255, 72. / 255);
    this->color_map["mardi_gras"] = Vec3(136. / 255, 0. / 255, 133. / 255);
    this->color_map["maroon_x11"] = Vec3(176. / 255, 48. / 255, 96. / 255);
    this->color_map["maroon_html_css"] = Vec3(128. / 255, 0. / 255, 0. / 255);
    this->color_map["mauve_taupe"] = Vec3(145. / 255, 95. / 255, 109. / 255);
    this->color_map["mauve"] = Vec3(224. / 255, 176. / 255, 255. / 255);
    this->color_map["maya_blue"] = Vec3(115. / 255, 194. / 255, 251. / 255);
    this->color_map["mauvelous"] = Vec3(239. / 255, 152. / 255, 170. / 255);
    this->color_map["medium_aquamarine"] = Vec3(102. / 255, 221. / 255, 170. / 255);
    this->color_map["meat_brown"] = Vec3(229. / 255, 183. / 255, 59. / 255);
    this->color_map["medium_candy_apple_red"] = Vec3(226. / 255, 6. / 255, 44. / 255);
    this->color_map["medium_blue"] = Vec3(0. / 255, 0. / 255, 205. / 255);
    this->color_map["medium_champagne"] = Vec3(243. / 255, 229. / 255, 171. / 255);
    this->color_map["medium_carmine"] = Vec3(175. / 255, 64. / 255, 53. / 255);
    this->color_map["medium_jungle_green"] = Vec3(28. / 255, 53. / 255, 45. / 255);
    this->color_map["medium_electric_blue"] = Vec3(3. / 255, 80. / 255, 150. / 255);
    this->color_map["medium_orchid"] = Vec3(186. / 255, 85. / 255, 211. / 255);
    this->color_map["medium_lavender_magenta"] = Vec3(221. / 255, 160. / 255, 221. / 255);
    this->color_map["medium_purple"] = Vec3(147. / 255, 112. / 255, 219. / 255);
    this->color_map["medium_persian_blue"] = Vec3(0. / 255, 103. / 255, 165. / 255);
    this->color_map["medium_ruby"] = Vec3(170. / 255, 64. / 255, 105. / 255);
    this->color_map["medium_red_violet"] = Vec3(187. / 255, 51. / 255, 133. / 255);
    this->color_map["medium_slate_blue"] = Vec3(123. / 255, 104. / 255, 238. / 255);
    this->color_map["medium_sea_green"] = Vec3(60. / 255, 179. / 255, 113. / 255);
    this->color_map["medium_spring_green"] = Vec3(0. / 255, 250. / 255, 154. / 255);
    this->color_map["medium_spring_bud"] = Vec3(201. / 255, 220. / 255, 135. / 255);
    this->color_map["medium_turquoise"] = Vec3(72. / 255, 209. / 255, 204. / 255);
    this->color_map["medium_taupe"] = Vec3(103. / 255, 76. / 255, 71. / 255);
    this->color_map["medium_vermilion"] = Vec3(217. / 255, 96. / 255, 59. / 255);
    this->color_map["medium_tuscan_red"] = Vec3(121. / 255, 68. / 255, 59. / 255);
    this->color_map["mellow_apricot"] = Vec3(248. / 255, 184. / 255, 120. / 255);
    this->color_map["medium_violet_red"] = Vec3(199. / 255, 21. / 255, 133. / 255);
    this->color_map["melon"] = Vec3(253. / 255, 188. / 255, 180. / 255);
    this->color_map["mellow_yellow"] = Vec3(248. / 255, 222. / 255, 126. / 255);
    this->color_map["midnight_green_eagle_green"] = Vec3(0. / 255, 73. / 255, 83. / 255);
    this->color_map["midnight_blue"] = Vec3(25. / 255, 25. / 255, 112. / 255);
    this->color_map["mint"] = Vec3(62. / 255, 180. / 255, 137. / 255);
    this->color_map["mikado_yellow"] = Vec3(255. / 255, 196. / 255, 12. / 255);
    this->color_map["mint_green"] = Vec3(152. / 255, 255. / 255, 152. / 255);
    this->color_map["mint_cream"] = Vec3(245. / 255, 255. / 255, 250. / 255);
    this->color_map["moccasin"] = Vec3(250. / 255, 235. / 255, 215. / 255);
    this->color_map["misty_rose"] = Vec3(255. / 255, 228. / 255, 225. / 255);
    this->color_map["moonstone_blue"] = Vec3(115. / 255, 169. / 255, 194. / 255);
    this->color_map["mode_beige"] = Vec3(150. / 255, 113. / 255, 23. / 255);
    this->color_map["moss_green"] = Vec3(173. / 255, 223. / 255, 173. / 255);
    this->color_map["mordant_red_19"] = Vec3(174. / 255, 12. / 255, 0. / 255);
    this->color_map["mountbatten_pink"] = Vec3(153. / 255, 122. / 255, 141. / 255);
    this->color_map["mountain_meadow"] = Vec3(48. / 255, 186. / 255, 143. / 255);
    this->color_map["mulberry"] = Vec3(197. / 255, 75. / 255, 140. / 255);
    this->color_map["msu_green"] = Vec3(24. / 255, 69. / 255, 59. / 255);
    this->color_map["myrtle"] = Vec3(33. / 255, 66. / 255, 30. / 255);
    this->color_map["mustard"] = Vec3(255. / 255, 219. / 255, 88. / 255);
    this->color_map["napier_green"] = Vec3(42. / 255, 128. / 255, 0. / 255);
    this->color_map["nadeshiko_pink"] = Vec3(246. / 255, 173. / 255, 198. / 255);
    this->color_map["navajo_white"] = Vec3(255. / 255, 222. / 255, 173. / 255);
    this->color_map["naples_yellow"] = Vec3(250. / 255, 218. / 255, 94. / 255);
    this->color_map["neon_carrot"] = Vec3(255. / 255, 163. / 255, 67. / 255);
    this->color_map["navy_blue"] = Vec3(0. / 255, 0. / 255, 128. / 255);
    this->color_map["neon_green"] = Vec3(57. / 255, 255. / 255, 20. / 255);
    this->color_map["neon_fuchsia"] = Vec3(254. / 255, 65. / 255, 100. / 255);
    this->color_map["non_photo_blue"] = Vec3(164. / 255, 221. / 255, 237. / 255);
    this->color_map["new_york_pink"] = Vec3(215. / 255, 131. / 255, 127. / 255);
    this->color_map["ocean_boat_blue"] = Vec3(0. / 255, 119. / 255, 190. / 255);
    this->color_map["north_texas_green"] = Vec3(5. / 255, 144. / 255, 51. / 255);
    this->color_map["office_green"] = Vec3(0. / 255, 128. / 255, 0. / 255);
    this->color_map["ochre"] = Vec3(204. / 255, 119. / 255, 34. / 255);
    this->color_map["old_lace"] = Vec3(253. / 255, 245. / 255, 230. / 255);
    this->color_map["old_gold"] = Vec3(207. / 255, 181. / 255, 59. / 255);
    this->color_map["old_mauve"] = Vec3(103. / 255, 49. / 255, 71. / 255);
    this->color_map["old_lavender"] = Vec3(121. / 255, 104. / 255, 120. / 255);
    this->color_map["olive"] = Vec3(128. / 255, 128. / 255, 0. / 255);
    this->color_map["old_rose"] = Vec3(192. / 255, 128. / 255, 129. / 255);
    this->color_map["olive_drab_web_olive_drab_3"] = Vec3(107. / 255, 142. / 255, 35. / 255);
    this->color_map["olive_drab_7"] = Vec3(60. / 255, 52. / 255, 31. / 255);
    this->color_map["onyx"] = Vec3(53. / 255, 56. / 255, 57. / 255);
    this->color_map["olivine"] = Vec3(154. / 255, 185. / 255, 115. / 255);
    this->color_map["orange_color_wheel"] = Vec3(255. / 255, 127. / 255, 0. / 255);
    this->color_map["opera_mauve"] = Vec3(183. / 255, 132. / 255, 167. / 255);
    this->color_map["orange_red"] = Vec3(255. / 255, 69. / 255, 0. / 255);
    this->color_map["orange_peel"] = Vec3(255. / 255, 159. / 255, 0. / 255);
    this->color_map["orange_web_color"] = Vec3(255. / 255, 165. / 255, 0. / 255);
    this->color_map["orange_ryb"] = Vec3(251. / 255, 153. / 255, 2. / 255);
    this->color_map["otter_brown"] = Vec3(101. / 255, 67. / 255, 33. / 255);
    this->color_map["orchid"] = Vec3(218. / 255, 112. / 255, 214. / 255);
    this->color_map["outer_space"] = Vec3(65. / 255, 74. / 255, 76. / 255);
    this->color_map["ou_crimson_red"] = Vec3(153. / 255, 0. / 255, 0. / 255);
    this->color_map["oxford_blue"] = Vec3(0. / 255, 33. / 255, 71. / 255);
    this->color_map["outrageous_orange"] = Vec3(255. / 255, 110. / 255, 74. / 255);
    this->color_map["palatinate_blue"] = Vec3(39. / 255, 59. / 255, 226. / 255);
    this->color_map["pakistan_green"] = Vec3(0. / 255, 102. / 255, 0. / 255);
    this->color_map["pale_aqua"] = Vec3(188. / 255, 212. / 255, 230. / 255);
    this->color_map["palatinate_purple"] = Vec3(104. / 255, 40. / 255, 96. / 255);
    this->color_map["pale_brown"] = Vec3(152. / 255, 118. / 255, 84. / 255);
    this->color_map["pale_blue"] = Vec3(175. / 255, 238. / 255, 238. / 255);
    this->color_map["pale_cerulean"] = Vec3(155. / 255, 196. / 255, 226. / 255);
    this->color_map["pale_carmine"] = Vec3(175. / 255, 64. / 255, 53. / 255);
    this->color_map["pale_copper"] = Vec3(218. / 255, 138. / 255, 103. / 255);
    this->color_map["pale_chestnut"] = Vec3(221. / 255, 173. / 255, 175. / 255);
    this->color_map["pale_gold"] = Vec3(230. / 255, 190. / 255, 138. / 255);
    this->color_map["pale_cornflower_blue"] = Vec3(171. / 255, 205. / 255, 239. / 255);
    this->color_map["pale_green"] = Vec3(152. / 255, 251. / 255, 152. / 255);
    this->color_map["pale_goldenrod"] = Vec3(238. / 255, 232. / 255, 170. / 255);
    this->color_map["pale_magenta"] = Vec3(249. / 255, 132. / 255, 229. / 255);
    this->color_map["pale_lavender"] = Vec3(220. / 255, 208. / 255, 255. / 255);
    this->color_map["pale_plum"] = Vec3(221. / 255, 160. / 255, 221. / 255);
    this->color_map["pale_pink"] = Vec3(250. / 255, 218. / 255, 221. / 255);
    this->color_map["pale_robin_egg_blue"] = Vec3(150. / 255, 222. / 255, 209. / 255);
    this->color_map["pale_red_violet"] = Vec3(219. / 255, 112. / 255, 147. / 255);
    this->color_map["pale_spring_bud"] = Vec3(236. / 255, 235. / 255, 189. / 255);
    this->color_map["pale_silver"] = Vec3(201. / 255, 192. / 255, 187. / 255);
    this->color_map["pale_violet_red"] = Vec3(219. / 255, 112. / 255, 147. / 255);
    this->color_map["pale_taupe"] = Vec3(188. / 255, 152. / 255, 126. / 255);
    this->color_map["papaya_whip"] = Vec3(255. / 255, 239. / 255, 213. / 255);
    this->color_map["pansy_purple"] = Vec3(120. / 255, 24. / 255, 74. / 255);
    this->color_map["pastel_blue"] = Vec3(174. / 255, 198. / 255, 207. / 255);
    this->color_map["paris_green"] = Vec3(80. / 255, 200. / 255, 120. / 255);
    this->color_map["pastel_gray"] = Vec3(207. / 255, 207. / 255, 196. / 255);
    this->color_map["pastel_brown"] = Vec3(131. / 255, 105. / 255, 83. / 255);
    this->color_map["pastel_magenta"] = Vec3(244. / 255, 154. / 255, 194. / 255);
    this->color_map["pastel_green"] = Vec3(119. / 255, 221. / 255, 119. / 255);
    this->color_map["pastel_pink"] = Vec3(222. / 255, 165. / 255, 164. / 255);
    this->color_map["pastel_orange"] = Vec3(255. / 255, 179. / 255, 71. / 255);
    this->color_map["pastel_red"] = Vec3(255. / 255, 105. / 255, 97. / 255);
    this->color_map["pastel_purple"] = Vec3(179. / 255, 158. / 255, 181. / 255);
    this->color_map["pastel_yellow"] = Vec3(253. / 255, 253. / 255, 150. / 255);
    this->color_map["pastel_violet"] = Vec3(203. / 255, 153. / 255, 201. / 255);
    this->color_map["payne_s_grey"] = Vec3(83. / 255, 104. / 255, 120. / 255);
    this->color_map["patriarch"] = Vec3(128. / 255, 0. / 255, 128. / 255);
    this->color_map["peach_crayola"] = Vec3(255. / 255, 203. / 255, 164. / 255);
    this->color_map["peach"] = Vec3(255. / 255, 229. / 255, 180. / 255);
    this->color_map["peach_puff"] = Vec3(255. / 255, 218. / 255, 185. / 255);
    this->color_map["peach_orange"] = Vec3(255. / 255, 204. / 255, 153. / 255);
    this->color_map["pear"] = Vec3(209. / 255, 226. / 255, 49. / 255);
    this->color_map["peach_yellow"] = Vec3(250. / 255, 223. / 255, 173. / 255);
    this->color_map["pearl_aqua"] = Vec3(136. / 255, 216. / 255, 192. / 255);
    this->color_map["pearl"] = Vec3(234. / 255, 224. / 255, 200. / 255);
    this->color_map["peridot"] = Vec3(230. / 255, 226. / 255, 0. / 255);
    this->color_map["pearly_purple"] = Vec3(183. / 255, 104. / 255, 162. / 255);
    this->color_map["persian_blue"] = Vec3(28. / 255, 57. / 255, 187. / 255);
    this->color_map["periwinkle"] = Vec3(204. / 255, 204. / 255, 255. / 255);
    this->color_map["persian_indigo"] = Vec3(50. / 255, 18. / 255, 122. / 255);
    this->color_map["persian_green"] = Vec3(0. / 255, 166. / 255, 147. / 255);
    this->color_map["persian_pink"] = Vec3(247. / 255, 127. / 255, 190. / 255);
    this->color_map["persian_orange"] = Vec3(217. / 255, 144. / 255, 88. / 255);
    this->color_map["persian_red"] = Vec3(204. / 255, 51. / 255, 51. / 255);
    this->color_map["persian_plum"] = Vec3(112. / 255, 28. / 255, 28. / 255);
    this->color_map["persimmon"] = Vec3(236. / 255, 88. / 255, 0. / 255);
    this->color_map["persian_rose"] = Vec3(254. / 255, 40. / 255, 162. / 255);
    this->color_map["phlox"] = Vec3(223. / 255, 0. / 255, 255. / 255);
    this->color_map["peru"] = Vec3(205. / 255, 133. / 255, 63. / 255);
    this->color_map["phthalo_green"] = Vec3(18. / 255, 53. / 255, 36. / 255);
    this->color_map["phthalo_blue"] = Vec3(0. / 255, 15. / 255, 137. / 255);
    this->color_map["pine_green"] = Vec3(1. / 255, 121. / 255, 111. / 255);
    this->color_map["piggy_pink"] = Vec3(253. / 255, 221. / 255, 230. / 255);
    this->color_map["pink_lace"] = Vec3(255. / 255, 221. / 255, 244. / 255);
    this->color_map["pink"] = Vec3(255. / 255, 192. / 255, 203. / 255);
    this->color_map["pink_pearl"] = Vec3(231. / 255, 172. / 255, 207. / 255);
    this->color_map["pink_orange"] = Vec3(255. / 255, 153. / 255, 102. / 255);
    this->color_map["pistachio"] = Vec3(147. / 255, 197. / 255, 114. / 255);
    this->color_map["pink_sherbet"] = Vec3(247. / 255, 143. / 255, 167. / 255);
    this->color_map["plum_traditional"] = Vec3(142. / 255, 69. / 255, 133. / 255);
    this->color_map["platinum"] = Vec3(229. / 255, 228. / 255, 226. / 255);
    this->color_map["portland_orange"] = Vec3(255. / 255, 90. / 255, 54. / 255);
    this->color_map["plum_web"] = Vec3(221. / 255, 160. / 255, 221. / 255);
    this->color_map["princeton_orange"] = Vec3(255. / 255, 143. / 255, 0. / 255);
    this->color_map["powder_blue_web"] = Vec3(176. / 255, 224. / 255, 230. / 255);
    this->color_map["prussian_blue"] = Vec3(0. / 255, 49. / 255, 83. / 255);
    this->color_map["prune"] = Vec3(112. / 255, 28. / 255, 28. / 255);
    this->color_map["puce"] = Vec3(204. / 255, 136. / 255, 153. / 255);
    this->color_map["psychedelic_purple"] = Vec3(223. / 255, 0. / 255, 255. / 255);
    this->color_map["purple_heart"] = Vec3(105. / 255, 53. / 255, 156. / 255);
    this->color_map["pumpkin"] = Vec3(255. / 255, 117. / 255, 24. / 255);
    this->color_map["purple_mountain_majesty"] = Vec3(150. / 255, 120. / 255, 182. / 255);
    this->color_map["purple_html_css"] = Vec3(128. / 255, 0. / 255, 128. / 255);
    this->color_map["purple_pizzazz"] = Vec3(254. / 255, 78. / 255, 218. / 255);
    this->color_map["purple_munsell"] = Vec3(159. / 255, 0. / 255, 197. / 255);
    this->color_map["purple_x11"] = Vec3(160. / 255, 32. / 255, 240. / 255);
    this->color_map["purple_taupe"] = Vec3(80. / 255, 64. / 255, 77. / 255);
    this->color_map["rackley"] = Vec3(93. / 255, 138. / 255, 168. / 255);
    this->color_map["quartz"] = Vec3(81. / 255, 72. / 255, 79. / 255);
    this->color_map["rajah"] = Vec3(251. / 255, 171. / 255, 96. / 255);
    this->color_map["radical_red"] = Vec3(255. / 255, 53. / 255, 94. / 255);
    this->color_map["raspberry_glace"] = Vec3(145. / 255, 95. / 255, 109. / 255);
    this->color_map["raspberry"] = Vec3(227. / 255, 11. / 255, 93. / 255);
    this->color_map["raspberry_rose"] = Vec3(179. / 255, 68. / 255, 108. / 255);
    this->color_map["raspberry_pink"] = Vec3(226. / 255, 80. / 255, 152. / 255);
    this->color_map["razzle_dazzle_rose"] = Vec3(255. / 255, 51. / 255, 204. / 255);
    this->color_map["raw_umber"] = Vec3(130. / 255, 102. / 255, 68. / 255);
    this->color_map["red"] = Vec3(255. / 255, 0. / 255, 0. / 255);
    this->color_map["razzmatazz"] = Vec3(227. / 255, 37. / 255, 107. / 255);
    this->color_map["red_devil"] = Vec3(134. / 255, 1. / 255, 17. / 255);
    this->color_map["red_brown"] = Vec3(165. / 255, 42. / 255, 42. / 255);
    this->color_map["red_ncs"] = Vec3(196. / 255, 2. / 255, 51. / 255);
    this->color_map["red_munsell"] = Vec3(242. / 255, 0. / 255, 60. / 255);
    this->color_map["red_pigment"] = Vec3(237. / 255, 28. / 255, 36. / 255);
    this->color_map["red_orange"] = Vec3(255. / 255, 83. / 255, 73. / 255);
    this->color_map["red_violet"] = Vec3(199. / 255, 21. / 255, 133. / 255);
    this->color_map["red_ryb"] = Vec3(254. / 255, 39. / 255, 18. / 255);
    this->color_map["regalia"] = Vec3(82. / 255, 45. / 255, 128. / 255);
    this->color_map["redwood"] = Vec3(171. / 255, 78. / 255, 82. / 255);
    this->color_map["rich_black"] = Vec3(0. / 255, 64. / 255, 64. / 255);
    this->color_map["resolution_blue"] = Vec3(0. / 255, 35. / 255, 135. / 255);
    this->color_map["rich_carmine"] = Vec3(215. / 255, 0. / 255, 64. / 255);
    this->color_map["rich_brilliant_lavender"] = Vec3(241. / 255, 167. / 255, 254. / 255);
    this->color_map["rich_lavender"] = Vec3(167. / 255, 107. / 255, 207. / 255);
    this->color_map["rich_electric_blue"] = Vec3(8. / 255, 146. / 255, 208. / 255);
    this->color_map["rich_maroon"] = Vec3(176. / 255, 48. / 255, 96. / 255);
    this->color_map["rich_lilac"] = Vec3(182. / 255, 102. / 255, 210. / 255);
    this->color_map["robin_egg_blue"] = Vec3(0. / 255, 204. / 255, 204. / 255);
    this->color_map["rifle_green"] = Vec3(65. / 255, 72. / 255, 51. / 255);
    this->color_map["rose_bonbon"] = Vec3(249. / 255, 66. / 255, 158. / 255);
    this->color_map["rose"] = Vec3(255. / 255, 0. / 255, 127. / 255);
    this->color_map["rose_gold"] = Vec3(183. / 255, 110. / 255, 121. / 255);
    this->color_map["rose_ebony"] = Vec3(103. / 255, 72. / 255, 70. / 255);
    this->color_map["rose_pink"] = Vec3(255. / 255, 102. / 255, 204. / 255);
    this->color_map["rose_madder"] = Vec3(227. / 255, 38. / 255, 54. / 255);
    this->color_map["rose_taupe"] = Vec3(144. / 255, 93. / 255, 93. / 255);
    this->color_map["rose_quartz"] = Vec3(170. / 255, 152. / 255, 169. / 255);
    this->color_map["rosewood"] = Vec3(101. / 255, 0. / 255, 11. / 255);
    this->color_map["rose_vale"] = Vec3(171. / 255, 78. / 255, 82. / 255);
    this->color_map["rosy_brown"] = Vec3(188. / 255, 143. / 255, 143. / 255);
    this->color_map["rosso_corsa"] = Vec3(212. / 255, 0. / 255, 0. / 255);
    this->color_map["royal_blue_traditional"] = Vec3(0. / 255, 35. / 255, 102. / 255);
    this->color_map["royal_azure"] = Vec3(0. / 255, 56. / 255, 168. / 255);
    this->color_map["royal_fuchsia"] = Vec3(202. / 255, 44. / 255, 146. / 255);
    this->color_map["royal_blue_web"] = Vec3(65. / 255, 105. / 255, 225. / 255);
    this->color_map["royal_yellow"] = Vec3(250. / 255, 218. / 255, 94. / 255);
    this->color_map["royal_purple"] = Vec3(120. / 255, 81. / 255, 169. / 255);
    this->color_map["ruby"] = Vec3(224. / 255, 17. / 255, 95. / 255);
    this->color_map["rubine_red"] = Vec3(209. / 255, 0. / 255, 86. / 255);
    this->color_map["ruddy"] = Vec3(255. / 255, 0. / 255, 40. / 255);
    this->color_map["ruby_red"] = Vec3(155. / 255, 17. / 255, 30. / 255);
    this->color_map["ruddy_pink"] = Vec3(225. / 255, 142. / 255, 150. / 255);
    this->color_map["ruddy_brown"] = Vec3(187. / 255, 101. / 255, 40. / 255);
    this->color_map["russet"] = Vec3(128. / 255, 70. / 255, 27. / 255);
    this->color_map["rufous"] = Vec3(168. / 255, 28. / 255, 7. / 255);
    this->color_map["rusty_red"] = Vec3(218. / 255, 44. / 255, 67. / 255);
    this->color_map["rust"] = Vec3(183. / 255, 65. / 255, 14. / 255);
    this->color_map["saddle_brown"] = Vec3(139. / 255, 69. / 255, 19. / 255);
    this->color_map["sacramento_state_green"] = Vec3(0. / 255, 86. / 255, 63. / 255);
    this->color_map["saffron"] = Vec3(244. / 255, 196. / 255, 48. / 255);
    this->color_map["safety_orange_blaze_orange"] = Vec3(255. / 255, 103. / 255, 0. / 255);
    this->color_map["salmon_pink"] = Vec3(255. / 255, 145. / 255, 164. / 255);
    this->color_map["salmon"] = Vec3(255. / 255, 140. / 255, 105. / 255);
    this->color_map["sand_dune"] = Vec3(150. / 255, 113. / 255, 23. / 255);
    this->color_map["sand"] = Vec3(194. / 255, 178. / 255, 128. / 255);
    this->color_map["sandy_brown"] = Vec3(244. / 255, 164. / 255, 96. / 255);
    this->color_map["sandstorm"] = Vec3(236. / 255, 213. / 255, 64. / 255);
    this->color_map["sangria"] = Vec3(146. / 255, 0. / 255, 10. / 255);
    this->color_map["sandy_taupe"] = Vec3(150. / 255, 113. / 255, 23. / 255);
    this->color_map["sapphire"] = Vec3(15. / 255, 82. / 255, 186. / 255);
    this->color_map["sap_green"] = Vec3(80. / 255, 125. / 255, 42. / 255);
    this->color_map["satin_sheen_gold"] = Vec3(203. / 255, 161. / 255, 53. / 255);
    this->color_map["sapphire_blue"] = Vec3(0. / 255, 103. / 255, 165. / 255);
    this->color_map["scarlet_crayola"] = Vec3(253. / 255, 14. / 255, 53. / 255);
    this->color_map["scarlet"] = Vec3(255. / 255, 36. / 255, 0. / 255);
    this->color_map["screamin_green"] = Vec3(118. / 255, 255. / 255, 122. / 255);
    this->color_map["school_bus_yellow"] = Vec3(255. / 255, 216. / 255, 0. / 255);
    this->color_map["sea_green"] = Vec3(46. / 255, 139. / 255, 87. / 255);
    this->color_map["sea_blue"] = Vec3(0. / 255, 105. / 255, 148. / 255);
    this->color_map["seashell"] = Vec3(255. / 255, 245. / 255, 238. / 255);
    this->color_map["seal_brown"] = Vec3(50. / 255, 20. / 255, 20. / 255);
    this->color_map["sepia"] = Vec3(112. / 255, 66. / 255, 20. / 255);
    this->color_map["selective_yellow"] = Vec3(255. / 255, 186. / 255, 0. / 255);
    this->color_map["shamrock_green"] = Vec3(0. / 255, 158. / 255, 96. / 255);
    this->color_map["shadow"] = Vec3(138. / 255, 121. / 255, 93. / 255);
    this->color_map["shocking_pink_crayola"] = Vec3(255. / 255, 111. / 255, 255. / 255);
    this->color_map["shocking_pink"] = Vec3(252. / 255, 15. / 255, 192. / 255);
    this->color_map["silver"] = Vec3(192. / 255, 192. / 255, 192. / 255);
    this->color_map["sienna"] = Vec3(136. / 255, 45. / 255, 23. / 255);
    this->color_map["skobeloff"] = Vec3(0. / 255, 116. / 255, 116. / 255);
    this->color_map["sinopia"] = Vec3(203. / 255, 65. / 255, 11. / 255);
    this->color_map["sky_magenta"] = Vec3(207. / 255, 113. / 255, 175. / 255);
    this->color_map["sky_blue"] = Vec3(135. / 255, 206. / 255, 235. / 255);
    this->color_map["slate_gray"] = Vec3(112. / 255, 128. / 255, 144. / 255);
    this->color_map["slate_blue"] = Vec3(106. / 255, 90. / 255, 205. / 255);
    this->color_map["smokey_topaz"] = Vec3(147. / 255, 61. / 255, 65. / 255);
    this->color_map["smalt_dark_powder_blue"] = Vec3(0. / 255, 51. / 255, 153. / 255);
    this->color_map["snow"] = Vec3(255. / 255, 250. / 255, 250. / 255);
    this->color_map["smoky_black"] = Vec3(16. / 255, 12. / 255, 8. / 255);
    this->color_map["spring_bud"] = Vec3(167. / 255, 252. / 255, 0. / 255);
    this->color_map["spiro_disco_ball"] = Vec3(15. / 255, 192. / 255, 252. / 255);
    this->color_map["st_patrick_s_blue"] = Vec3(35. / 255, 41. / 255, 122. / 255);
    this->color_map["spring_green"] = Vec3(0. / 255, 255. / 255, 127. / 255);
    this->color_map["stil_de_grain_yellow"] = Vec3(250. / 255, 218. / 255, 94. / 255);
    this->color_map["steel_blue"] = Vec3(70. / 255, 130. / 255, 180. / 255);
    this->color_map["stormcloud"] = Vec3(79. / 255, 102. / 255, 106. / 255);
    this->color_map["stizza"] = Vec3(153. / 255, 0. / 255, 0. / 255);
    this->color_map["sunglow"] = Vec3(255. / 255, 204. / 255, 51. / 255);
    this->color_map["straw"] = Vec3(228. / 255, 217. / 255, 111. / 255);
    this->color_map["tan"] = Vec3(210. / 255, 180. / 255, 140. / 255);
    this->color_map["sunset"] = Vec3(250. / 255, 214. / 255, 165. / 255);
    this->color_map["tangerine"] = Vec3(242. / 255, 133. / 255, 0. / 255);
    this->color_map["tangelo"] = Vec3(249. / 255, 77. / 255, 0. / 255);
    this->color_map["tango_pink"] = Vec3(228. / 255, 113. / 255, 122. / 255);
    this->color_map["tangerine_yellow"] = Vec3(255. / 255, 204. / 255, 0. / 255);
    this->color_map["taupe_gray"] = Vec3(139. / 255, 133. / 255, 137. / 255);
    this->color_map["taupe"] = Vec3(72. / 255, 60. / 255, 50. / 255);
    this->color_map["tea_rose_orange"] = Vec3(248. / 255, 131. / 255, 121. / 255);
    this->color_map["tea_green"] = Vec3(208. / 255, 240. / 255, 192. / 255);
    this->color_map["teal"] = Vec3(0. / 255, 128. / 255, 128. / 255);
    this->color_map["tea_rose_rose"] = Vec3(244. / 255, 194. / 255, 194. / 255);
    this->color_map["teal_green"] = Vec3(0. / 255, 130. / 255, 127. / 255);
    this->color_map["teal_blue"] = Vec3(54. / 255, 117. / 255, 136. / 255);
    this->color_map["tenn_tawny"] = Vec3(205. / 255, 87. / 255, 0. / 255);
    this->color_map["telemagenta"] = Vec3(207. / 255, 52. / 255, 118. / 255);
    this->color_map["thistle"] = Vec3(216. / 255, 191. / 255, 216. / 255);
    this->color_map["terra_cotta"] = Vec3(226. / 255, 114. / 255, 91. / 255);
    this->color_map["tickle_me_pink"] = Vec3(252. / 255, 137. / 255, 172. / 255);
    this->color_map["thulian_pink"] = Vec3(222. / 255, 111. / 255, 161. / 255);
    this->color_map["tiger_s_eye"] = Vec3(224. / 255, 141. / 255, 60. / 255);
    this->color_map["tiffany_blue"] = Vec3(10. / 255, 186. / 255, 181. / 255);
    this->color_map["titanium_yellow"] = Vec3(238. / 255, 230. / 255, 0. / 255);
    this->color_map["timberwolf"] = Vec3(219. / 255, 215. / 255, 210. / 255);
    this->color_map["toolbox"] = Vec3(116. / 255, 108. / 255, 192. / 255);
    this->color_map["tomato"] = Vec3(255. / 255, 99. / 255, 71. / 255);
    this->color_map["tractor_red"] = Vec3(253. / 255, 14. / 255, 53. / 255);
    this->color_map["topaz"] = Vec3(255. / 255, 200. / 255, 124. / 255);
    this->color_map["tropical_rain_forest"] = Vec3(0. / 255, 117. / 255, 94. / 255);
    this->color_map["trolley_grey"] = Vec3(128. / 255, 128. / 255, 128. / 255);
    this->color_map["tufts_blue"] = Vec3(65. / 255, 125. / 255, 193. / 255);
    this->color_map["true_blue"] = Vec3(0. / 255, 115. / 255, 207. / 255);
    this->color_map["turkish_rose"] = Vec3(181. / 255, 114. / 255, 129. / 255);
    this->color_map["tumbleweed"] = Vec3(222. / 255, 170. / 255, 136. / 255);
    this->color_map["turquoise_blue"] = Vec3(0. / 255, 255. / 255, 239. / 255);
    this->color_map["turquoise"] = Vec3(48. / 255, 213. / 255, 200. / 255);
    this->color_map["tuscan_red"] = Vec3(124. / 255, 72. / 255, 72. / 255);
    this->color_map["turquoise_green"] = Vec3(160. / 255, 214. / 255, 180. / 255);
    this->color_map["tyrian_purple"] = Vec3(102. / 255, 2. / 255, 60. / 255);
    this->color_map["twilight_lavender"] = Vec3(138. / 255, 73. / 255, 107. / 255);
    this->color_map["ua_red"] = Vec3(217. / 255, 0. / 255, 76. / 255);
    this->color_map["ua_blue"] = Vec3(0. / 255, 51. / 255, 170. / 255);
    this->color_map["ucla_blue"] = Vec3(83. / 255, 104. / 255, 149. / 255);
    this->color_map["ube"] = Vec3(136. / 255, 120. / 255, 195. / 255);
    this->color_map["ufo_green"] = Vec3(60. / 255, 208. / 255, 112. / 255);
    this->color_map["ucla_gold"] = Vec3(255. / 255, 179. / 255, 0. / 255);
    this->color_map["ultramarine"] = Vec3(18. / 255, 10. / 255, 143. / 255);
    this->color_map["ultra_pink"] = Vec3(255. / 255, 111. / 255, 255. / 255);
    this->color_map["umber"] = Vec3(99. / 255, 81. / 255, 71. / 255);
    this->color_map["ultramarine_blue"] = Vec3(65. / 255, 102. / 255, 245. / 255);
    this->color_map["united_nations_blue"] = Vec3(91. / 255, 146. / 255, 229. / 255);
    this->color_map["unbleached_silk"] = Vec3(255. / 255, 221. / 255, 202. / 255);
    this->color_map["unmellow_yellow"] = Vec3(255. / 255, 255. / 255, 102. / 255);
    this->color_map["university_of_california_gold"] = Vec3(183. / 255, 135. / 255, 39. / 255);
    this->color_map["up_maroon"] = Vec3(123. / 255, 17. / 255, 19. / 255);
    this->color_map["up_forest_green"] = Vec3(1. / 255, 68. / 255, 33. / 255);
    this->color_map["urobilin"] = Vec3(225. / 255, 173. / 255, 33. / 255);
    this->color_map["upsdell_red"] = Vec3(174. / 255, 32. / 255, 41. / 255);
    this->color_map["usc_cardinal"] = Vec3(153. / 255, 0. / 255, 0. / 255);
    this->color_map["usafa_blue"] = Vec3(0. / 255, 79. / 255, 152. / 255);
    this->color_map["utah_crimson"] = Vec3(211. / 255, 0. / 255, 63. / 255);
    this->color_map["usc_gold"] = Vec3(255. / 255, 204. / 255, 0. / 255);
    this->color_map["vegas_gold"] = Vec3(197. / 255, 179. / 255, 88. / 255);
    this->color_map["vanilla"] = Vec3(243. / 255, 229. / 255, 171. / 255);
    this->color_map["verdigris"] = Vec3(67. / 255, 179. / 255, 174. / 255);
    this->color_map["venetian_red"] = Vec3(200. / 255, 8. / 255, 21. / 255);
    this->color_map["vermilion_plochere"] = Vec3(217. / 255, 96. / 255, 59. / 255);
    this->color_map["vermilion_cinnabar"] = Vec3(227. / 255, 66. / 255, 52. / 255);
    this->color_map["violet"] = Vec3(143. / 255, 0. / 255, 255. / 255);
    this->color_map["veronica"] = Vec3(160. / 255, 32. / 255, 240. / 255);
    this->color_map["violet_color_wheel"] = Vec3(127. / 255, 0. / 255, 255. / 255);
    this->color_map["violet_blue"] = Vec3(50. / 255, 74. / 255, 178. / 255);
    this->color_map["violet_web"] = Vec3(238. / 255, 130. / 255, 238. / 255);
    this->color_map["violet_ryb"] = Vec3(134. / 255, 1. / 255, 175. / 255);
    this->color_map["vivid_auburn"] = Vec3(146. / 255, 39. / 255, 36. / 255);
    this->color_map["viridian"] = Vec3(64. / 255, 130. / 255, 109. / 255);
    this->color_map["vivid_cerise"] = Vec3(218. / 255, 29. / 255, 129. / 255);
    this->color_map["vivid_burgundy"] = Vec3(159. / 255, 29. / 255, 53. / 255);
    this->color_map["vivid_violet"] = Vec3(159. / 255, 0. / 255, 255. / 255);
    this->color_map["vivid_tangerine"] = Vec3(255. / 255, 160. / 255, 137. / 255);
    this->color_map["waterspout"] = Vec3(164. / 255, 244. / 255, 249. / 255);
    this->color_map["warm_black"] = Vec3(0. / 255, 66. / 255, 66. / 255);
    this->color_map["wheat"] = Vec3(245. / 255, 222. / 255, 179. / 255);
    this->color_map["wenge"] = Vec3(100. / 255, 84. / 255, 82. / 255);
    this->color_map["white_smoke"] = Vec3(245. / 255, 245. / 255, 245. / 255);
    this->color_map["white"] = Vec3(255. / 255, 255. / 255, 255. / 255);
    this->color_map["wild_strawberry"] = Vec3(255. / 255, 67. / 255, 164. / 255);
    this->color_map["wild_blue_yonder"] = Vec3(162. / 255, 173. / 255, 208. / 255);
    this->color_map["wine"] = Vec3(114. / 255, 47. / 255, 55. / 255);
    this->color_map["wild_watermelon"] = Vec3(252. / 255, 108. / 255, 133. / 255);
    this->color_map["wisteria"] = Vec3(201. / 255, 160. / 255, 220. / 255);
    this->color_map["wine_dregs"] = Vec3(103. / 255, 49. / 255, 71. / 255);
    this->color_map["xanadu"] = Vec3(115. / 255, 134. / 255, 120. / 255);
    this->color_map["wood_brown"] = Vec3(193. / 255, 154. / 255, 107. / 255);
    this->color_map["yellow"] = Vec3(255. / 255, 255. / 255, 0. / 255);
    this->color_map["yale_blue"] = Vec3(15. / 255, 77. / 255, 146. / 255);
    this->color_map["yellow_munsell"] = Vec3(239. / 255, 204. / 255, 0. / 255);
    this->color_map["yellow_green"] = Vec3(154. / 255, 205. / 255, 50. / 255);
    this->color_map["yellow_orange"] = Vec3(255. / 255, 174. / 255, 66. / 255);
    this->color_map["yellow_ncs"] = Vec3(255. / 255, 211. / 255, 0. / 255);
    this->color_map["yellow_ryb"] = Vec3(254. / 255, 254. / 255, 51. / 255);
    this->color_map["yellow_process"] = Vec3(255. / 255, 239. / 255, 0. / 255);
    this->color_map["zinnwaldite_brown"] = Vec3(44. / 255, 22. / 255, 8. / 255);
    this->color_map["zaffre"] = Vec3(0. / 255, 20. / 255, 168. / 255);
}