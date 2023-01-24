#include "mathUtils.h"
#include "model3d.h"

Object3::Object3(){
    axis={0,0,0};
}

Object3::Object3(std::vector<std::vector<Point3>>v){
    vertices=v;
    axis=determineAxis(*this);
}

Object3::Object3(std::vector<std::vector<Vec3>>v){
    for(auto& i:v){
        std::vector<Point3>temp;
        for(auto& j:i){
            temp.push_back({j.x, j.y, j.z});
        }
        vertices.push_back(temp);
    }
    axis=determineAxis(*this);
}

Object3::Object3(std::vector<std::vector<Point3>>v, Vec3 a){
    vertices=v;
    axis=a;
}

Object3::Object3(Vec3 a){
    axis=a;
}

Vec3 determineAxis(Object3 _object){
    Vec3 return_axis={0,0,0};
    int points_count=0;
    for(auto& i:_object.getVertices()){
        for(auto& j:i){
            return_axis=add_vectors(return_axis,j.makeVec3());
            points_count++;
        }
    }
    return {return_axis.x/points_count, return_axis.y/points_count, return_axis.z/points_count};
}

void Object3::addVertices(std::vector<std::vector<Point3>>v){
    for(auto o:v)vertices.push_back(o);
}

void Object3::setAxis(Vec3 a){
    axis=a;
}

void Object3::translate_object(Vec3 v){
    for(size_t i=0; i<vertices.size(); i++){
        for(size_t j=0; j<vertices[i].size(); j++){
            vertices[i][j]=add_vectors(vertices[i][j].makeVec3(),v);
        }
    }
    axis=add_vectors(axis,v);
}

std::vector<std::vector<Point3>>& Object3::getVertices(){
    return vertices;
}

Vec3& Object3::getAxis(){
    return axis;
}