#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<map>
using namespace std;
bool allCharactersUnique(string s) {
    // map<char, bool> seenChars;
    // for(int i=0; i<s.size();i++) {
    //     if(seenChars.find(s.at(i)) != seenChars.end()) {
    //         return false;
    //     } 
    //     seenChars.insert(make_pair(s.at(i), true));
    // }
    // return true;
    //If possible characters are all lowercase english alphabets
    int seenChars = 0;
    for(int i=0;i<s.size();i++) {
        int curChar = s.at(i) - 'a';
        if((seenChars & (1 << curChar)) > 0) {
            return false;
        }
        seenChars = seenChars | (1 << curChar);
    }
    return true;
    // //Without using additional data structures 
    // for(int i=0;i<s.size();i++) {
    //     for(int j=i+1;j<s.size();j++) {
    //         if(s.at(i) == s.at(j)) {
    //             return false;
    //         }
    //     }
    // }
    // return true;
}

int main() {
    string s1 = "rishanth";
    string s2 = "struct";
    string s3 =  "lowercas";
    printf("%s -  %d\n",s1.c_str(), allCharactersUnique(s1));
    printf("%s -  %d\n",s2.c_str(), allCharactersUnique(s2));
    printf("%s -  %d\n",s3.c_str(), allCharactersUnique(s3));
    return 0;
}