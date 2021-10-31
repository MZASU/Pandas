#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

#include "MNISTReader.h"
#include "FFNeuralNetwork.h"

using namespace std;

/*      Pandas AIs @MZASU

 *  github.com/MZASU/Pandas

 *  This file is just for showcase

 */

int main()
{
    cout << "Welcome to Pandas!" << endl;

    // to save the progress of the network
    ofstream stats;
    stats.open("stats.csv", ifstream::trunc);
    
    // the files are in the same dir
    MNISTReader f("");

    // drawing the image for debug purpose
    // f.read();
    // for(int i = 0; i < 28; i++)
    // {
    //     for(int j = 0; j < 28; j++)
    //     {
    //         if(f.image(i*28+j)>128)    cout << "8";
    //         else                    cout << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl << "label: " << (int)f.label << endl;

    // while(1){};

    // defining the layers of the network
    // Here the input layer will have 28*28 (784) inputs
    // then the first hidden layer will have 128, the second 128, etc
    // and finally the output layer will have 10 outputs
    vector<int> layers = {28*28, 128, 128, 128, 64, 64, 32, 32, 10};
    // initialisaton of the network using our defined layers
    FFNeuralNetwork nn(layers);  

    // counters for good guess and total trainings
    int good = 0;
    int numb = 1000000;

    for(int i = 0; i < numb; i++)
    {
        // read the image & label from the dataset
        f.read();
        // pass the image to the network
        int res = nn.input(f.image);
        // check if the guess is correct
        if(res == f.label) good++;
        // train the network according to the correct answer
        nn.train(f.label);
        // save stats and display current state of training
        if(i%1000 == 0)
        {
            stats << i << "," << good << "," << numb << endl;
            cout << i << endl;
        }
    }
    stats << numb << "," << good << "," << numb << endl;

    // display end and final stats 
    cout << "Fini!" << endl;
    cout << good << "/" << numb << "(" << (good/(numb*1.0f))*100.0f << ")" << endl;

    // close the file 
    stats.close();

    std::cout << std::endl;
    return EXIT_SUCCESS;
}
