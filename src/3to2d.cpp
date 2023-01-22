#include "3to2d.h"

Camera::Camera():camera_origin({0,0,0}),projection_plane({1,0,0,100}){
}

Vec3 Camera::get_camera_origin(){
    return camera_origin;
}

Vec4 Camera::get_projection_plane(){
    return projection_plane;
}

vector<Object2> projection(Camera _camera, vector<Object3> objects){

}

Vec3 intersection_point(Camera _camera, Vec3 vertex){
    Vec3 return_point;
    Vec3 point_camera_vector{
        _camera.get_camera_origin().x-vertex.x,
        _camera.get_camera_origin().y-vertex.y,
        _camera.get_camera_origin().z-vertex.z
    };
    Vec4 plane=_camera.get_projection_plane();

    double t=-(plane.x*vertex.x+plane.y*vertex.y+plane.z*vertex.z+plane.w)
    /(plane.x*point_camera_vector.x+plane.y*point_camera_vector.y+plane.z*point_camera_vector.z);

    return_point={
        vertex.x+t*point_camera_vector.x,
        vertex.y+t*point_camera_vector.y,
        vertex.z+t*point_camera_vector.z
    }
}

Vec2 find_point_coordinates_on_plane(Camera _camera, Vec3 _intersection_point){
    double camera_angle_vertical, camera_angle_horizontal, point_angle_horizontal, point_angle_vertical;
    
}

double distance_from_camera(Vec3 _camera_origin ,Vec3 vertex){
    return sqrt((camera_origin.x-vertex.x)*(camera_origin.x-vertex.x)+
    (camera_origin.y-vertex.y)*(camera_origin.y-vertex.y)+
    (camera_origin.z-vertex.z)*(camera_origin.z-vertex.z));
}