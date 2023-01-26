#include <vector>
#include <cmath>
#include "mathUtils.h"
#include "model3d.h"
#include "model2d.h"
#include "constants.h"

#ifndef _3TO2D
#define _3TO2D

/*
    3to2d.h contains camera implementation and a functions which are meant to breach the gap between 3D and 2D spaces using projection
*/

class Camera{

    
    
    Vec3 camera_origin;
    Vec4 projection_plane;

    public:

    Point3 
        O, 
        X, Xa1, Xa2, 
        Y, Ya1, Ya2,
        Z, Za1, Za2;
    
    Object3 axisX, axisY, axisZ;

    Camera();
    Camera(Vec3, Vec4);

    Vec3 get_camera_origin();

    Vec4 get_projection_plane();

    void setCameraOrigin(Vec3 o);

    void setProjectionPlane(Vec4 p);

    void moveCamera(Vec3 v);
};

/*
    main projection function, it invokes utility functions to return vector of Object2 made by projecting vector of Object3 onto the screen
*/
vector<Object2> projection(Camera _camera,vector<Object3> objects);

/*
    function returns an intersetion point between camera-vertex line and the camera plane
*/
Vec3 intersection_point(Camera _camera, Vec3 vertex);

/*
    function which return the 2D position of a point on a plane, regarding that plane
*/
Vec2 find_point_coordinates_on_plane(Camera _camera, Vec3 _intersection_point);

/*
    function return distance of a given vertex from the camera origin point
*/
double distance_from_camera(Vec3 _camera_origin ,Vec3 vertex);


bool isVecInFrontOfCamera(Vec3 v, Camera cam);



#endif