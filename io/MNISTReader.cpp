#include "MNISTReader.h"
#include <cassert>

// path:  "" means same dir, otherwise the expected input would be, "io/" if you were to put the data in the io folder
MNISTReader::MNISTReader(std::string path)
{
    // open the image file of the dataset
    this->images.open(path + "mnist.image", std::ifstream::binary);

    // basic checks 
    assert(images.good() == true);
    assert(images.is_open() == true);

    // length of the file (basic check)
    images.seekg(0, images.end);
    uint32_t l = images.tellg();
    assert(l > 0);

    // the structure of the file from MNIST contains metadata 
    // in the first 16 bytes (like heights, and width)
    // however that object is onyl used for mnist so i harcoded it
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
    // gets the time in millis, use it to seed the random engine and get a random position in the dataset
    // each time that we read - may be overkill for a simple program like that, or may be too much line 
    int64_t t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::default_random_engine engine;
	engine.seed(t);
	std::uniform_int_distribution<unsigned int> distribution(0, 60000);

    // get the said number and calculate the pos in the file (offset of metadata and images)
    unsigned int pos = distribution(engine);
    labels.seekg(8+pos, labels.beg);
    images.seekg(16+((28*28)*pos), images.beg);

    // get the answer and store it
    uint8_t c;
    labels.get((char&)c);
    this->label = c;
    
    // get each pixel and store them in an array
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