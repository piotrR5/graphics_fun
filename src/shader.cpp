#include "shader.h"


ConstColorShader::ConstColorShader(Color_RGBA _color) : color(_color){};

Color_RGBA ConstColorShader::shade(Point2 p){return color;}
