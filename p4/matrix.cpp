//
// Matrix.cpp
//
// implementation of matrix class
//


#include "Matrix.h"

#include <iostream>
//#include <iterator>
//#include <algorithm>

using namespace std;



Matrix::Matrix(vector<vector<double> > elements) : data(elements), rows(elements.size()), cols(elements[0].size()) {}

Matrix Matrix::operator+ (const Matrix &c2) const{

    if(rows != c2.rows || cols != c2.cols)
        return Matrix(1,1);
    Matrix elements(data);
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            elements.data[i][j] += c2.data[i][j];
    return elements;
}

Matrix Matrix::operator- (const Matrix &c2) const{

    if(rows != c2.rows || cols != c2.cols)
        return Matrix(1,1);
    Matrix elements(data);
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            elements.data[i][j] -= c2.data[i][j];
    return elements;
}

Matrix Matrix::operator* (const Matrix &c2) const{

    if(cols != c2.rows)
        return Matrix(1,1);
    vector<vector<double> > elements(rows, vector<double> (c2.cols));
    for(int i=0;i<rows;i++)
        for(int j=0, sum=0;j<c2.cols;j++)
        {
            for(int k=0;k<cols;k++)
                sum+= data[i][k] * c2.data[k][j];
            elements[i][j] = sum;
            sum = 0;
        }
    return Matrix(elements);
}
Matrix Matrix::operator* (double num) const{

    Matrix elements(data);
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            elements.data[i][j] *= num;
    return elements;
}
void Matrix::printMatrix() const{

    cout<<rows<<"x"<<cols<<" matrix:"<<endl;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
            cout<<data[i][j]<<"\t";
            cout<<endl;
    }
}

Matrix Matrix::transpos() const{

    vector<vector<double> > elements(cols, vector<double> (rows));
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            elements[j][i] = data[i][j];
    return Matrix(elements);
}
vector<vector<double> > CreateVector(int rows, int cols, const double * value)
{
    vector<vector<double> >  data(rows, vector<double> (cols));
//    int size = rows * cols;
        for(int i=0, sum=0;i<rows;i++)
            for(int j=0;j<cols;j++)
            {
                data.at(i).at(j)= value[sum];
                sum++;
            }

  return data;
}

/*

void Matrix::setMatrix(const double *values){
    for(int i = 0;i< size * size;i++)
        elements[i]=values[i];
}

*/

//Matrix::Matrix(int size /* =2 */) : size(size)
//{
//    elements = new double[size *size];
//}

/*
Matrix::~Matrix(){
    delete[] elements;
}

void Matrix::printMatrix() const{
    cout<<"The Matrix is:"<<endl;
    for(int i=0;i<size;i++)
    {
        for(int j;j<size;j++)
            cout<<element(i,j)<<" ";
            cout<<endl;
    }
}

*/
