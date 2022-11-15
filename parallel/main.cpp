#include "par.hpp"
#include <fstream>
#include <chrono>

typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point_t;

int main(int argc, char* argv[])
{
    int i = 0;
    Counter cnt;
    
    std::ifstream input(argv[1]);
    time_point_t startTime, endTime;
    std::chrono::duration<double, std::milli> timeInterval, totalTime, avgTime;

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return -1;
    }

    if (!input) {
        std::cout << "Failed to open input file: " << argv[1] << std::endl;
        return -1;
    }

    cnt.readFromFile(input);

    for (i; i < 10; ++i) {
        cnt.clear();        

        startTime = std::chrono::high_resolution_clock::now();
        cnt.count();
        endTime = std::chrono::high_resolution_clock::now();

        timeInterval = endTime - startTime;
        totalTime += timeInterval;
    }

    avgTime = totalTime/10;

    std::cout << "Average time: " << avgTime.count() << std::endl;

    cnt.writeToFile("output.txt");
}