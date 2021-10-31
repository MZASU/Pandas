#pragma once

#include "../Eigen/Dense"
#include <vector>
#include <random>
#include <chrono>

using Eigen::MatrixXd;
using Eigen::VectorXd;

class NeuralNetwork;

class Layer
{
    // we say that the NeuralNetwork classe can access our private data
    friend class NeuralNetwork;
private:
    // stores it for clarity of code 
    int previous_layer_size;
    int size;

    // self explanetory
    MatrixXd WEIGHTS;
    VectorXd BIASES;
    VectorXd Z_VALUES;
    VectorXd ACTIVATION_VALUES;

    double sigmoid(double);

public:
    Layer(int size, int psize);
    ~Layer();

    // gets as input the array of the previous layer's activation function 
    void forwardPass(VectorXd values);

    //operators to save network TODO
};