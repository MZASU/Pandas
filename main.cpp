#include <iostream>
#include <cstdlib>

#include "./io/FileReader.h"

using namespace std;

/*      Pandas AIs @MZASU

 *  github.com/MZASU/Pandas

 *  This file is just for showcase

 */

int main()
{
    cout << "Welcome to Pandas!" << endl;

    FileReader f("mnist.image", DATATYPE::IMAGE);

    f.draw();

    std::cout << std::endl;
    return EXIT_SUCCESS;
}