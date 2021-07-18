#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<map>
#include<vector>
using namespace std;

bool isPalPerm(string s) {
    // map<char, int>  charCounts;
    // int len = 0;
    // for(int i=0;i<s.size();i++) {
    //     if(s.at(i) == ' ') {
    //         continue;
    //     }
    //     len++;
    //     auto it = charCounts.find(tolower(s.at(i)));
    //     if(it == charCounts.end()) {
    //         charCounts.insert(make_pair(tolower(s.at(i)),1));
    //     } else {
    //         it->second++;
    //     }
    // }
    // bool leeway = len%2;
    // for(auto i=charCounts.begin();i!=charCounts.end();i++) {
    //     if(i->second%2) {
    //         if(!leeway) {
    //             return false;
    //         }
    //         leeway =  false;
    //     }
    // }
    // return true;
    //Optimized solution - All characters are assumed to be lowercase english alphabets
    int bitVector = 0;
    for(int i=0;i<s.size();i++) {
        if(s[i] == ' ') {
            continue;
        }
        int mask = 1 << (s[i] - 'a');
        if((bitVector & mask) == 0) {
            bitVector = bitVector | mask;
        } else {
            bitVector = (bitVector & (~mask));
        }
    }
    return (bitVector==0 || ((bitVector & (bitVector - 1)) == 0));
}

int main() {
    string s = "Tact Coa";
    // s = "ymamlalaa";
    printf("%s - %d\n",s.c_str(),isPalPerm(s));
    return 0;
}