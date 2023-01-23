#include "3to2d.h"

Camera::Camera():camera_origin({0,0,0}),projection_plane({0,0,1,-100}){
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
        for(auto& vertexVectors:object.getVertives()){
            std::vector<Point2>vec2_temp;
            for(auto& v:vertexVectors)  if(distance_from_camera(camera.get_camera_origin(), v.makeVec3())<20 || v.z-camera.get_camera_origin().z <0){
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
    return {p.x, p.y};
}

// vector<Object2> projection(Camera _camera, vector<Object3> objects){
//     std::vector<Object2>returned;

//     // std::cout<<"["<<(int)objects.size()<<"]\n";
//     // exit(0);

//     for(auto& o:objects){
//         Object2 o_temp;
//         for(auto& i:o.getVertives()){
//             std::vector<Point2>v_temp;
//             for(auto& v:i){
//                 Vec2 vec2_temp=find_point_coordinates_on_plane(_camera, intersection_point(_camera, v.makeVec3()));
//                 // std::cout<<"["<<vec2_temp.x<<" "<<vec2_temp.y<<"]\n";
//                 // exit(0);
//                 v_temp.push_back(Point2(vec2_temp.x, vec2_temp.y));
//             }
//             o_temp.getVertices().push_back(v_temp);
//         }
//         returned.push_back(o_temp);
//     }

//     return returned;
// }

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
    };

    // std::cout<<"["<<return_point.x<<" "<<return_point.y<<" "<<return_point.z<<"]\n";
    // exit(0);

    return return_point;
}

// void rotate(Vec3& vec, Vec3 rotation){
//     double newX=vec.x;
//     double newY=vec.y;
//     double newZ=vec.z;

//     //rx
//     newY=vec.y*std::cos(rotation.x) - vec.z*std::sin(rotation.x);
//     newZ=vec.y*std::sin(rotation.x) + vec.z*std::cos(rotation.x);
//     vec={newX, newY, newZ};
    
//     //ry
//     newX=vec.x*std::cos(rotation.y) + vec.z*std::sin(rotation.y);
//     newY=vec.y;
//     newZ=-vec.x*std::sin(rotation.y)+vec.z*std::cos(rotation.y);
//     vec={newX, newY, newZ};

//     //rz
//     newX=vec.x*std::cos(rotation.z) - vec.y*std::sin(rotation.z);
//     newY=vec.x*std::sin(rotation.z)+vec.y*std::cos(rotation.z);
//     newZ=vec.z;
//     vec={newX, newY, newZ};
// }

// std::pair<Camera, Vec3>rotateCameraAndPointToNeutralRotation(Camera camera, Vec3 point){
//     double ax,ay,az;

//     Vec3 c{
//         camera.get_projection_plane().x-camera.get_camera_origin().x,
//         camera.get_projection_plane().y-camera.get_camera_origin().y,
//         camera.get_projection_plane().z-camera.get_camera_origin().z
//     };

//     Vec3 p{
//         point.x-camera.get_camera_origin().x,
//         point.y-camera.get_camera_origin().y,
//         point.z-camera.get_camera_origin().z
//     };

//     ax=c.z ? std::atan(std::tan(c.y/c.z)) : c.x >= 0 ? 0 : 3.14;
//     ay=c.x ? std::atan(std::tan(c.z/c.x)) : c.z >= 0 ? 0 : 3.14;
//     az=c.x ? std::atan(std::tan(c.y/c.x)) : c.y >= 0 ? 0 : 3.14;
//     rotate(c, {ax,ay,az});

//     rotate(p, {ax,ay,az});
    
//     Camera retCam{camera.get_camera_origin(),{c.x, c.y, c.z, camera.get_projection_plane().w}};

//     return {retCam, p};
// }

// Vec2 find_point_coordinates_on_plane(Camera _camera, Vec3 _intersection_point){
//     // double x=_camera.get_projection_plane().x-_camera.get_camera_origin().x;
//     // double y=_camera.get_projection_plane().y-_camera.get_camera_origin().y;
//     // double z=_camera.get_projection_plane().z-_camera.get_camera_origin().z;

//     // double xv=_intersection_point.x-_camera.get_camera_origin().x;
//     // double yv=_intersection_point.y-_camera.get_camera_origin().y;
//     // double zv=_intersection_point.z-_camera.get_camera_origin().z;

//     // double camera_angle_vertical=(y!=0 ? std::atan(y/sqrt(z*z+x*x)) : 0);
//     // double camera_angle_horizontal=(x!=0 ? std::atan(x/z) : 0);

//     // double point_angle_horizontal=(yv!=0 ? std::atan(yv/sqrt(zv*zv+xv*xv)) : 0);
//     // double point_angle_vertical=(xv!=0 ? std::atan(xv/zv) : 0);



//     // double ye=sqrt(z*z + x*x) * std::tan(
//     //     point_angle_vertical - camera_angle_vertical    
//     // );

//     // double xe=x * std::tan(
//     //     point_angle_horizontal - camera_angle_horizontal
//     // );

//     // // std::cout<<"["<<xe<<" "<<ye<<"]\n";
//     // // exit(0);



//     // return {xe,200*ye};

//     auto [rotatedCamera, rotatedVertex] = rotateCameraAndPointToNeutralRotation(_camera, _intersection_point);

//     // std::cout<<"["<<rotatedVertex.x<<" "<<rotatedVertex.y<<"]\n";
//     // exit(0);

//     return {rotatedVertex.x, rotatedVertex.y};


// }

double distance_from_camera(Vec3 camera_origin ,Vec3 vertex){
    return sqrt((camera_origin.x-vertex.x)*(camera_origin.x-vertex.x)+
    (camera_origin.y-vertex.y)*(camera_origin.y-vertex.y)+
    (camera_origin.z-vertex.z)*(camera_origin.z-vertex.z));
}