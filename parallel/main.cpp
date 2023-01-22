#include "par.hpp"
#include <fstream>


int main(int argc, char* argv[])
{
    int i = 0;
    
    std::ifstream input(argv[1]);

    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return -1;
    }

    if (!input) {
        std::cout << "Failed to open input file: " << argv[1] << std::endl;
        return -1;
    }

    Counter cnt(std::atoi(argv[2]));

    cnt.readFromFile(input);

    cnt.count();

    cnt.writeToFile("output.txt");
}