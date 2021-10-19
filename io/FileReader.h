#pragma once

#include <fstream>
#include <string>
#include <iostream>

/* Class that reads MNIST database */

enum class DATATYPE {IMAGE, LABEL};

class FileReader
{
private:
    DATATYPE t;
    std::ifstream file;

    void draw(); // testing purpose

public:
    FileReader(std::string path, DATATYPE type);
    ~FileReader();
};
