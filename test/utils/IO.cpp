#include "IO.h"
#include <fstream>
#include <sstream>
#include <string>

InputCVRP IO::fileToInputCVRP(std::string file_path) {
    InputCVRP *inputCVRP = new InputCVRP();

    std::ifstream infile(file_path);

    std::string line;
    int i = 0;
    std::vector<Dot> dots;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int a;
        if (i == 0) {
            if (!(iss >> a)) { break; } // error
            inputCVRP->setVertex(a);
        } else if (i == 1) {
            if (!(iss >> a)) { break; } // error
            inputCVRP->setCapacity(a);
        } else {
            int x, y, objetivo;
            if (!(iss >> x >> y >> objetivo)) { break; } // error
                dots.push_back(Dot(x,y,objetivo));
        }
        i++;
    }

    inputCVRP->setVertexCordenates(dots);

    return *inputCVRP;
}

