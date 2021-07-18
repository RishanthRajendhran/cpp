#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<map>
#include<vector>
using namespace std;

bool isPermutation(string s1, string s2) {
    if(s2.length() > s1.length()) {
        string temp = s1;
        s1 = s2;
        s2 = temp;
    }
    map<char, int> charCounts;
    for(int i=0;i<s1.size();i++) {
        auto it =  charCounts.find(s1.at(i));
        if(it == charCounts.end()) {
            charCounts.insert(make_pair(s1.at(i), 1));
        } else {
            it->second++;
        }
    }
    for(int i=0;i<s2.size();i++) {
        auto it = charCounts.find(s2.at(i));
        if(it == charCounts.end()) {
            return false;
        }
        it->second--;
        if(it->second == 0) {
            charCounts.erase(it);
        }
    }
    return true;
}

int main() {
    string s1 = "amrit";
    string s2 = "ritam";
    printf("%s and %s permutations? %d\n",s1.c_str() ,s2.c_str() , isPermutation(s1, s2));
    return 0;
}