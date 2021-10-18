#include "../objects/components/Point.hpp"

class Light
{
private:
    Point *p;

public:
    Light(double px, double py, double pz);
    Light(Point *p);
    ~Light();
};