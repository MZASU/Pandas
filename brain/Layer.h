#pragma once

#include "../Eigen/Dense"
#include <vector>

typedef Eigen::MatrixXd MatrixXd;
typedef Eigen::VectorXd VectorXd;

class Layer
{
private:
    int previous_layer_size;
    int size;

    MatrixXd WEIGHTS;
    VectorXd BIASES;
    VectorXd Z_VALUES;
    VectorXd ACTIVATION_VALUES;

    double sigmoid(double);

public:
    Layer(int size, int psize);
    ~Layer();

    void forwardPass(VectorXd values);

    //operators TODO
};