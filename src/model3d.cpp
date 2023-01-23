#include "mathUtils.h"
#include "model3d.h"

Object3::Object3(){
    axis=Point3();
}

Object3::Object3(std::vector<std::vector<Point3>>v){
    vertices=v;
    axis=Point3();
}

Object3::Object3(std::vector<std::vector<Vec3>>v){
    for(auto& i:v){
        std::vector<Point3>temp;
        for(auto& j:i){
            temp.push_back({j.x, j.y, j.z});
        }
        vertices.push_back(temp);
    }
}

Object3::Object3(std::vector<std::vector<Point3>>v, Point3 a){
    vertices=v;
    axis=a;
}

Object3::Object3(Point3 a){
    axis=a;
}

void Object3::addVertices(std::vector<std::vector<Point3>>v){
    for(auto o:v)vertices.push_back(o);
}

void Object3::setAxis(Point3 a){
    axis=a;
}

std::vector<std::vector<Point3>>& Object3::getVertives(){
    return vertices;
}

Point3& Object3::getAxis(){
    return axis;
}