#pragma once

#include <fstream>
#include <string>
#include <random>
#include <chrono>

#include "../Eigen/Dense"

/* Class that reads MNIST database */


class MNISTReader
{
private:
    // objects that point to the two dataset files
    std::ifstream images;
    std::ifstream labels;
public:
    // we only need the path for the constructor
    MNISTReader(std::string path);
    ~MNISTReader();
    // reads the next entry from both files 
    void read();

    // both public to be retrieve in the main fonction and then passed to the network
    uint8_t label;
    Eigen::Matrix<double, 784, 1> image;

};
