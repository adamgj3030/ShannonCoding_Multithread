#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

//shannonCode takes string and displays information
void shannonCode(string line) {

    int len = line.length();
    int totalChar = 0;

    //dictionary to hold frequency of each character
    map<char, int> charCount;

    for (int i = 0; i < len; ++i) {
      char currChar = line[i];

      charCount[currChar]++;

      totalChar++;
      cout << currChar << endl;
    }


    for (auto& it : charCount) {
        cout << it.first << " : " << it.second << endl;
    }
};

int main() {
    string test = "AAABAAABAAAAMMAAAAAU";
    shannonCode(test);
    return 0;
}