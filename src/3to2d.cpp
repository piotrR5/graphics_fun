#include "3to2d.h"

Camera::Camera():camera_origin({0,0,-500}),projection_plane({0,0,1,-500}){
}

Camera::Camera(Vec3 o, Vec4 p){
    camera_origin=o;
    projection_plane=p;
}

Vec3 Camera::get_camera_origin(){
    return camera_origin;
}

Vec4 Camera::get_projection_plane(){
    return projection_plane;
}

vector<Object2> projection(Camera camera, std::vector<Object3> objects){

    std::vector<Object2>returned;

    for(auto& object : objects){
        Object2 o_temp;
        bool toRender=true;
        for(auto& vertexVectors:object.getVertices()){
            std::vector<Point2>vec2_temp;
            for(auto& v:vertexVectors)  if(distance_from_camera(camera.get_camera_origin(), v.makeVec3())<5 || v.z-camera.get_camera_origin().z <0){
                                            toRender=false;
                                            break;
                                        }  
            if(toRender==false){
                toRender=true;
                continue;
            }


            for(auto& v:vertexVectors){
                Vec3 intersection=intersection_point(camera, v.makeVec3());
                Vec2 point_on_plane=find_point_coordinates_on_plane(camera, intersection);
                vec2_temp.push_back({point_on_plane.x, point_on_plane.y});
            }
            o_temp.getVertices().push_back(vec2_temp);
        }
        returned.push_back(o_temp);
    }
    return returned;
}

Vec2 find_point_coordinates_on_plane(Camera camera, Vec3 p){
    return {p.x*3, p.y*3};
}

Vec3 intersection_point(Camera _camera, Vec3 vertex){
    Vec3 return_point;
    Vec4 plane=_camera.get_projection_plane();
    Vec3 origin=_camera.get_camera_origin();
    Vec3 point_camera_vector{
        origin.x-vertex.x,
        origin.y-vertex.y,
        origin.z-vertex.z
    };
    

    double t=-(plane.x*(vertex.x - origin.x) + plane.y*(vertex.y - origin.y) + plane.z*(vertex.z - origin.z) + plane.w)/(point_camera_vector.x*plane.x + point_camera_vector.y*plane.y + point_camera_vector.z*plane.z);

    return_point={
        vertex.x+t*point_camera_vector.x,
        vertex.y+t*point_camera_vector.y,
        vertex.z+t*point_camera_vector.z
    };

    return return_point;
}

double distance_from_camera(Vec3 camera_origin ,Vec3 vertex){
    return sqrt((camera_origin.x-vertex.x)*(camera_origin.x-vertex.x)+
    (camera_origin.y-vertex.y)*(camera_origin.y-vertex.y)+
    (camera_origin.z-vertex.z)*(camera_origin.z-vertex.z));
}