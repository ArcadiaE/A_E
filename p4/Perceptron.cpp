#include "Perceptron.h"

#include <cstdlib>

Perceptron::Perceptron(Matrix w, Matrix b, Matrix i) : weights(w), bias(b), input(i){}

Matrix Perceptron::feedforward()
{
    output = weights * input + bias;
	return output;
}

void Perceptron::update(/*YOUR INPUT*/Matrix correct_output, double learning_rate)
{
    Matrix error = correct_output - feedforward();
	Matrix delta = error * learning_rate;
	Matrix weights_transpose = weights.transpos();
	Matrix weight_update = delta * input;
	Matrix bias_update = delta;
	weights = weights + weight_update;
	bias = bias + bias_update;
}

void Perceptron::display() const{

    cout << "Weights:\t";
         weights.printMatrix();
    cout << "Bias:\t";
         bias.printMatrix();
    cout << "Input:\t";
         input.printMatrix();
    cout << "Output:\t";
         output.printMatrix();
    cout<<endl;
}

//Include any functions which may be useful to you (e.g. print functions)

// input 1xn
// weights nx1
// bias 1x1
// output 1x1

//output = weights * input + bias;
//input 1x3 weights 3x1
// n=0
//weight = rand
//eta
//omega(n+1)=omega(n)+eta[d(n)-y(n)]x(n)
