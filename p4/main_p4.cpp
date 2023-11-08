//
//
//
// file: main_p4.cpp
// last modified:
// copyright:
// version:
//
// email:
// web:
//

//#include "complex.h"
//#include "circuit.h"
#include "Matrix.h"
#include "Perceptron.h"

#include <iostream>
#include <cstdlib>
//#include <iomanip>
//#include <iterator>

using namespace std;



int main(/* int argc, char *argv[] */ )
{
 //   istream_iterator<double> i1(cin), i2;
//    vector<double> s1(i1,i2);
    cout<<"__cplusplus = "<<__cplusplus<<endl;

    Matrix m1(3,4);
    m1.printMatrix();
    double temp1[] ={1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,3.0,7.0,1.0};
    Matrix m2(CreateVector(4,3,temp1));
    m2.printMatrix();
    m1=m2;
    m1.printMatrix();
    m1.element(0,0) = 2.0;

    m1.printMatrix();
    m2.printMatrix();
    m1 = m1 + m2;
    m1.printMatrix();

    m1.printMatrix();
    m2.printMatrix();
    m1 = m1 - m2;
    m1.printMatrix();

    m1.printMatrix();
    m1 = m1 * -2;
    m1.printMatrix();
/*
    m1.printMatrix();
    m2.printMatrix();
    m1 = m1 * m2;
    m1.printMatrix();
*/

    double temp2[] ={1.0};
    Matrix m3(CreateVector(1,1,temp2));
    m3.printMatrix();

    double temp3[] ={15.0,14.0,13.0,12.0,11.0,10.0,9.0,8.0,7.0,6.0,5.0,4.0,3.0,2.0,1.0};
    Matrix m4(CreateVector(3,5,temp3));
    m1.printMatrix();
    m4.printMatrix();
    m1 = m1 * m4;
    m1.printMatrix();
    m1.transpos().printMatrix();

// ------------------------------------------------------------------------------------ //
//
// ------------------------------------------------------------------------------------ //

        // Define input, weights, and bias
    double p_input[]={1.0,0.0,1.0};
    double p_weights[]={0.5,-0.7,0.3};
    double p_bias[]={-0.1};

    Matrix input(CreateVector(3,1,p_input));
    Matrix weights(CreateVector(1,3,p_weights));
    Matrix bias(CreateVector(1,1,p_bias));

    input.printMatrix();
    weights.printMatrix();
    bias.printMatrix();

//    Matrix input(std::vector<std::vector<double>>{{1}, {0}, {1}});
//    Matrix weights(std::vector<std::vector<double>>{{0.5, -0.7, 0.3}});
//    Matrix bias(std::vector<std::vector<double>>{{-0.1}});

    // Create perceptron object
    Perceptron p(weights, bias, input);

    p.display();

    // Test feedforward
    Matrix output = p.feedforward();
    cout << "Output before training:" << endl;
    output.printMatrix();
//    std::cout << output << std::endl;

    // Define correct output and learning rate
    double p_target[]={19};
    Matrix target(CreateVector(1,1,p_target));
//    Matrix correct_output(1,1);
//    Matrix correct_output(std::vector<std::vector<double>>{{0}});
//    double learning_rate = 0.1;

    // Train perceptron
    for(int i=0;i<10;i++)
    p.update(target, 0.1);

    // Test feedforward again
    output = p.feedforward();
    cout << "Output after training:" << endl;
    output.printMatrix();
//    std::cout << output << std::endl;

// ------------------------------------------------------------------------------------ //
//
// ------------------------------------------------------------------------------------ //

    unsigned seed = 1500;

    srand(seed);

    for(int i=0;i<30;i++)
        cout<<1+rand() % 6<<"\t";
    cout<<endl;


    return 0;
}
