#pragma once

#include <fstream>
#include <string>

#include "../Eigen/Dense"

/* Class that reads MNIST database */


class FileReader
{
private:
    std::ifstream images;
    std::ifstream labels;
public:
    FileReader(std::string path);
    ~FileReader();
    void draw(); // testing purpose
    void read();

    uint8_t label;
    Eigen::VectorXd image;

};
