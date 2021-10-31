#include "MNISTReader.h"
#include <cassert>

// path:  "" means same dir, otherwise the expected input would be, "io/" if you were to put the data in the io folder
MNISTReader::MNISTReader(std::string path)
{
    this->images.open(path + "mnist.image", std::ifstream::binary);

    assert(images.good() == true);
    assert(images.is_open() == true);

    // longueur du fichier
    images.seekg(0, images.end);
    uint32_t l = images.tellg();
    assert(l > 0);

    images.seekg(16, images.beg);

    this->labels.open(path + "mnist.label", std::ifstream::binary);

    assert(labels.good() == true);
    assert(labels.is_open() == true);

    // longueur du fichier
    labels.seekg(0, labels.end);
    l = labels.tellg();
    assert(l > 0);

    labels.seekg(8, labels.beg);
}

void MNISTReader::read()
{
    if(images.eof() == true) return;

    int64_t t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::default_random_engine engine;
	engine.seed(t);
	std::uniform_int_distribution<unsigned int> distribution(0, 60000);

    unsigned int pos = distribution(engine);
    labels.seekg(8+pos, labels.beg);
    images.seekg(16+((28*28)*pos), images.beg);

    uint8_t c;
    labels.get((char&)c);
    this->label = c;
    
    c = 0;
    for(int i = 0; i < 28; i++)
    {
        for(int j = 0; j < 28; j++)
        {
            images.get((char&)c);
            this->image(i*28+j) = (double)c;
        }
    }
}

MNISTReader::~MNISTReader()
{
    images.close();
    labels.close();
}