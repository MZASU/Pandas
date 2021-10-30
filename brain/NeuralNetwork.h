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

    vector<Layer> layers;
    VectorXd inputs;
    VectorXd outputs;

    double sigmoid(double);
    double sigmoidPrime(double);
    VectorXd sigmoidPrime(VectorXd);

public:
    
    NeuralNetwork(vector<int>);
    ~NeuralNetwork();

    int input(VectorXd);

    void train(int);

};

