#pragma once

#include "../Eigen/Dense"
#include <vector>
#include <random>
#include <chrono>
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;

class FFNeuralNetwork;

class Layer
{
    // we say that the NeuralNetwork classe can access our private data
    friend class FFNeuralNetwork;
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
    Layer();
    ~Layer();

    // gets as input the array of the previous layer's activation function 
    void forwardPass(VectorXd values);

    friend std::ostream& operator<<(std::ostream& os, const Layer& l);
    friend std::istream& operator>>(std::istream& is, Layer& l);
};