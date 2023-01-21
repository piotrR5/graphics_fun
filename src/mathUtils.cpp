#include "mathUtils.h"

vector<vector<double>> inverse_matrix(vector<vector<double>> matrix){ //https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    vector<vector<double>> return_matrix;
    double inv[16],invOut[16] , det;
    int i,p=0;
    double m[16];
    for(int i=0; i<matrix.size(); i++){
        for(int j=0; j<matrix.size(); j++){
            m[p]=matrix[i][j];
            p++;
        }
    }

    inv[0] = m[5]  * m[10] * m[15] -
             m[5]  * m[11] * m[14] -
             m[9]  * m[6]  * m[15] +
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] -
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] +
              m[4]  * m[11] * m[14] +
              m[8]  * m[6]  * m[15] -
              m[8]  * m[7]  * m[14] -
              m[12] * m[6]  * m[11] +
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] -
             m[4]  * m[11] * m[13] -
             m[8]  * m[5] * m[15] +
             m[8]  * m[7] * m[13] +
             m[12] * m[5] * m[11] -
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] +
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] -
               m[8]  * m[6] * m[13] -
               m[12] * m[5] * m[10] +
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] +
              m[1]  * m[11] * m[14] +
              m[9]  * m[2] * m[15] -
              m[9]  * m[3] * m[14] -
              m[13] * m[2] * m[11] +
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] -
             m[0]  * m[11] * m[14] -
             m[8]  * m[2] * m[15] +
             m[8]  * m[3] * m[14] +
             m[12] * m[2] * m[11] -
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] +
              m[0]  * m[11] * m[13] +
              m[8]  * m[1] * m[15] -
              m[8]  * m[3] * m[13] -
              m[12] * m[1] * m[11] +
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] -
              m[0]  * m[10] * m[13] -
              m[8]  * m[1] * m[14] +
              m[8]  * m[2] * m[13] +
              m[12] * m[1] * m[10] -
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] -
             m[1]  * m[7] * m[14] -
             m[5]  * m[2] * m[15] +
             m[5]  * m[3] * m[14] +
             m[13] * m[2] * m[7] -
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] +
              m[0]  * m[7] * m[14] +
              m[4]  * m[2] * m[15] -
              m[4]  * m[3] * m[14] -
              m[12] * m[2] * m[7] +
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] -
              m[0]  * m[7] * m[13] -
              m[4]  * m[1] * m[15] +
              m[4]  * m[3] * m[13] +
              m[12] * m[1] * m[7] -
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] +
               m[0]  * m[6] * m[13] +
               m[4]  * m[1] * m[14] -
               m[4]  * m[2] * m[13] -
               m[12] * m[1] * m[6] +
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
              m[1] * m[7] * m[10] +
              m[5] * m[2] * m[11] -
              m[5] * m[3] * m[10] -
              m[9] * m[2] * m[7] +
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
             m[0] * m[7] * m[10] -
             m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] -
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
               m[0] * m[7] * m[9] +
               m[4] * m[1] * m[11] -
               m[4] * m[3] * m[9] -
               m[8] * m[1] * m[7] +
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
              m[0] * m[6] * m[9] -
              m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    vector<double> matrix_row;
    matrix_row.push_back(invOut[0]);
    matrix_row.push_back(invOut[1]);
    matrix_row.push_back(invOut[2]);
    matrix_row.push_back(invOut[3]);
    return_matrix.push_back(matrix_row);
    matrix_row.erase(matrix_row.begin(), matrix_row.end());
    matrix_row.push_back(invOut[4]);
    matrix_row.push_back(invOut[5]);
    matrix_row.push_back(invOut[6]);
    matrix_row.push_back(invOut[7]);
    return_matrix.push_back(matrix_row);
    matrix_row.erase(matrix_row.begin(), matrix_row.end());
    matrix_row.push_back(invOut[8]);
    matrix_row.push_back(invOut[9]);
    matrix_row.push_back(invOut[10]);
    matrix_row.push_back(invOut[11]);
    return_matrix.push_back(matrix_row);
    matrix_row.erase(matrix_row.begin(), matrix_row.end());
    matrix_row.push_back(invOut[12]);
    matrix_row.push_back(invOut[13]);
    matrix_row.push_back(invOut[14]);
    matrix_row.push_back(invOut[15]);
    return_matrix.push_back(matrix_row);

    return return_matrix;
}


point3::point3(double x, double y, double z){
    this->x=x;
    this->y=y;
    this->z=z;
}

point3::point3(){
    x=0;
    y=0;
    z=0;
}

line3::line3(){
    a=point3(0,0,0);
    b=point3(0,0,0);
}

line3::line3(point3 a, point3 b){
    this->a=a;
    this->b=b;
}

triangle3::triangle3(){
    a=point3(0,0,0);
    b=point3(0,0,0);
    c=point3(0,0,0);
}

triangle3::triangle3(point3 a, point3 b, point3 c){
    this->a=a;
    this->b=b;
    this->c=c;
}

double& matrix4::at(size_t row, char col){
    return data[row][(col=='w' ? 3 : col-'x')];
}

vector<vector<double>> matrix4::multip_matrix(vector<vector<double>> matrix_1, vector<vector<double>> matrix_2){
    vector<vector<double>> return_matrix;
    for(int i=0; i<matrix_1.size(); i++){
        vector<double> matrix_row;
        double sum=0;
        for(int j=0; j<matrix_1.size(); j++){
            for(int k=0; k<matrix_1.size(); k++){
                sum+=matrix_1[i][k]*matrix_2[k][j];
            }
            matrix_row.push_back(sum);
            sum=0;
        }
        return_matrix.push_back(matrix_row);
    }
    return return_matrix;
}





point2::point2(double x, double y){
    this->x=x;
    this->y=y;
}

point2::point2(){
    x=0;
    y=0;
}

line2::line2(point2 a, point2 b){
    this->a=a;
    this->b=b;
}

line2::line2(){
    a=point2();
    b=point2();
}

triangle2::triangle2(point2 a, point2 b, point2 c){
    this->a=a;
    this->b=b;
    this->c=c;
}

triangle2::triangle2(){
    a=point2();
    b=point2();
    c=point2();
}

double& matrix3::at(size_t row, char col){
    return data[row][col-'x'];
}