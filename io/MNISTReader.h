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
    std::ifstream images;
    std::ifstream labels;
public:
    MNISTReader(std::string path);
    ~MNISTReader();
    void read();

    uint8_t label;
    Eigen::Matrix<double, 784, 1> image;

};
