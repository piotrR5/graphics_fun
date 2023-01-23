#include <cstdint>
#include <string>
#include <fstream>
#include <filesystem>
#include "constants.h"


#include "mathUtils.h"

#include <iostream>

// UNCOMENT IF USED IN Pedor's PROJECT
#define PP

#ifdef PP
#include <vector>
#endif

// UNCOMENT TO IGNORE STL'S OPTIONAL ATTRIBUTE FIELD 
// (IF YOU WANT TO CREATE YOUR OWN OBJECT, IT'S SIMPLER TO IGNORE ARGS THAN TO CREATE THEM YOURSELF)
#define IGNORE_STL_ARGS

// ----------------------------------
// STL format:
// 80 bytes     HEADER (string)
// 4 bytes      TRIANGLE COUNT (uint32_t)
// triangles:
// 4*3 bytes    NORMAL VECTOR (3 floats)
// 4*3*3 bytes  3 POINTs (3*3 floats)
// 2 bytes      PADDING (or attributes)
// ----------------------------------

// ----------------------------------
// STLObject:
// header       STL header (80 char string)
// triangle_count   Number of triangles (uint32)
// points       All points from file (array of Vec3s)
// normals      All normals from file (array of Vec3s)
// attributes   All attributes from file (array of uint16_ts)
// THREE CONSECUTIVE POINTS MAKE UP A TRIANGLE
// To iterate over triangles use:
// for(uint32_t i=0; i<cube.triangle_count; ++i){
//      now points of this triangle are: points[i*3+0], points[i*3+1], points[i*3+2]
//      and it's normal is: normals[i]
// }
// ----------------------------------

struct Vec3f{
    float x;
    float y;
    float z;
};

// file io return codes:
// 0 - ok
// 1 - can't open file
// 2 - defective data

#define STL_HEADER_SIZE 80
struct STLObject{
    char header[STL_HEADER_SIZE];
    uint32_t triangle_count = 0;
    Vec3f* points = nullptr;
    Vec3f* normals = nullptr;
    #ifndef IGNORE_STL_ARGS
    uint16_t* attributes = nullptr;
    #endif


    STLObject(){
        
    }
    ~STLObject(){
        if(points != nullptr)
            delete[] points;
        if(normals != nullptr)
            delete[] normals;
        #ifndef IGNORE_STL_ARGS
        if(attributes != nullptr)
            delete[] attributes;
        #endif
    }
    
    int read_file(const char* filename){
        std::ifstream file(filename, std::ios::in|std::ios::binary);
        if (file.is_open()){
            file.read(header, STL_HEADER_SIZE);
            file.read((char*)&triangle_count, 4);

            auto file_size = std::filesystem::file_size(filename);
            u_int64_t expected_file_size = 80 + 4 + 50 * triangle_count;
            if(file_size != expected_file_size){
                file.close();
                return 2;
            }

            points = new Vec3f[triangle_count*3];
            normals = new Vec3f[triangle_count];
            #ifndef IGNORE_STL_ARGS
            attributes = new u_int16_t[triangle_count];
            #endif

            for(size_t i=0; i<triangle_count; ++i){
                file.read((char*)&normals[i].x, 4);
                file.read((char*)&normals[i].y, 4);
                file.read((char*)&normals[i].z, 4);
                for(size_t j=0; j<3; ++j){
                    file.read((char*)&points[i*3+j].x, 4);
                    file.read((char*)&points[i*3+j].y, 4);
                    file.read((char*)&points[i*3+j].z, 4);
                }
                #ifndef IGNORE_STL_ARGS
                file.read((char*)&attributes[i], 2);
                #endif
                #ifdef IGNORE_STL_ARGS
                file.seekg(2,std::ios::cur);
                #endif
            }

            file.close();
            return 0;
        }
        return 1;
    }

    int write_file(const char* filename){
        if(triangle_count < 1){
            return 2;
        }

        std::ofstream file(filename, std::ios::out|std::ios::binary);
        if (file.is_open()){
            file.write(header, STL_HEADER_SIZE);
            file.write((char*)&triangle_count, 4);

            for(size_t i=0; i<triangle_count; ++i){
                file.write((char*)&normals[i].x, 4);
                file.write((char*)&normals[i].y, 4);
                file.write((char*)&normals[i].z, 4);
                for(size_t j=0; j<3; ++j){
                    file.write((char*)&points[i*3+j].x, 4);
                    file.write((char*)&points[i*3+j].y, 4);
                    file.write((char*)&points[i*3+j].z, 4);
                }
                #ifndef IGNORE_STL_ARGS
                file.write((char*)&attributes[i],2);
                #endif
                #ifdef IGNORE_STL_ARGS
                char padding[2] = {0,0};
                file.write(padding,2);
                #endif
            }

            file.close();
            return 0;
        }
        return 1;
    }

#ifdef PP
    std::vector<std::vector<Vec3>> getTriangles(){
        std::vector<std::vector<Vec3>>returned;
        for(uint32_t i=0; i<triangle_count; ++i){
            returned.push_back(std::vector<Vec3>());
            for(size_t j=0; j<3; ++j){
                Vec3 foo;
                foo.x=(double)points[i*3+j].x;
                foo.y=(double)points[i*3+j].y;
                foo.z=(double)points[i*3+j].z;
                returned[returned.size()-1].push_back(foo);
            }
        }
        return returned;
    }
#endif

    void debug_print(){
        std::cout<<"HEADER: "<<header<<"\n";
        std::cout<<"TRI CNT: "<<triangle_count<<"\n";
        std::cout<<"TRIANGLES: "<<"\n";
        for(uint32_t i=0; i<triangle_count; ++i){
            std::cout<<"Triangle "<<i+1<<": N:";
            std::cout<<normals[i].x<<";";
            std::cout<<normals[i].y<<";";
            std::cout<<normals[i].z<<" P:";
            for(size_t j=0; j<3; ++j){
                std::cout<<points[i*3+j].x<<";";
                std::cout<<points[i*3+j].y<<";";
                std::cout<<points[i*3+j].z<<" ";
            }
            #ifndef IGNORE_STL_ARGS
            std::cout<<"A:"<<attributes[i];
            #endif
            std::cout<<std::endl;
        }
    }
    
};