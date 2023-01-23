#include "shader.h"


ConstColorShader::ConstColorShader(Color_RGBA _color) : color(_color){};

Color_RGBA ConstColorShader::shade(Point2 p){return color;}

LinearInterpolationShader::LinearInterpolationShader(Point2 _a, Point2 _b) : a(_a), b(_b){};

Color_RGBA LinearInterpolationShader::shade(Point2 m){
    double f=0.0;
    if(b.x-a.x)f=(m.x-a.x)/(b.x-a.x);
    else if(b.y-a.y)f=(m.y-a.y)/(b.y-a.y);

    Color_RGBA ret;

    ret.r=(b.color.r - a.color.r) * f + a.color.r;
    ret.g=(b.color.g - a.color.g) * f + a.color.g;
    ret.b=(b.color.b - a.color.b) * f + a.color.b;
    ret.a=(b.color.a - a.color.a) * f + a.color.a;


    return ret;
}
