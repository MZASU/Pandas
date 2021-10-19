#pragma once

#include <fstream>
#include <string>

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
};
