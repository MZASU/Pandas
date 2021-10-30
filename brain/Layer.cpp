#include "Layer.h"

Layer::Layer(int s, int ps)
{
    this->size = s;
    this->previous_layer_size = ps;

	WEIGHTS = MatrixXd::Random(size, previous_layer_size);
	ACTIVATION_VALUES = VectorXd::Random(size, 1);
	Z_VALUES = VectorXd::Random(size, 1);
	BIASES = VectorXd::Random(size, 1);

}

void Layer::forwardPass(VectorXd in)
{
	Z_VALUES = (WEIGHTS * in) + BIASES; 

	for (int i = 0; i < size; i++)
	{
		ACTIVATION_VALUES(i, 0) = sigmoid(Z_VALUES(i, 0));
	}
}

double Layer::sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

Layer::~Layer()
{
}