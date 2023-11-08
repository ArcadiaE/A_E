#include <iostream>
#include "Matrix.h"

class Perceptron {
private:
	Matrix weights;
	Matrix bias;
	Matrix input;
	Matrix output;

public:
    
	Perceptron();
	Perceptron(Matrix w, Matrix b, Matrix i);
	Matrix feedforward();
	void update(Matrix correct_output, double learning_rate);
    friend std::ostream& operator<<(std::ostream& out, Perceptron& p) {
    out << "Weights: " << std::endl << p.weights << std::endl;
    out << "Bias: " << std::endl << p.bias << std::endl;
    out << "Input: " << std::endl << p.input << std::endl;
    out << "Output: " << std::endl << p.output << std::endl;
    return out;
}

};

Perceptron::Perceptron()
{
	weights = Matrix();
	bias = Matrix();
	input = Matrix();
	output = Matrix();
}

Perceptron::Perceptron(Matrix w, Matrix b, Matrix i)
{
	weights = w;
	bias = b;
	input = i;
	output = Matrix();
}

Matrix Perceptron::feedforward()
{
	Matrix weighted_input = weights * input;
	Matrix biased_input = weighted_input + bias;
	output = biased_input;  // Identity activation function
	return output;
}

void Perceptron::update(Matrix correct_output, double learning_rate)
{
	Matrix error = correct_output - output;
	Matrix delta = error * learning_rate;
	Matrix weights_transpose = weights.transpose();
	Matrix weight_update = delta * input;
	Matrix bias_update = delta;
	weights = weights + weight_update;
	bias = bias + bias_update;
}

