// Anisha Braganza
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <ctype.h>

#include <iostream>

class BookBot {
private:
    std::map<std::string, std::vector<std::string>> markov_chain;
    unsigned int m_seed;

public:
    BookBot(const unsigned int seed);

    void readIn(const std::string & filename);
    bool isEndPunctuation(const char character);
    std::vector<std::string> getValues(const std::string & key);
    std::string generateSentence();
};