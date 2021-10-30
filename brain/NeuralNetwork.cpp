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

    VectorXd tmp = in;
    for(int i = 0; i < layers.size(); i++)
    {
        layers.at(i).forwardPass(tmp);
        tmp = layers.at(i).ACTIVATION_VALUES;
    }
    this->outputs = tmp;

    double t = 0.0;
    int ans = -1;
    for(int i = 0; i < outputs.rows(); i++)
    {
        if(outputs(i) > t)
        {
            t = outputs(i);
            ans = i;
        }
    }    

    return ans;
}

void NeuralNetwork::train(int ER)
{
    VectorXd expected = VectorXd::Zero(layers.back().size);
    expected(ER) = 1;

    vector<VectorXd> erros = calculateError(expected);

    for(int layer = 0; layer < layers.size(); layer++)
    {
            VectorXd tmp_a;
            if(layer == 0) tmp_a = inputs;
            else           tmp_a = layers.at(layer-1).ACTIVATION_VALUES;

            VectorXd tmp_z = sigmoidPrime(layers.at(layer).Z_VALUES);
            VectorXd tmp_err = erros.at(layer);
            VectorXd tmp_prim_err = tmp_z.array() * tmp_err.array();

            MatrixXd delta_w = Eigen::MatrixXd::Zero(layers.at(layer).size, layers.at(layer).previous_layer_size);
            VectorXd delta_b = tmp_prim_err;

            for(int neuron = 0; neuron < layers.at(layer).size; neuron++)
            {
                VectorXd err_w_j = tmp_a * tmp_prim_err(neuron);
                delta_w.row(neuron) = err_w_j.transpose();
            }

            layers.at(layer).WEIGHTS -= learning_rate * delta_w;
            layers.at(layer).BIASES -= learning_rate * delta_b;
    }
}

vector<VectorXd> NeuralNetwork::calculateError(VectorXd ex)
{
    // calcul ∂C / ∂A
    vector<VectorXd> backprop;
    backprop.resize(layers.size());

    int last_layer = layers.size() - 1;
    VectorXd tmp = 2*(layers.at(last_layer).ACTIVATION_VALUES - ex); // 2(Aj - Yj)
    backprop.at(last_layer) = tmp;

    for(int layer = last_layer-1; layer >= 0; layer--)
    {
        VectorXd layer_err;
        layer_err.resize(layers.at(layer).size);

        for(int neuron = 0; neuron < layers.at(layer).size; neuron++)
        {       // sum(w * sig' * ∂C / ∂(A-1)) calculer l'erreur de chaque neurons
            VectorXd tmp_col = layers.at(layer+1).WEIGHTS.col(neuron);
            VectorXd tmp_z = sigmoidPrime(layers.at(layer).Z_VALUES);
            VectorXd tmp_a = backprop.at(layer+1);
            layer_err(neuron) = (tmp_col.array() * tmp_z.array() * tmp_a.array()).sum();
        }
        backprop.at(layer) = layer_err;
    }

    return backprop;
}

double NeuralNetwork::sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double NeuralNetwork::sigmoidPrime(double x)
{
	return sigmoid(x) * (1 - sigmoid(x));
}

VectorXd NeuralNetwork::sigmoidPrime(VectorXd x)
{
	VectorXd res;
	res.resize(x.rows());

	for (size_t i = 0; i < x.rows(); i++)
	{
		res(i) = sigmoidPrime(x(i));
	}

	return res;
}

NeuralNetwork::~NeuralNetwork()
{

}
