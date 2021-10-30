#include <iostream>
#include <cstdlib>
#include <vector>

#include "FileReader.h"
#include "NeuralNetwork.h"

using namespace std;

/*      Pandas AIs @MZASU

 *  github.com/MZASU/Pandas

 *  This file is just for showcase

 */

int main()
{
    cout << "Welcome to Pandas!" << endl;

    FileReader f("");

    vector<int> layers = {28*28, 128, 128, 128, 64, 64, 32, 32, 10};
    NeuralNetwork nn(layers);  

    int good = 0;
    int numb = 10000;

    for(int i = 0; i < numb; i++)
    {
        f.read();
        int res = nn.input(f.image);
        if(res == f.label) good++;
        nn.train(f.label);
    }

    cout << "Fini!" << endl;
    cout << good << "/" << numb << "(" << (good/(numb*1.0f))*100.0f << ")" << endl;


    std::cout << std::endl;
    return EXIT_SUCCESS;
}
