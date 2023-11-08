#include <iostream>
#include "Perceptron.h"

int main()
{
    // Define input, weights, and bias
    Matrix input(std::vector<std::vector<double>>{{1}, {0}, {1}});
    Matrix weights(std::vector<std::vector<double>>{{0.5, -0.7, 0.3}});
    Matrix bias(std::vector<std::vector<double>>{{-0.1}});

    // Create perceptron object
    Perceptron p(weights, bias, input);

    // Test feedforward
    Matrix output = p.feedforward();
    std::cout << "Output before training:" << std::endl;
    std::cout << output << std::endl;

    // Define correct output and learning rate
    Matrix correct_output(std::vector<std::vector<double>>{{0}});
    double learning_rate = 0.1;

    // Train perceptron
    p.update(correct_output, learning_rate);

    // Test feedforward again
    output = p.feedforward();
    std::cout << "Output after training:" << std::endl;
    std::cout << output << std::endl;

    system("pause");

    return 0;
}