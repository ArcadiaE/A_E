#include <iostream>
#include "Matrix.h"

class Perceptron {
public:
    Perceptron(Matrix w, Matrix b, Matrix i);
//	Perceptron();
	Matrix feedforward();
	void update( /*YOUR INPUT*/Matrix correct_output, double learning_rate);
	void display() const;

private:
	Matrix weights;
	Matrix bias;
	Matrix input;
	Matrix output;

};
