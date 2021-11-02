#include "NetworkSave.h"

//  * ---- NEURALNETWORK.SAVE STRUCTURE
/*  *   Everything is written in binary not text form, this starts at offset 0x00, everythign that will be written is wrtten here
    *   
    *   DOUBLE: learning rate
    *   INT : input size
    *   INT : number of layers (NL)
    *   -- LAYERS (NL times)          // under this is how a single layer is written, it's gonna be repeated NL times
    *       *   INT : size of current layer object LS            // !NOT NUMBER OF NEURONS!
    *       *   LAYER of size LS :
    *       *       *   INT : number of neurons NbN                                                                          // 1 2 3
    *       *       *   INT : number of neurons from previous layer NbNP                                                     // 4 5 6
    *       *       *   MATRIXD(NbN, NbNP) : Weights matrice it is saved in the order col then row. It would look like this  // 7 8 9
    *       *       *   VECTORD(NbN) : Biases
    *      
*/



NetworkSave::NetworkSave(std::string path)
{
    // saves the path given by the user
    // if he gave one
    if(path.length() != 0) this->file = path;
}

void NetworkSave::load(FFNeuralNetwork& nn)
{
    // Opens the file
    input_save.open(file, std::ifstream::binary);

    // loads the network
    input_save >> nn;
    input_save.sync();

    //closes
    input_save.close();
}

void NetworkSave::save(FFNeuralNetwork nn)
{
    // Opens the file
    output_save.open(file, std::ofstream::binary);

    // saves the network
    output_save << nn;
    output_save.flush();

    output_save.close();
}

NetworkSave::~NetworkSave()
{

}