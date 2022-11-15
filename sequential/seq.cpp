#include "seq.hpp"
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>

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
    std::string::size_type i = 0;

    for (i = 0; i < container.size(); ++i) {
        ++this->map[this->transform(container[i])];
    }
}

void Counter::writeToFile(std::string filename)
{
    map_t::iterator i;
    std::ofstream output(filename);

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