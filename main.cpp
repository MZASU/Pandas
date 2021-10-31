#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

#include "MNISTReader.h"
#include "NeuralNetwork.h"

using namespace std;

/*      Pandas AIs @MZASU

 *  github.com/MZASU/Pandas

 *  This file is just for showcase

 */

int main()
{
    cout << "Welcome to Pandas!" << endl;

    ofstream stats;
    stats.open("stats.csv", ifstream::trunc);
    
    MNISTReader f("");

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

    vector<int> layers = {28*28, 128, 128, 128, 64, 64, 32, 32, 10};
    NeuralNetwork nn(layers);  

    int good = 0;
    int numb = 1000000;

    for(int i = 0; i < numb; i++)
    {
        f.read();
        int res = nn.input(f.image);
        if(res == f.label) good++;
        nn.train(f.label);
        if(i%1000 == 0)
        {
            stats << i << "," << good << "," << numb << endl;
            cout << i << endl;
        }
    }
    stats << numb << "," << good << "," << numb << endl;

    cout << "Fini!" << endl;
    cout << good << "/" << numb << "(" << (good/(numb*1.0f))*100.0f << ")" << endl;

    stats.close();

    std::cout << std::endl;
    return EXIT_SUCCESS;
}
