#include "mathUtils.h"

double& matrix4::at(size_t row, char col){
    return data[row][(col=='w' ? 3 : col-'x')];
}

double& matrix3::at(size_t row, char col){
    return data[row][col-'x'];
}


