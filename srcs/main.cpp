#include "parser/Parser.hpp"
#include "objects/Object.hpp"
#include "objects/Sphere.hpp"

int main(int argc, char *argv[])
{
    Parser parser("../configs/sphere.json");

    Object obj("sphere");
    Sphere sp(0, 0, 0, 0);

    std::cout << obj << std::endl;
    std::cout << sp << std::endl;

    return 0;
}
