#pragma once 

#include "Layer.h"
#include <vector>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

class NeuralNetwork
{
private:
    int input_size;

    vector<Layer> layers;
    VectorXd inputs;
    VectorXd outputs;
    int last_output = -1;

    vector<VectorXd> calculateError(VectorXd);

    double sigmoid(double);
    double sigmoidPrime(double);
    VectorXd sigmoidPrime(VectorXd);

public:
    
    double learning_rate = 0.05f;
    double momentum = 1.0f;

    NeuralNetwork(vector<int>);
    ~NeuralNetwork();

    int input(VectorXd);

    void train(int);

};

