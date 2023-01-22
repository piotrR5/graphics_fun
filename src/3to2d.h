#include <vector>
#include <cmath>
#include "mathUtils.h"
#include "model3d.h"
#include "model2d.h"
#include "constants.h"

#ifndef _3TO2D
#define _3TO2D

class Camera{
    
    Vec3 camera_origin;
    Vec4 projection_plane;

    public:
    Camera();
    Camera(){};

    Vec3 get_camera_origin();

    Vec4 get_projection_plane();
}

vector<Object2> projection(Camera _camera,vector<Object3> objects);

Vec3 intersection_point(Camera _camera, Vec3 vertex);

Vec2 find_point_coordinates_on_plane(Camera _camera, Vec3 _intersection_point);

double distance_from_camera(Vec3 _camera_origin ,Vec3 vertex);

#endif