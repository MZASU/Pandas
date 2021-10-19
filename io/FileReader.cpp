#include "FileReader.h"
#include <iostream>
#include <cassert>

FileReader::FileReader(std::string path, DATATYPE t)
{
    assert(path.length() > 0);

    this->type = t;
    this->file.open(path);

    assert(file.is_open() == true);

    // longueur du fichier
    file.seekg(0, file.beg);
    uint32_t l = file.tellg();
    std::cout << "length = " << l << std::endl;
    assert(l > 0);

    if(type == DATATYPE::IMAGE)
    {
        file.seekg(16, file.beg);
    }
    else if(type == DATATYPE::LABEL)
    {
        file.seekg(8, file.beg);
    }
    
}

FileReader::~FileReader()
{
}

void FileReader::draw()
{
    assert(file.eof() == false);
    assert(this->type == DATATYPE::IMAGE);

    uint8_t c;
    for(int i = 0; i < 28; i++)
    {
        for(int j = 0; j < 28; j++)
        {
            file.get((char&)c);
            //if(c > 128) std::cout << "0";
            if(i==0) std::cout << (int)c << ",";
        }
        std::cout << ";";
    }

}

