#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
private:
    vector<vector<double>> data;
    int rows;
    int cols;

public:
    int getrows()const{
        return rows;
    }

    int getcols()const{
        return cols;
    }

    Matrix();
    Matrix(vector<vector<double>> d);
    void print_matrix();
    Matrix operator*(Matrix& mat);
    Matrix operator+(Matrix& mat);
    Matrix operator-(Matrix& mat);
    Matrix operator*(double num);
    Matrix transpose();
    friend std::ostream& operator<<(std::ostream& out, Matrix& mat) {
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            out << mat.data[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}
};

Matrix::Matrix() {}

Matrix::Matrix(vector<vector<double>> d)
{
    data = d;
    rows = d.size();
    cols = d[0].size();
}

void Matrix::print_matrix()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

Matrix Matrix::operator*(Matrix& mat)
{
    if (cols != mat.rows)
    {
        throw "Error: Cannot multiply matrices with incompatible dimensions.";
    }

    Matrix result = Matrix(vector<vector<double>>(rows, vector<double>(mat.cols, 0)));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < mat.cols; j++)
        {
            double sum = 0;
            for (int k = 0; k < cols; k++)
            {
                sum += data[i][k] * mat.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

Matrix Matrix::operator+(Matrix& mat)
{
    if (rows != mat.rows || cols != mat.cols)
    {
        throw "Error: Cannot add matrices with incompatible dimensions.";
    }

    Matrix result = Matrix(vector<vector<double>>(rows, vector<double>(cols, 0)));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result.data[i][j] = data[i][j] + mat.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(Matrix& mat)
{
    if (rows != mat.rows || cols != mat.cols)
    {
        throw "Error: Cannot subtract matrices with incompatible dimensions.";
    }

    Matrix result = Matrix(vector<vector<double>>(rows, vector<double>(cols, 0)));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result.data[i][j] = data[i][j] - mat.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(double num)
{
    Matrix result = Matrix(vector<vector<double>>(rows, vector<double>(cols, 0)));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result.data[i][j] = data[i][j] * num;
        }
    }
    return result;
}

Matrix Matrix::transpose()
{
    Matrix result = Matrix(vector<vector<double>>(cols, vector<double>(rows, 0)));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}