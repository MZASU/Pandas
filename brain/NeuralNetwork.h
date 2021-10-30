#pragma once 

#include "FileReader.h"
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

    vector<VectorXd> calculateError(VectorXd);

    double sigmoid(double);
    double sigmoidPrime(double);
    VectorXd sigmoidPrime(VectorXd);

public:
    
    double learning_rate = 0.01f;

    NeuralNetwork(vector<int>);
    ~NeuralNetwork();

    int input(VectorXd);

    void train(int);

};

