#include "FFNeuralNetwork.h"

FFNeuralNetwork::FFNeuralNetwork(std::vector<int> sizes)
{
    // remembers the input size
    this->input_size = sizes.at(0);

    for(size_t i = 1; i < sizes.size(); i++)
    {
        // creates all the layers and give them their size and the previous layer's size
        layers.push_back(Layer(sizes.at(i), sizes.at(i-1)));
    }
}

int FFNeuralNetwork::input(VectorXd in)
{
    // remember the input
    this->inputs = in;

    // tmp act as a container for the activation value of every layer
    // and is then passed to the next layer
    VectorXd tmp = in;
    for(size_t i = 0; i < layers.size(); i++)
    {
        layers.at(i).forwardPass(tmp);
        tmp = layers.at(i).ACTIVATION_VALUES;
    }
    // at last we get the output of the whole network
    this->outputs = tmp;

    // simple algorithym to know wich fo the answer
    // as the highest value
    // The answer of the network
    double t = 0.0;
    int ans = -1;
    for(long int i = 0; i < outputs.rows(); i++)
    {
        if(outputs(i) > t)
        {
            t = outputs(i);
            ans = i;
        }
    }    

    // returns it to whoever inputs the image
    return ans;
}

void FFNeuralNetwork::train(int ER)
{
    // ER is the correct answer 
    // we wanted the network to returns us that value
    // so we create an array that's filled with zeros, exept the correct one
    VectorXd expected = VectorXd::Zero(layers.back().size);
    expected(ER) = 1;

    // if the network got a correct answer give it a kudos
    if(last_output == ER)
    {
        momentum *= 1.10f;
    }else{
        momentum = 1.0f;
    }


    // get the error of each neuron from each layer according to the expected outcome
    vector<VectorXd> erros = calculateError(expected);

    // apply the changes according to the errors
    for(size_t layer = 0; layer < layers.size(); layer++)
    {
            // tmp_a always contains the activation values of each layers
            // but the vector 'layers' doesn't contain the input layer
            // so we make sure it uses it
            VectorXd tmp_a;
            if(layer == 0) tmp_a = inputs;
            else           tmp_a = layers.at(layer-1).ACTIVATION_VALUES;

            // tmp_z contains the z values of each neuron of the current layer
            VectorXd tmp_z = sigmoidPrime(layers.at(layer).Z_VALUES);
            // tmp_err contains the errors for each neuron, given by the calculateError function
            VectorXd tmp_err = erros.at(layer);
            // gives us the 'vector' of error of each neuron according to it's strength
            // for exemple, a neuron that as a high strengh and gets good result is more rewarded that way
            // (it's been a long time i didn't read about nn so this might wrong in some ways)                          (i forgor :skull:)
            // (anyway i supose if you're reading that you already have some knowledge)
            VectorXd tmp_prim_err = tmp_z.array() * tmp_err.array();


            // we change the biases exactly according to each erros (because biases are added "flat" whereas weight are "multiplicative" so we change them)
            MatrixXd delta_w = Eigen::MatrixXd::Zero(layers.at(layer).size, layers.at(layer).previous_layer_size);
            VectorXd delta_b = tmp_prim_err;

            for(int neuron = 0; neuron < layers.at(layer).size; neuron++)
            {
                // the error of each weights of a given neurons 
                // is the previously calculated 'vector' times the it's activation
                VectorXd err_w_j = tmp_a * tmp_prim_err(neuron);
                // we transpose because in the weight matrix, the weights of the given neuron are in the same row
                // VectorXd on the other hand stores in collumn. Yes i could have used a rowVectorXd but i will have to transpose 
                // at one point anyways and i choose it to be there. feel free to change it 
                delta_w.row(neuron) = err_w_j.transpose();
            }

            // change the weights and biases given how delta(how much the value has to change), 
            // times learning rate(how much do we care (usually not much)) and the momentum(is this a winstreak)
            layers.at(layer).WEIGHTS -= learning_rate * delta_w * momentum;
            layers.at(layer).BIASES -= learning_rate * delta_b * momentum;
    }
}

vector<VectorXd> FFNeuralNetwork::calculateError(VectorXd ex)
{
    // Warning their is a lot of math going on there and i'm sleepy
    // So 1 i assume the math is correct since the test showed that it did improve
    // and 2 rely on my comments with causion since i might be misexplaining thing

    //  -- calculs ∂C / ∂A

    // stores the values for each neurons of eahc layers
    vector<VectorXd> backprop;
    backprop.resize(layers.size());

    // This calculs the error of the last layer by the function commented below
    int last_layer = layers.size() - 1;
    VectorXd tmp = 2*(layers.at(last_layer).ACTIVATION_VALUES - ex); // 2(Aj - Yj)
    backprop.at(last_layer) = tmp;

    // Now that we have the error of the last layer we can backpropagate
    for(int layer = last_layer-1; layer >= 0; layer--)
    {
        // will store the error of each neuron of the current layer
        VectorXd layer_err;
        layer_err.resize(layers.at(layer).size);

        // calculate the error for each neuron of current layer
        for(int neuron = 0; neuron < layers.at(layer).size; neuron++)
        {       
            // gets the weights of a neuron connecting it to the next layer
            VectorXd tmp_col = layers.at(layer+1).WEIGHTS.col(neuron);  
            // z' values of the next layer             
            VectorXd tmp_z = sigmoidPrime(layers.at(layer+1).Z_VALUES);
            // get the error of the previous layer
            VectorXd tmp_a = backprop.at(layer+1);
            // the error of that neuron follows that equation (it's written A-1 because since we go backwards the 'next' layer becomes the 'previous'(don't think to much of it))
            // sum(w * sig' * ∂C / ∂(A-1)) calculer l'erreur de chaque neurons
            layer_err(neuron) = (tmp_col.array() * tmp_z.array() * tmp_a.array()).sum();
        }
        // store it on our array and go to the nrextvious one
        backprop.at(layer) = layer_err;
    }
    // returns to the unknown calling entity the value of the previously calculated backpropation 
    return backprop;
}

// the next three are just single lines
double FFNeuralNetwork::sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double FFNeuralNetwork::sigmoidPrime(double x)
{
	return sigmoid(x) * (1 - sigmoid(x));
}

VectorXd FFNeuralNetwork::sigmoidPrime(VectorXd x)
{
    // exept this one where we go it to each neuron
	VectorXd res;
	res.resize(x.rows());

	for (long int i = 0; i < x.rows(); i++)
	{
		res(i) = sigmoidPrime(x(i));
	}

	return res;
}

FFNeuralNetwork::~FFNeuralNetwork()
{

}
