#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    string line = "AAABAAABAAAAMMAAAAAU";
    int len = line.length();
    
    map<char, int> charMap;

    for (int i = 0; i < len; ++i) {
        char character = line[i];
        ++charMap[character];
    }

    vector< pair <pair<int, char>, string>> charCodeVec; 
    
    for (auto charCount : charMap) {
        char character = charCount.first;
        int freq = charCount.second;

        pair <pair<int, char>, string> tempPair {{freq, character}, ""};
        charCodeVec.push_back(tempPair);

    }

    sort(charCodeVec.begin(), charCodeVec.end());

    for (auto& temp : charCodeVec) {
        cout << temp.first.first << " : " << temp.first.second << " : " << temp.second << endl;
    }

    
    return 0;
}