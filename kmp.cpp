#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<string>
using namespace std;

vector<int> findLPS(string s) {
    vector<int> lps(s.size(), 0);
    int i = 1;
    int len = 0;
    while(i<s.size()) {
        if(s[i] == s[len]) {
            lps[i++] = ++len;
        } else {
            if(len) {
                len = lps[len-1];   
            } else {
                lps[i++] = 0;
            }
        }
    }
    return lps;
}

vector<int> findMatchingIndices(string s, string p) {
    vector<int> lps = findLPS(p);
    vector<int> inds;
    int sPos = 0;
    int pPos = 0;
    while(sPos<s.size()) {
        while(s[sPos] == p[pPos]) {
            sPos++;
            pPos++;
        } 
        if(pPos == p.size()) {
            inds.push_back(sPos - pPos);
            pPos = lps[pPos-1];
        } else {
            if(pPos) {
                pPos = lps[pPos-1];
            } else {
                sPos++;
            }
        }
    }
    return inds;
}

int main() {
    vector<int> inds = findMatchingIndices("AAAAABAAAABA","AAAA");
    for(int i=0;i<inds.size();i++) {
        printf("%d, ",inds[i]);
    }
    return 0;
}