#pragma once 

#include "Layer.h"
#include <vector>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

class NeuralNetwork
{
private:
    // remembers the size of the input instead of calling 
    // layers.first().size();
    int input_size;

    // vector containing every layers EXEPT THE INPUT LAYER
    vector<Layer> layers;
    VectorXd inputs;        // remembers it for training 
    VectorXd outputs;       // idem
    int last_output = -1;   // reidem

    // this function calculates the error for every neurons of every layers
    // it returns a vector of array contains each one of them
    // each VectorXd contains the neurons
    // and represent a layer
    // ie neurons J of layer K is, v.at(K)(J);
    vector<VectorXd> calculateError(VectorXd);

    // sigmoid function and it's derivative 
    // used in the training process
    double sigmoid(double);
    double sigmoidPrime(double);
    VectorXd sigmoidPrime(VectorXd);

public:
    
    // the learning rate define how much an error changes the neuron
    double learning_rate = 0.05f;
    // MY implementation of momentum, in other words most certainly not the one you should use
    // but basicly if consecutive success happens then rewards the network more
    // the idea is that if it manages to get many consecutive correct guesses, the network is heading the right way
    // so why not speed up the process
    double momentum = 1.0f;

    // takes the size of each layer as input
    NeuralNetwork(vector<int>);
    ~NeuralNetwork();

    // takes the image as input
    int input(VectorXd);

    // takes the correct answer as input
    void train(int);

};

