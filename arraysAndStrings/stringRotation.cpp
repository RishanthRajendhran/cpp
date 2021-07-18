#include<stdio.h>
#include<stdlib.h>
#include <string>
#include<sstream>
#include<map>
#include<vector>
#include<math.h>
using namespace std; 

vector<int> findLPS(string s) {
    vector<int> lps(s.size(),0);
    int len = 0;
    int i = 1;
    while(i<s.size()) {
        if(s[i] == s[len]) {
            lps[i++] = ++len;
        } else {
            if(len!=0) {
                len = lps[len-1];
            } else {
                lps[i++] = 0;
            }
        }
    }
    return lps;
}

bool isSubstring(string s, string pattern) {
    if(pattern.size() > s.size()) {
        string temp = pattern;
        pattern = s;
        s = temp;
    }
    vector<int> lps = findLPS(pattern);
    int len = 0;
    int i = 0;
    while(i<s.size()) {
        while(len < pattern.size() && i < s.size() && s[i] == pattern[len]) {
            len++;
            i++;
        }
        if(len == pattern.size()) {
            return true;
        }
        if(len!=0) {
            len = lps[len-1];
        } else  {
            len = 0;
            i++;
        }
    }
    return false;
}

bool isRotation(string s1, string s2) {
    if(s1.size() != s2.size()) {
        return false;
    }
    return isSubstring(s1+s1, s2);
}

int main() {
    string s = "waterbottle";
    string pattern = "erbottlewat";
    vector<int> lps = findLPS(pattern);
    // for(int i=0;i<lps.size();i++) {
    //     printf("%5d ",i);
    // }
    // printf("\n");
    // for(int i=0;i<lps.size();i++) {
    //     printf("%5d ",lps[i]);
    // }
    // printf("\n");
    printf("%s, %s - %d\n",s.c_str(), pattern.c_str(), isRotation(s, pattern));
    return 0;
}