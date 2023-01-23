#include "mathUtils.h"
#include <vector>
#include <iostream>
#include <ctime>

//TODO:
/*
    linear interpolation shader
    black and white shader
    inversed colors shader
    static color shader
    different noises shaders
    :3

    

*/

class Shader{
public:
    virtual Color_RGBA shade(Point2) = 0;
};

class ConstColorShader : public Shader{
    Color_RGBA color;
public:
    ConstColorShader(Color_RGBA);
    Color_RGBA shade(Point2);
};

class LinearInterpolationShader : public Shader{
    Point2 a,b;
public:
    LinearInterpolationShader(Point2 _a, Point2 _b);
    Color_RGBA shade(Point2);
};
