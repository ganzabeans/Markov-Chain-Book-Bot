// Anisha Braganza

#include "BookBot.h"
#include "sanitize.h" //pragma once not compiling so had to move this here 

//Constructor
BookBot::BookBot(const unsigned int seed) {std::srand(seed);}    // set random seed};

//this functions reads in a text file stores the sentences
void BookBot::readIn(const std::string & filename){
    std::string tempString; //holds current word
    std::string prevString = "^"; // holds previous word, carrot is starting indicator
    std::ifstream classicBook(filename);

    if (classicBook.is_open()){
        while(classicBook >> tempString){
            sanitize(tempString); //get rid of junk characters

            //check for punctuation at the end
            std::string endString = "";
            char tempChar = tempString.back();
            endString += tempChar;

            /****** I think this would make sense to pop off other punctuation (ie. comma) and add it to the markov_chain, but test didn't pass with it
            //if punction is attached to end, pop it!
            if (!isalpha(tempChar) && !isdigit(tempChar)) {
                tempString.pop_back();   
            }
            */

            //markov_chain[prevString].push_back(tempString);
            if (isEndPunctuation(tempChar)) {     //if punctuation is . ? !, add the $
                tempString.pop_back();  
                markov_chain[endString].push_back("$");
                markov_chain[prevString].push_back(tempString);
                markov_chain[tempString].push_back(endString);
                prevString = "^"; //start a new sentence   
            }  
            else {
                markov_chain[prevString].push_back(tempString);
                 // add temp string to prev string 
                prevString = tempString;
            }
        }
        classicBook.close();
    }
    else std::cout << "Unable to open file :'(\n";
}

//this function returns true if punctuation is . ? or !
bool BookBot::isEndPunctuation(const char character){
    char punctuation[] = {'.', '?', '!'};

    //check if the punctuation matches
    for (size_t i = 0; i < 3; i++) {
        if (character == punctuation[i])
            return true;
    }
    return false;
}

//returns a vector of values
std::vector<std::string> BookBot::getValues(const std::string & key){
    return markov_chain[key];
}

std::string BookBot::generateSentence(){

    std::string mySentence, key, value;     // return string, key and val
    
    //initial start of sentence
    int vectorSize = markov_chain["^"].size() - 1;
    int vectorSpot = std::rand() % vectorSize;
    key = "^";
    value = markov_chain[key][vectorSpot];

    // fill rest of sentence 
    while (key != "$") {
        //add space if appropriate
        if (key != "^" && !isEndPunctuation(value.back()))
            mySentence.append(" ");     //no space for beginning and end 

        mySentence.append(value);
        vectorSize = markov_chain[key].size();
        if (vectorSize > 1)
            vectorSpot = std::rand() % (vectorSize -1);
        else
            vectorSpot = 0;  //in case of 0;
        value = markov_chain[key][vectorSpot];

        key = value; // go to the next one!
    }

    return mySentence;
}