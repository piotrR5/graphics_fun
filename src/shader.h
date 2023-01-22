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
    virtual Color_RGBA shade(Point2 p) = 0;
};

class ConstColorShader : public Shader{
    Color_RGBA color;
public:
    ConstColorShader(Color_RGBA);
    Color_RGBA shade(Point2 p);
};






