#include <iostream>
#include <vector>
#include <pthread.h>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

// Struct to store frequency and binaryCode for a said character
struct CharCode
{
    char character;
    int freq;
    std::string code;
};

// Used for sorting function, Compares frequency first then if equal, compares character 
bool compareFreqChar(CharCode a, CharCode b) 
{
    // first compares frequencies
    if (a.freq != b.freq)
        return a.freq > b.freq;
    
    // if frequencies are even, then compares characters
    return a.character > b.character;
}

// converts the probability to its binary equivalent to a certain precision
std::string decimalToBinary(float decimal, int precision) 
{
    // holds the finished binary code
    std::string binary = "";

    // converts the decimal until it is 0 OR precision reaches 0
    while (decimal > 0 && precision > 0) 
    {
        double temp = decimal * 2;

        // adds a 1 if a 1 is in the one's place
        if (temp >= 1) 
        {
            binary += "1";
            decimal = temp - 1;
        }

        // adds a 0 if a 0 is in the one's place
        else 
        {
            binary += "0";
            decimal = temp;
        }
        --precision;
    }

    // Adds any missing 0's due to previous loop terminating from the decimal reaching 0 first
    while (precision > 0) 
    {
        --precision;
        binary += "0";
    }

    return binary;
}


void *shannonCode(void *void_ptr) 
{
    // change the void_ptr into a string line_ptr
    std::string line = *(std::string*) void_ptr;
    
    // create a mapping to store each unique character and count their appearances 
    std::map<char, int> charCountMap;

    // iterate through each character for the given line
    // NOTE: COULD skip the mapping part and do this in the charCode struct 
    int len = (line).length();
    for (int i = 0; i < len; i++) 
    {
        // Stores unqiue characters and their associated frequencies from the line
        ++charCountMap[line[i]];
    }

    // vector to sort the frequencies 
    std::vector<CharCode> charCodeVec;
    CharCode temp;
    for (const auto& charCount: charCountMap)
    {
        temp.character = charCount.first;
        temp.freq = charCount.second;
        // each entry in the charCodeVec holds its character and associated frequency so far
        charCodeVec.push_back(temp);
    }

    // sorts the charCodeVec based on frequencies, and if equal then characters
    std::sort(charCodeVec.begin(), charCodeVec.end(), compareFreqChar);

    // Keeps track of the Cumulative Probability as we iterate through the charCode vector
    float cumulativeProbability = 0;

    // create a new mapping to hold the characters and their associated binary codes
    std::map<char, std::string> charCodeMap;

    
    for (auto& charCode : charCodeVec) 
    {
        // probability = frequency / total freq (total freq is just the length of the line)
        float probability = ((float)charCode.freq/len);

        // precision = ceiling of log base 2 (1/probability)
        int precision = ceil(log2(1/probability));

        // maps the character to its associated code
        std::string ShannonCode = decimalToBinary(cumulativeProbability, precision);
        charCode.code = ShannonCode;
        charCodeMap[charCode.character] = ShannonCode;

        // adds current probability to the total
        cumulativeProbability += probability;
    }

    std::cout << "Message: " << line << std::endl;
    std::cout << std::endl;

    std::cout << "Alphabet:" << std::endl;

    // prints out the each symbol in the line and their associated frequency and shannon code 
    for (const auto& charCode : charCodeVec) 
    {
        std::cout << "Symbol: "<< charCode.character
        << ", Frequency: " << charCode.freq 
        << ", Shannon code: " << charCode.code << std::endl;
    }
    
    std::cout << std::endl;

    // holds the finished encoded line
    std::string encodeMsg = "";

    // iterates over the intial line
    for (int i = 0; i < len; ++i) {
        // Adds each encountered characters associated shannon code to the finished encoded line 
        encodeMsg += charCodeMap[line[i]];
    }

    std::cout << "Encoded message: " << encodeMsg << std::endl;


    return nullptr;
}


int main() 
{
    // store each line into a different vector of struct EncodedMsg
    std::string temp;
    std::vector<std::string> inputVec;
    while(std::getline(std::cin, temp)) {
        inputVec.push_back(temp);
    }

    int encodedMsgSize = inputVec.size();

    // store the thread id in tid
    pthread_t *tid = new pthread_t[encodedMsgSize];

    // iterate through the vector
    for (int i = 0; i < encodedMsgSize; i++)
    {
        // create a thread for each EncodedMsg struct of the vector, and if an error is thrown return 1;
        if(pthread_create(&tid[i], nullptr, shannonCode, (void *) &inputVec[i]))
        {
            std::cerr << "Error creating thread" << std::endl;
			return 1;
        }
        std::cout << std::endl;
    }

    // join threads back together when they are finished
    for (int i = 0; i < encodedMsgSize; i++)
    {
        pthread_join(tid[i], nullptr);
    }
    

    return 0;
}