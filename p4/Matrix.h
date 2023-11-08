//=============================================================================
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================


#ifndef __MATRIX_H__
#define __MATRIX_H__

//
// matrix.h
//

#include <vector>

using namespace std;


extern vector<vector<double> > CreateVector(int rows, int cols, const double * value);


class Matrix
{
public:
    Matrix(int rows = 3,int cols = 3) : data(rows, vector<double> (cols)), rows(rows), cols(cols) {}
    Matrix(vector<vector<double> > elements);
//    Matrix(vector<vector<double> > &elements);
    Matrix operator+ (const Matrix &c2) const;
    Matrix operator- (const Matrix &c2) const;
    Matrix operator* (const Matrix &c2) const;
    Matrix operator* (double num) const;

//    void setMatrix();
    void printMatrix() const;
//    int getSize() const {return rows * cols;}
    double &element(int i, int j){return data.at(i).at(j);}
    double element(int i, int j) const {return data.at(i).at(j);}
    Matrix transpos() const;

	//Matrix operator*(Matrix& mat);
	//Matrix operator+(Matrix& mat);
	//Matrix operator-(Matrix& mat);
	//Matrix operator*(double num);

private:
    vector<vector<double> > data;
	int rows;
	int cols;
};

/*
class Matrix {
public:
    Matrix(int size = 2);
    ~Matrix();
    void setMatrix(const double * vaule);
    void printMatrix() const;
    int getSize() const {return size;}
    double &element(int i, int j){return elements[i * size+j];}
    double element(int i, int j) const {return elements[i * size+j];}
private:
    int size;
    double * elements;

};
*/

#endif  //__MATRIX_H__
