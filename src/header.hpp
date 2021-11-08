#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include <exception>
#include <thread>
#include <mutex>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

#include <vector>
#include <list>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>

#include "exceptions/NoInterException.hpp"

#include "loadingBar/LoadingBar.hpp"
#include "window/Window.hpp"
#include "visuals/Camera.hpp"
#include "light/Light.hpp"
#include "colorManager/ColorManager.hpp"

#include "color/Color.hpp"
#include "color/Texture.hpp"
#include "color/TextureAplicator.hpp"

#include "../include/nlohmann/json.hpp"

#include "objects/Object.hpp"
#include "objects/Plane.hpp"
#include "objects/Sphere.hpp"
#include "objects/Circle.hpp"
#include "objects/Quadratic.hpp"
#include "objects/Polygone.hpp"

#include "objects/components/Point.hpp"
#include "objects/components/Vector.hpp"
#include "objects/components/Line.hpp"
#include "objects/components/Triangle.hpp"

#include "objects/factories/AlphaFactory.hpp"
#include "objects/factories/PolygoneFactory.hpp"
#include "objects/factories/ShapeFactory.hpp"

#include "blackObjects/BlackObject.hpp"
#include "blackObjects/BlackSphere.hpp"
#include "blackObjects/BlackCylinder.hpp"

#include "solver/Complex.hpp"
#include "solver/EquationSolver.hpp"

#include "headers/define.hpp"

#include "saver/Saver.hpp"
#include "parser/Parser.hpp"
#include "config/Config.hpp"
