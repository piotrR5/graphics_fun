#include "mathUtils.h"
#include "model3d.h"

Object3::Object3():axis({0,0,0}){}

Object3::Object3(std::vector<std::vector<Point3>>v):vertices(v), axis(determineAxis(*this)){}

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

Object3::Object3(std::vector<std::vector<Point3>>v, Vec3 a):vertices(v), axis(a){}

Object3::Object3(Vec3 a):axis(a){}

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
    for(auto& o:v)vertices.push_back(o);
}

void Object3::addVertices(std::vector<std::vector<Vec3>>v){
    for(auto& o:v){
        std::vector<Point3> temp;
        for(auto& i:o){
            temp.push_back(Point3(i));
        } 
        vertices.push_back(temp);
    }
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

void Object3::scale_object(double scale){
    for(size_t i=0; i<vertices.size(); i++){
        for(size_t j=0; j<vertices[i].size(); j++){
            Vec3 axis_to_point_vector=subtract_vectors(vertices[i][j].makeVec3(),axis);
            vertices[i][j]=add_vectors(axis,{axis_to_point_vector.x*scale,axis_to_point_vector.y*scale,axis_to_point_vector.z*scale});
        }
    }
}   

void Object3::set_object_position(Vec3 position){
    Vec3 move_to_pos_vector=subtract_vectors(position,axis);
    translate_object(move_to_pos_vector);
}

void Object3::rotate_object_x(double angle){
    auto rotationMatrix=rx_elementary_rotation(angle);
    for(auto& i:vertices){
        for(auto& j:i){
            j=add_vectors(axis,matrix_to_vector3(multip_matrix(rotationMatrix,vector3_to_matrix(subtract_vectors(j.makeVec3(),axis)))));
        }
    }
}

void Object3::rotate_object_y(double angle){
    auto rotationMatrix=ry_elementary_rotation(angle);
    for(auto& i:vertices){
        for(auto& j:i){
            j=add_vectors(axis,matrix_to_vector3(multip_matrix(rotationMatrix,vector3_to_matrix(subtract_vectors(j.makeVec3(),axis)))));
        }
    }
}

void Object3::rotate_object_z(double angle){
    auto rotationMatrix=rz_elementary_rotation(angle);
    for(auto& i:vertices){
        for(auto& j:i){
            j=add_vectors(axis,matrix_to_vector3(multip_matrix(rotationMatrix,vector3_to_matrix(subtract_vectors(j.makeVec3(),axis)))));
        }
    }
}

std::vector<std::vector<Point3>>& Object3::getVertices(){
    return vertices;
}

Vec3& Object3::getAxis(){
    return axis;
}








