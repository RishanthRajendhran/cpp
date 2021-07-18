#include<stdio.h>
#include<stdlib.h>
#include <string>
#include<sstream>
#include<map>
#include<vector>
#include<math.h>
using namespace std; 

string compressString(string s) {
    string newStr;
    int lastCount = 0;
    for(int i=0;i<s.size();i++) {
        lastCount++;
        if((i == s.size()-1) || (s[i] != s[i+1])) {
            newStr.push_back(s[i]);
            std::stringstream toAdd;
            toAdd << lastCount;
            newStr.append(toAdd.str());
            lastCount = 0;
        }
    }
    return (s.size() < newStr.size())?s:newStr;
}

int main() {
    string s = "aaabbbabbbbbaccccdasss";
    printf("%s - %s\n",s.c_str(), compressString(s).c_str());
    return 0;
}