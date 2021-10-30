#pragma once

#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <thread>

#include <list>
#include <map>

#include "window/Window.hpp"
#include "visuals/Camera.hpp"
#include "light/Light.hpp"
#include "colorManager/ColorManager.hpp"
#include "color/Color.hpp"

#include "loadingBar/LoadingBar.hpp"
#include "../include/nlohmann/json.hpp"

#include "objects/Object.hpp"
#include "objects/Plane.hpp"
#include "objects/components/Line.hpp"
#include "objects/Quadratic.hpp"
#include "objects/Polygone.hpp"
#include "objects/factories/AlphaFactory.hpp"
#include "objects/factories/PolygoneFactory.hpp"
#include "objects/factories/ShapeFactory.hpp"

#include "blackObjects/BlackObject.hpp"
#include "blackObjects/BlackSphere.hpp"
#include "blackObjects/BlackCylinder.hpp"


#include "headers/define.hpp"

#include "saver/Saver.hpp"
#include "parser/Parser.hpp"
#include "config/Config.hpp"
