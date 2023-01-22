#include "par.hpp"
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>

Counter::Counter(int numThreads)
{
    this->numThreads = numThreads;
}

void Counter::readFromFile(std::istream& input)
{
    std::string word;
    while(input >> word) {
        container.push_back(word);
    }
}

std::string Counter::transform(std::string& word)
{
    std::string transformed;
    std::string::size_type i = 0;

    for (i; i < word.size(); ++i) {
        if (std::ispunct(word[i])) {
            continue;
        }
        else if (std::isupper(word[i])) {
            word[i] = tolower(word[i]);
        }
        transformed += word[i];
    }

    return transformed;
}

void Counter::count(void)
{
    map_t localMaps[this->numThreads];

#pragma omp parallel num_threads(this->numThreads)
{
#pragma omp for
        for (int i = 0; i < container.size(); ++i) {
            int threadId = omp_get_thread_num();
            ++localMaps[threadId][this->transform(container[i])];
        }
}
#pragma omp barrier
    for (int j = 0; j < this->numThreads; ++j) {
        for (auto el : localMaps[j]) {
            map[el.first] += el.second;
        }
    }
}

void Counter::writeToFile(std::string filename)
{
    map_t::iterator i;
    std::ofstream output(filename, std::ofstream::out | std::ofstream::trunc);

    if (output.is_open()) {
        for (i = this->map.begin();
            i != this->map.end(); ++i) {
            output << i->first << "\t" << i->second << std::endl;
        }
        output.close();
    }
    else {
        std::cout << "Unable to create output file" << std::endl;
    }
}

void Counter::clear(void)
{
    this->map.clear();
}