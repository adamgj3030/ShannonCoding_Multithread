#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

// Struct to store character, frequency and finished binary code
struct CharFreq {
    char character;
    int freq;
    string code;
};

// Used for sorting function, Compares Frequency first then if equal, compares character 
bool compare(CharFreq a, CharFreq b) {
    
    if (a.freq != b.freq) {
        // if a.freq > b.freq, return true
        return a.freq > b.freq;
    }

    // if a.freq = b.freq, return the character with the higher value
    return a.character > b.character;
}

void shannonCode(string line) 
{


}

int main() 
{
    string line;
    vector<string> input;
    while(getline(cin, line)) {
        input.push_back(line);
    }

    return 0;
}