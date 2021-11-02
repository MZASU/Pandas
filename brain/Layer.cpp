#include "Layer.h"

Layer::Layer()
{
	// This constructor should only be called in NeuralNetwork's operator>> call
	// to be able to load a layer from a file
}

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
	// The functions you have seen when you watched the 3blue1brown videos

	Z_VALUES = (WEIGHTS * in) + BIASES; 

	for (int i = 0; i < size; i++)
	{
		ACTIVATION_VALUES(i, 0) = sigmoid(Z_VALUES(i, 0));
	}
}

std::ostream& operator<<(std::ostream& os, const Layer& l)
{
	os.write((char*)&l.size, sizeof(int));
	os.write((char*)&l.previous_layer_size, sizeof(int));
	for(int i = 0; i < l.size; i++)
	{
		for(int j = 0; j < l.previous_layer_size; j++)
		{
			os.write((char*)&l.WEIGHTS(i,j), sizeof(double));
		}
	}
	for(int i = 0; i < l.size; i++)
	{
		os.write((char*)&l.BIASES(i), sizeof(double));
	}
	return os;
}


std::istream& operator>>(std::istream& is, Layer& l)
{
	is.read((char*)&l.size, sizeof(int));
	is.read((char*)&l.previous_layer_size, sizeof(int));
	l.WEIGHTS.resize(l.size, l.previous_layer_size);
	l.BIASES.resize(l.size, 1);
	l.Z_VALUES = VectorXd::Zero(l.size, 1);
	l.ACTIVATION_VALUES = VectorXd::Zero(l.size, 1);

	for(int i = 0; i < l.size; i++)
	{
		for(int j = 0; j < l.previous_layer_size; j++)
		{
			is.read((char*)&l.WEIGHTS(i,j), sizeof(double));
		}
	}
	for(int i = 0; i < l.size; i++)
	{
		is.read((char*)&l.BIASES(i), sizeof(double));
	}
	return is;
}

double Layer::sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

Layer::~Layer()
{
}