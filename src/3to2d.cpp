#include "3to2d.h"

Camera::Camera():camera_origin({0,0,-500}),projection_plane({0,0,1,-500}){
    O=Point3(0,0,500);
    X=Point3(50,0,500); Xa1=Point3(40,5,500); Xa2=Point3(40,-5,500); 
    Y=Point3(0,50,500); Ya1=Point3(5,40,500); Ya2=Point3(-5,40,500);
    Z=Point3(0,0,550); Za1=Point3(5,0,540); Za2=Point3(-5, 0, 540);

    axisX=Object3({{O,X}, {X,Xa1}, {X,Xa2}}); 
    axisY=Object3({{O,Y}, {Y,Ya1}, {Y,Ya2}});
    axisZ=Object3({{O,Z}, {Z, Za1}, {Z,Za2}});
}

Camera::Camera(Vec3 o, Vec4 p){
    camera_origin=o;
    projection_plane=p;

    O=Point3(0,0,0);
    X=Point3(50,0,500); Xa1=Point3(40,5,500); Xa2=Point3(40,-5,500); 
    Y=Point3(0,50,500); Ya1=Point3(5,40,500); Ya2=Point3(-5,40,500);
    Z=Point3(0,0,550); Za1=Point3(5,0,540); Za2=Point3(-5, 0, 540);

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
    return {(p.x-camera.get_camera_origin().x)*3, (p.y-camera.get_camera_origin().y)*3};
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