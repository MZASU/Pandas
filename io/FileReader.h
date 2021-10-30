#pragma once

#include <fstream>
#include <string>

#include "../Eigen/Dense"

/* Class that reads MNIST database */

enum class DATATYPE {IMAGE, LABEL};

class FileReader
{
private:
    DATATYPE type;
    std::ifstream file;
public:
    FileReader(std::string path, DATATYPE t);
    ~FileReader();
    void draw(); // testing purpose
    void read();

    uint8_t label;
    Eigen::VectorXi image;

};
