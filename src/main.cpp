
#include "global.hpp"
#include "engine/Engine.hpp"

int debug = 0;

int main(int argc, char *argv[])
{
    if (argc != 3) return 1;

    try
    {
        Engine(argv[1], argv[2]).run();
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (const std::string& e)
    {
        std::cerr << e << std::endl;
    }
    catch (const char *e)
    {
        std::cerr << e << std::endl;
    }
    catch (...)
    {
        std::cerr << "catch something else" << std::endl;
    }

    return 1;
};
