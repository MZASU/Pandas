#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(std::vector<int> sizes)
{
    this->input_size = sizes.at(0);

    for(int i = 1; i < sizes.size(); i++)
    {
        layers.push_back(Layer(sizes.at(i), sizes.at(i-1)));
    }
}

int NeuralNetwork::input(VectorXd in)
{
    this->inputs = in;
}

NeuralNetwork::~NeuralNetwork()
{

}
