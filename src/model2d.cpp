#include "mathUtils.h"
#include "model2d.h"

Object2::Object2(){
    axis=vec2();
}

Object2::Object2(std::vector<std::vector<point2>>v){
    vertices=v;
    axis=vec2();
}

Object2::Object2(std::vector<std::vector<point2>>v, vec2 a){
    vertices=v;
    axis=a;
}

Object2::Object2(vec2 a){
    axis=a;
}

void Object2::addVertices(std::vector<std::vector<point2>>v){
    for(auto o:v)vertices.push_back(o);
}

void Object2::setAxis(vec2 a){
    axis=a;
}

std::vector<std::vector<point2>>& Object2::getVertices(){
    return vertices;
}

vec2& Object2::getAxis(){
    return axis;
}

void Object2::rotate(double a){
    std::vector<std::vector<vec2>>points;
    for(auto& i:vertices){
        points.push_back(std::vector<vec2>());
        for(auto& v:i){
            vec2 old{v.x-axis.x, v.y-axis.y};
            double newX=old.x*std::cos(a) - old.y*std::sin(a);
            double newY=old.x*std::sin(a) + old.y*std::cos(a);
            v.x=newX+axis.x;
            v.y=newY+axis.y;
        }
    }
}

void Object2::move(vec2 vec){
    for(auto& i:vertices){
        for(auto& v:i)v.add(vec);
    }
    axis.add(vec);
}

void Object2::setPos(vec2 vec){
    vec2 toMove{vec.x - axis.x, vec.y - axis.y};
    for(auto& i:vertices){
        for(auto& v:i)v.add(toMove);
    }
    axis=vec;
}

void Object2::scale(double x){
    for(auto& i:vertices){
        for(auto& v:i){
            vec2 old{v.x-axis.x, v.y-axis.y};
            old.x*=x;
            old.y*=x;
            v.x=old.x+axis.x;
            v.y=old.y+axis.y;
        }
    }
}
