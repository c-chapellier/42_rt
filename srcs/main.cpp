#include "engine/Engine.hpp"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    try
    {
        if (argc < 2)
            throw std::string("Usage: ") + argv[0] + " <config file>";

        Engine engine(argv[1]);
        
        engine.run(); 
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


// void perlinNoise(int height, int width)
// {
//     std::vector<std::vector<Vector*>> vectors;
//     vectors.resize(height, std::vector<Vector*>(width));

//     for(int h = 0; h < height; ++h){
//         std::vector<Vector*> tmp;
//         for (int w = 0; w < width; ++w){
//             double x = (double)(rand() % 100) / 100;
//             double y = 1 - pow(x, 2);
//             x = rand() % 2 == 0 ? (x) : (-x);
//             y = rand() % 2 == 0 ? (y) : (-y);
//             tmp.push_back(new Vector(x, y, 0));
//         }
//         vectors.push_back(tmp);
//     }

//     int x = rand() % width - 1;
//     int y = rand() % height - 1;
//     Point p(x, y, 0);
//     Vector v1(x, y, 0, p);
//     Vector v2(x + 1, y, 0, p);
//     Vector v3(x + 1, y + 1, 0, p);
//     Vector v4(x, y + 1, 0, p);
//     double res1 = v1.scalarProduct(vectors[y][x]);
//     double res2 = v2.scalarProduct(vectors[y + 1][x]);
//     double res3 = v3.scalarProduct(vectors[y + 1][x + 1]);
//     double res4 = v4.scalarProduct(vectors[y][x + 1]);
// }