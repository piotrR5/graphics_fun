#include <vector>
#include <cstdint>
#include <string>
#include <fstream>
#include <filesystem>

#include "mathUtils.h"

struct Vec3f{
    float x;
    float y;
    float z;
};

#define STL_HEADER_SIZE 80
struct STLObject{
    char header[STL_HEADER_SIZE];
    uint32_t triangle_count = 0;
    Vec3f* points = nullptr;
    Vec3f* normals = nullptr;


    STLObject(){}
    ~STLObject(){
        if(points != nullptr)
            delete[] points;
        if(normals != nullptr)
            delete[] normals;
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

            for(size_t i=0; i<triangle_count; ++i){
                file.read((char*)&normals[i].x, 4);
                file.read((char*)&normals[i].y, 4);
                file.read((char*)&normals[i].z, 4);
                for(size_t j=0; j<3; ++j){
                    file.read((char*)&points[i*3+j].x, 4);
                    file.read((char*)&points[i*3+j].y, 4);
                    file.read((char*)&points[i*3+j].z, 4);
                }
                file.seekg(2,std::ios::cur);
            }

            file.close();
            return 0;
        }
        return 1;
    }

    std::vector<std::vector<Vec3>> getTriangles(){
        std::vector<std::vector<Vec3>>returned;
        for(uint32_t i=0; i<triangle_count; ++i){
            returned.push_back(std::vector<Vec3>());
            for(size_t j=0; j<3; ++j){
                // std::cout<<points[i*3+j].x<<";";
                // std::cout<<points[i*3+j].y<<";";
                // std::cout<<points[i*3+j].z<<" ";
                Vec3 foo;
                foo.x=(double)points[i*3+j].x;
                foo.y=(double)points[i*3+j].y;
                foo.z=(double)points[i*3+j].z;
                returned[returned.size()-1].push_back(foo);
            }
        }
        return returned;
    }

    void printTriangleVertices(){
        for(uint32_t i=0; i<triangle_count; ++i){
            for(size_t j=0; j<3; ++j){
                std::cout<<points[i*3+j].x<<"  ";
                std::cout<<points[i*3+j].y<<"  ";
                std::cout<<points[i*3+j].z<<"  \t";
            }
            std::cout<<"\n";
        }
    }
}; 
