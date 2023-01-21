#include "mathUtils.h"
#include "model2d.h"

Object2::Object2(){
    axis=point2();
}

Object2::Object2(std::vector<std::vector<point2>>v){
    vertices=v;
    axis=point2();
}

Object2::Object2(std::vector<std::vector<point2>>v, point2 a){
    vertices=v;
    axis=a;
}

Object2::Object2(point2 a){
    axis=a;
}

void Object2::addVertices(std::vector<std::vector<point2>>v){
    for(auto o:v)vertices.push_back(o);
}

void Object2::setAxis(point2 a){
    axis=a;
}

std::vector<std::vector<point2>>& Object2::getVertices(){
    return vertices;
}

point2& Object2::getAxis(){
    return axis;
}
