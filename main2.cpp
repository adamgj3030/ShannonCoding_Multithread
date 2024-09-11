#include <iostream>
#include <vector>
#include <pthread.h>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

// Struct to store line, character, frequency and finished binary code
struct CharFreq {
    std::string line;
    // Vector to store characters and their frequencies of said line
    std::vector<std::pair<char,int>> charFreqVec;
    std::string code;
};

// Used for sorting function, Compares Frequency first then if equal, compares character 
bool compare(CharFreq a, CharFreq b) {
    
    //if (a.freq != b.freq) {
        // if a.freq > b.freq, return true
    //    return a.freq > b.freq;
    //}

    //// if a.freq = b.freq, return the character with the higher value
    //return a.character > b.character;
}


void *shannonCode(void *void_ptr) 
{
    // change the void_ptr into a CharFreq struct ptr
    CharFreq *charFreq_ptr = (CharFreq*) void_ptr;
    
    // create a mapping to store each unique character and count their appearances 
    std::map<char, int> charCountMap;

    // iterate through each character for the given line
    // NOTE: COULD skip the mapping part and do this in the struct 
    int len = (charFreq_ptr->line).length();
    for (int i = 0; i < len; i++) 
    {
        // Stores unqiue characters and their associated frequencies 
        ++charCountMap[charFreq_ptr->line[i]];
    }

    // Once the mapping is done, the frequency part of the CharFreq strut is updated 
    for (const auto& charCount: charCountMap)
    {
        
    }

    return nullptr;
}


int main() 
{
    // store each line into a different vector of struct CharFreq
    CharFreq temp;
    std::vector<CharFreq> charFreq;
    while(std::getline(std::cin, temp.line)) {
        charFreq.push_back(temp);
    }

    int charFreqSize = charFreq.size();

    // store the thread id in tid
    pthread_t *tid = new pthread_t[charFreqSize];

    // iterate through the vector
    for (int i = 0; i < charFreqSize; i++)
    {
        // create a thread for each CharFreq struct of the vector, and if an error is thrown return 1;
        if(pthread_create(&tid[i], nullptr, shannonCode, (void *) &charFreq[i]))
        {
            std::cerr << "Error creating thread" << std::endl;
			return 1;
        }
    }

    // join threads back together when they are finished
    for (int i = 0; i < charFreqSize; i++)
    {
        pthread_join(tid[i], nullptr);
    }
    

    return 0;
}