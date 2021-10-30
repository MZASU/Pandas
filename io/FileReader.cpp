#include "FileReader.h"
#include <iostream>
#include <cassert>

FileReader::FileReader(std::string path, DATATYPE t)
{
    assert(path.length() > 0);

    this->type = t;
    this->file.open(path, std::ifstream::binary);

    assert(file.good() == true);
    assert(file.is_open() == true);

    // longueur du fichier
    file.seekg(0, file.end);
    uint32_t l = file.tellg();
    std::cout << "length = " << l << std::endl;
    assert(l > 0);

    if(type == DATATYPE::IMAGE)
    {
        file.seekg(16, file.beg);
        this->image.resize(28*28);
    }
    else if(type == DATATYPE::LABEL)
    {
        file.seekg(8, file.beg);
    }
    
}

FileReader::~FileReader()
{
}

void FileReader::read()
{
    if(file.eof() == true) return;

    if(type == DATATYPE::LABEL)
    {
        uint8_t c;
        file.get((char&)c);
        this->label = c;
        return;
    }
    assert(this->type == DATATYPE::IMAGE);

    uint8_t c;
    for(int i = 0; i < 28; i++)
    {
        for(int j = 0; j < 28; j++)
        {
            file.get((char&)c);
            this->image(i*28+j) = (int)c;
        }
    }
}

void FileReader::draw()
{   
    for(int i = 0; i < 28; i++)
    {
        for(int j = 0; j < 28; j++)
        {
            if(this->image(i*28+j) > 128 )
            {
                std::cout << "8";
            }else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

}

