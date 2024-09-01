#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

bool compare(pair<pair<char, int>, string> a, pair<pair<char, int>, string> b) {
    if (a.first.second != b.first.second) {
        return a.first.second > b.first.second;
    }
    return a.first.first > b.first.first;
}

string decimalToBinary(float decimal, int precision) {
    string binary = "";
    while (decimal > 0 && precision > 0) {
        double temp = decimal * 2;
        if (temp >= 1) {
            binary += "1";
            decimal = temp - 1;
        }
        else {
            binary += "0";
            decimal = temp;
        }
        --precision;
    }

    while (precision > 0) {
        --precision;
        binary += "0";
    }

    return binary;
}

void shannonCode(string line) {
    int len = line.length();
    
    map<char, int> charCountMap;

    for (int i = 0; i < len; ++i) {
        char character = line[i];
        ++charCountMap[character];
    }

    vector<pair<pair<char, int>, string>> charCodeVec; 
    
    for (auto charCount : charCountMap) {
        char character = charCount.first;
        int freq = charCount.second;

        pair<pair<char, int>, string> tempPair {{character, freq}, ""};
        charCodeVec.push_back(tempPair);
    }

    sort(charCodeVec.begin(), charCodeVec.end(), compare);

    float cumulativeProbability = 0;
    map<char, string> charCodeMap;

    for (auto& temp : charCodeVec) {

        float probability = ((float)temp.first.second/len);

        int precision = ceil(log2(1/probability));

        string ShannonCode = decimalToBinary(cumulativeProbability, precision);
        temp.second = ShannonCode;
        charCodeMap[temp.first.first] = ShannonCode;

        cumulativeProbability += probability;
    }

    cout << "Message: " << line << endl;
    cout << endl;

    cout << "Alphabet:" << endl;
    for (auto temp : charCodeVec) {
        cout << "Symbol: "<< temp.first.first
        << ", Frequency: " << temp.first.second 
        << ", Shannon code: " << temp.second << endl;
    }

    cout << endl;

    string encodeMsg = "";

    for (int i = 0; i < len; ++i) {
        encodeMsg += charCodeMap[line[i]];
    }

    cout << "Encoded message: " << encodeMsg << endl;
}

int main() {
    string line;
    vector<string> input;
    while(getline(cin, line)) {
        input.push_back(line);
    }

    for (auto message : input) {
        shannonCode(message);
        cout << endl;
    }

    return 0;
}
