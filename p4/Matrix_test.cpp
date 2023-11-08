#include <iostream>
#include <vector>
#include "Matrix.h"

using namespace std;

Matrix::Matrix()
{
    rows = 0;
    cols = 0;
}

Matrix::Matrix(vector<vector<double>> d)
{
    data = d;
    rows = d.size();
    cols = d[0].size();
}

void Matrix::print_matrix()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    // Create a matrix using the default constructor
    Matrix A;

    // Create a matrix using the vector constructor
    vector<vector<double>> data = {{1, 2, 3},
                                   {4, 5, 6},
                                   {7, 8, 9}};
    Matrix B(data);

    // Print the matrices
    cout << "Matrix A:" << endl;
    A.print_matrix();
    cout << "Matrix B:" << endl;
    B.print_matrix();

    // Test matrix multiplication
    try {
        Matrix C = A * B;
        cout << "Matrix A * B:" << endl;
        C.print_matrix();
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    // Test matrix addition
    try {
        Matrix D = B + B;
        cout << "Matrix B + B:" << endl;
        D.print_matrix();
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    // Test matrix subtraction
    try {
        Matrix E = B - B;
        cout << "Matrix B - B:" << endl;
        E.print_matrix();
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    // Test scalar multiplication
    Matrix F = B * 2;
    cout << "Matrix B * 2:" << endl;
    F.print_matrix();

    system("pause");

    return 0;
}