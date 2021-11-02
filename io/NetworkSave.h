#pragma once

#include <string>
#include <fstream>
#include "../brain/FFNeuralNetwork.h"   // Not right    // Will update when i do what's written in that file

// This class contains an fstream to a file that's gonna save every parameters of a network

using std::ofstream;
using std::ifstream;

class NetworkSave
{
private:
    // I'm using 2 of these instead of fstream because i'm not sure how thoses wroks
    // And because i find it more readable
    ofstream output_save;
    ifstream input_save;
    
    // placeholder path, it is replaced in the constructor
    std::string file = "neuralnetwork.save";

public:
    // path to the file
    NetworkSave(std::string path);
    ~NetworkSave();

    // saves a given network at the path given in constructor
    void save(FFNeuralNetwork);

    // loads a network from the path given in constructor
    void load(FFNeuralNetwork&);

};

