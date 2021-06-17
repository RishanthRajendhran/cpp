#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<string>
using namespace std;

bool isUnique(string s) {
    map<char, int> freq;
    for(int i=0;i<s.length();i++) {
        map<char, int>::iterator it = freq.find(s.at(i));
        if(it != freq.end()) {
            return false;
        }
        freq.insert(make_pair(s.at(i),1));
    }
    return true;
}

bool checkIfPermutation(string s1, string s2) {
    map<char, int> freq;
    for(int i=0;i<s1.length();i++) {
        map<char, int>::iterator it = freq.find(s1.at(i));
        if(it != freq.end()) {
            it->second++;
        }
        freq.insert(make_pair(s1.at(i),1));
    }
    for(int i=0;i<s2.length();i++) {
        map<char, int>::iterator it = freq.find(s2.at(i));
        if(it != freq.end()) {
            it->second--;
            if(it->second == 0) {
                freq.erase(s2.at(i));
            }
        } else {
            return false;
        }
    }
    return (freq.size() == 0);
}

string replaceSpaces(string s, int len) {
    int numSpaces = 0;
    for(int i=0;i<len;i++) {
        if(s[i] == ' ') {
            numSpaces++;
        }
    }
    int i = len + 2*numSpaces - 1;
    int j = len-1;
    if(s.length() < i) {
        printf("Inadequate space in string\n");
        return s;
    }
    if(s.length() > len) {
        s[len] = '\0';
    }
    while(j>=0) {
        if(s[j] == ' ') {
            s[i] = '0';
            s[i-1] = '2';
            s[i-2] = '%';
            i-=3;
        } else {
            s[i] = s[j];
            i-=1;
        }
        j-=1;
    }
    return s;
}

int main() {
    string a = "ri sh ant hi      ", b = "rishi";
    printf("%s\n", replaceSpaces(a, 11).c_str());
    return 0;
}