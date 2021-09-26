#include "parser/Parser.hpp"
#include "objects/Object.hpp"

int main(int argc, char *argv[])
{
    Parser parser("../configs/sphere.json");

    Object obj("sphere");

    std::cout << obj << std::endl;

    return 0;
}
