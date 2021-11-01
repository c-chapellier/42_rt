#include "engine/Engine.hpp"

// std::vector<std::vector<Vector*>> GRADIENT;
// void perlinNoise(int height, int width);

int main(int argc, char *argv[])
{
    srand(time(NULL));

    try
    {
        if (argc < 2)
            throw std::string("Usage: ") + argv[0] + " <config file>";

        Engine engine(argv[1]);
        
        engine.run();
        //perlinNoise(10, 10);
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

// float interpolate(float a0, float a1, float w) {
//     return ((1.0 - w) * a0) + (w * a1);
// }

// float dotGridGradient(int ix, int iy, float x, float y) {
//     // Compute the distance vector
//     float dx = x - (float)ix;
//     float dy = y - (float)iy;

//     // Compute the dot-product
//     return (dx * GRADIENT[iy][ix]->getX()) + (dy * GRADIENT[iy][ix]->getY());
// }

// float perlin(float x, float y) {
//     int x0 = floor(x);
//     int x1 = x0 + 1;
//     int y0 = floor(y);
//     int y1 = y0 + 1;

//     float sx = x - (float)x0;
//     float sy = y - (float)y0;

//     float n0, n1, ix0, ix1, value;
//     n0 = dotGridGradient(x0, y0, x, y);
//     n1 = dotGridGradient(x1, y0, x, y);
//     ix0 = interpolate(n0, n1, sx);
//     n0 = dotGridGradient(x0, y1, x, y);
//     n1 = dotGridGradient(x1, y1, x, y);
//     ix1 = interpolate(n0, n1, sx);
//     value = interpolate(ix0, ix1, sy);
//     return value;
// }

// void initGradient(int height, int width) {
//     for(int h = 0; h < height + 1; ++h){
//         std::vector<Vector*> tmp;
//         for (int w = 0; w < width + 1; ++w){
//             double x = (double)(rand() % 100) / 100.0f;
//             double y = 1.0 - pow(x, 2);
//             x = rand() % 2 == 0 ? (x) : (-x);
//             y = rand() % 2 == 0 ? (y) : (-y);
//             tmp.push_back(new Vector(x, y, 0));
//         }
//         GRADIENT.push_back(tmp);
//     }
// }

// void perlinNoise(int height, int width)
// {
    
//     initGradient(height, width);

//     std::vector<std::vector<double>> res;
//     for(int h = 0; h < height; ++h){
//         std::vector<double> tmp;
//         for (int w = 0; w < width; ++w){
//             tmp.push_back(perlin(w + 0.5, h + 0.5));
//         }
//         res.push_back(tmp);
//     }

//     for(int h = 0; h < height; ++h){
//         for (int w = 0; w < width; ++w){
//             std::cout << res[h][w] << " ";
//         }
//         std::cout << std::endl;
//     }
// }