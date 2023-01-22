#ifndef _PAR_
#define _PAR_

#include <iostream>
#include <map>
#include <vector>
#include <omp.h>

typedef std::map<std::string, int> map_t;

/* Class for counting the occurences
 * of all words in a text file */
class Counter
{
public:
    /* omp num threads */
    Counter(int numThreads);
    /* Reads contents of input file into
     * internal container */
    void readFromFile(std::istream& input);
    /* Counts occurences of all words
     * read from input file */
    void count(void);
    /* Writes contents of internal map
     * to a text file */
    void writeToFile(std::string filename);
    /* Clears internal map */
    void clear(void);
private:
    int numThreads;
    /* Stores occurences of words
     * from input file */
    map_t map;
    /* Stores contents of input file */
    std::vector<std::string> container;
    /* Transforms a given string to lowercase
     * and removes punctuation marks */
    std::string transform(std::string& word);
};

#endif