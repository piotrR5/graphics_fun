#include "3to2d.h"

Camera::Camera():camera_origin({0,0,-500}),projection_plane({0,0,1,-500}){
    O=Point3(0,0,0, {150,150,150,255});
    X=Point3(50,0,500, {0,0,255}); Xa1=Point3(40,5,500, {0,0,255}); Xa2=Point3(40,-5,500, {0,0,255}); 
    Y=Point3(0,50,500, {0,255,0}); Ya1=Point3(5,40,500, {0,255,0}); Ya2=Point3(-5,40,500, {0,255,0});
    Z=Point3(0,0,550, {255,0,0}); Za1=Point3(5,0,540, {255,0,0}); Za2=Point3(-5, 0, 540, {255,0,0});

    axisX=Object3({{O,X}, {X,Xa1}, {X,Xa2}}); 
    axisY=Object3({{O,Y}, {Y,Ya1}, {Y,Ya2}});
    axisZ=Object3({{O,Z}, {Z, Za1}, {Z,Za2}});
}

Camera::Camera(Vec3 o, Vec4 p){
    camera_origin=o;
    projection_plane=p;

    O=Point3(0,0,0, {150,150,150,255});
    X=Point3(50,0,500, {0,0,255}); Xa1=Point3(40,5,500, {0,0,255}); Xa2=Point3(40,-5,500, {0,0,255}); 
    Y=Point3(0,50,500, {0,255,0}); Ya1=Point3(5,40,500, {0,255,0}); Ya2=Point3(-5,40,500, {0,255,0});
    Z=Point3(0,0,550, {255,0,0}); Za1=Point3(5,0,540, {255,0,0}); Za2=Point3(-5, 0, 540, {255,0,0});

    axisX=Object3({{O,X}, {X,Xa1}, {X,Xa2}}); 
    axisY=Object3({{O,Y}, {Y,Ya1}, {Y,Ya2}});
    axisZ=Object3({{O,Z}, {Z, Za1}, {Z,Za2}});
}

/*
    
*/

Vec3 Camera::get_camera_origin(){
    return camera_origin;
}

Vec4 Camera::get_projection_plane(){
    return projection_plane;
}

void Camera::setCameraOrigin(Vec3 o){
    camera_origin=o;
}
void Camera::setProjectionPlane(Vec4 p){
    projection_plane=p;
}

void Camera::moveCamera(Vec3 v){
    camera_origin=add_vectors(camera_origin, v);
    axisX.translate_object(v);
    axisY.translate_object(v);
    axisZ.translate_object(v);
}

vector<Object2> projection(Camera camera, std::vector<Object3> objects){
    std::vector<Object2>returned;

    for(auto& object : objects){
        Object2 tempObject;
         
        for(auto& vertexVectors:object.getVertices()){
            std::vector<Point2>tempVec2;


            for(auto& v:vertexVectors){
                if(distance_from_camera(camera.get_camera_origin(), v.makeVec3())<5 ||
                    !isVecInFrontOfCamera(v.makeVec3(),camera))break;

                Vec3 intersection=intersection_point(camera, v.makeVec3());
                Vec2 point_on_plane=find_point_coordinates_on_plane(camera, intersection);
                tempVec2.push_back({point_on_plane.x, point_on_plane.y, v.color});
            }
            tempObject.getVertices().push_back(tempVec2);
        }
        returned.push_back(tempObject);
    }
    return returned;
}

Vec2 find_point_coordinates_on_plane(Camera camera, Vec3 p){
    return {(p.x-camera.get_camera_origin().x)*1, (p.y-camera.get_camera_origin().y)*1};
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

bool isVecInFrontOfCamera(Vec3 v, Camera cam){
    Vec3 co=cam.get_camera_origin();
    Vec4 pp=cam.get_projection_plane();

    Vec3 cv=subtract_vectors(v,co);
    Vec3 cp=subtract_vectors({pp.x,pp.y,pp.z}, {0,0,0});

    double angle=angleBetweenVectors(cp,cv);

    if(angle > 3.14/2 || angle > FIELD_OF_VIEW)return false;
    return true;
}

