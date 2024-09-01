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

    float cumulativeProbability = 0;

    for (auto& temp : charCodeVec) {
        cout << "Frequency: " << temp.first.second << endl;

        float probability = ((float)temp.first.second/len);
        cout << "Probability: " << probability << endl;

        int precision = ceil(log2(1/probability));
        cout << "Precision: " << precision << endl;
        cout << "cumulativeProbability: " << cumulativeProbability << endl;

        string ShannonCode = decimalToBinary(cumulativeProbability, precision);
        cout << "ShannonCode: " << ShannonCode << endl;

        temp.second = ShannonCode;

        cumulativeProbability += probability;
    }


    return 0;
}
