#include "Layer.h"

Layer::Layer(int s, int ps)
{
	// store
    this->size = s;
    this->previous_layer_size = ps;

	// gets the time in millis, use it to seed the random engine
	// later feed it to each weight and biases
	int64_t t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::default_random_engine engine;
	engine.seed(t);
	std::uniform_real_distribution<double> distribution(-1,1);

	// initialize each matrices and vectors
	// in reality there is no 'push_back' in eigen so if you forget those lines
	// the whole thing burns
	WEIGHTS = MatrixXd::Zero(size, previous_layer_size);
	ACTIVATION_VALUES = VectorXd::Zero(size, 1);
	Z_VALUES = VectorXd::Zero(size, 1);
	BIASES = VectorXd::Zero(size, 1);

	// feeds it to each weight and biases
	// (told ya)
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < previous_layer_size; j++)
		{
			WEIGHTS(i,j) = distribution(engine);
		}
		BIASES(i,0) = distribution(engine);
	}

}

void Layer::forwardPass(VectorXd in)
{
	// The functions you have see when you watched the 3blue1brown videos

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