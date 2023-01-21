#include "mathUtils.h"
#include "model3d.h"

Object3::Object3(){
    axis=point3();
}

Object3::Object3(std::vector<std::vector<point3>>v){
    vertices=v;
    axis=point3();
}

Object3::Object3(std::vector<std::vector<point3>>v, point3 a){
    vertices=v;
    axis=a;
}

Object3::Object3(point3 a){
    axis=a;
}

void Object3::addVertices(std::vector<std::vector<point3>>v){
    for(auto o:v)vertices.push_back(o);
}

void Object3::setAxis(point3 a){
    axis=a;
}

std::vector<std::vector<point3>>& Object3::getVertives(){
    return vertices;
}

point3& Object3::getAxis(){
    return axis;
}