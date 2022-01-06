#include "engine/Engine.hpp"

int main()
{
    try
    {
        Engine().run();
        
        IMG_Quit();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (const std::string& e)
    {
        std::cerr << e << '\n';
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    catch (...)
    {
        std::cerr << "catch something else" << '\n';
    }
    return 0;
}
