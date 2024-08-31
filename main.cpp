#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

bool compare(pair<pair<char, int>, string> a, pair<pair<char, int>, string> b) {
    if (a.first.second != b.first.second) {
        return a.first.second > b.first.second;
    }
    return a.first.first > b.first.first;
}

int main() {
    string line = "AAABAAABAAAAMMAAAAAU";
    int len = line.length();
    
    map<char, int> charMap;

    for (int i = 0; i < len; ++i) {
        char character = line[i];
        ++charMap[character];
    }

    vector<pair<pair<char, int>, string>> charCodeVec; 
    
    for (auto charCount : charMap) {
        char character = charCount.first;
        int freq = charCount.second;

        pair<pair<char, int>, string> tempPair {{character, freq}, ""};
        charCodeVec.push_back(tempPair);
    }

    sort(charCodeVec.begin(), charCodeVec.end(), compare);

    for (auto temp : charCodeVec) {
        cout << temp.first.first << " , " << temp.first.second << " , " << temp.second << endl;
    }

    return 0;
}
