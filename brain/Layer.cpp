#include "Layer.h"

Layer::Layer(int s, int ps)
{
    this->size = s;
    this->previous_layer_size = ps;

	int64_t t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::default_random_engine engine;
	engine.seed(t);
	std::uniform_real_distribution<double> distribution(-1,1);

	WEIGHTS = MatrixXd::Zero(size, previous_layer_size);

	ACTIVATION_VALUES = VectorXd::Zero(size, 1);
	Z_VALUES = VectorXd::Zero(size, 1);
	BIASES = VectorXd::Zero(size, 1);

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < previous_layer_size; j++)
		{
			WEIGHTS(i,j) = distribution(engine);
		}
		ACTIVATION_VALUES(i,0) = distribution(engine);
		Z_VALUES(i,0) = distribution(engine);
		BIASES(i,0) = distribution(engine);
	}

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