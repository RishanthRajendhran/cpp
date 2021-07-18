#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<map>
#include<vector>
#include<math.h>
using namespace std; 

bool isNeditsAway(string s1, string s2, int n) {
    if(s1.size() == 0 && s2.size() == 0) {  //Both strings are empty
        return true;
    } else if(s1.size() == 0 || s2.size() == 0) {   //Exactly  one string is empty
        if(n>0) {   //Edits allowed?
            return true;
        } else {
            return false;
        }
    }
    if(s1[0] != s2[0]) {
        if(n<=0) {
            return false;
        }
        bool res;
        if(s1.size() - s2.size() != 0) {
            //Insert character in s1
            res = isNeditsAway(s1, s2.substr(1), n-1); 
            if(res) {
                return true;
            }
            //Insert character in s2
            res = isNeditsAway(s1.substr(1), s2, n-1); 
            if(res) {
                return true;
            }
            //Checking for remove is redundant since insert and delete both require 1 edit 
            // //Remove character in s1
            // res = isNeditsAway(s1.substr(1), s2, n-1); 
            // if(res) {
            //     return true;
            // }
            // //Remove character in s2
            // res = isNeditsAway(s1, s2.substr(1), n-1); 
            // if(res) {
            //     return true;
            // }
        } else {
            //Replace character in s1/s2
            res = isNeditsAway(s1.substr(1), s2.substr(1), n-1); 
            if(res) {
                return true;
            }
        }
    } else {
        return isNeditsAway(s1.substr(1), s2.substr(1), n);
    }
    return false;
}

bool isOneEditAway(string s1, string s2) {
    if(abs(int(s1.size() - s2.size())) > 1) {
        return false;
    }
    return isNeditsAway(s1, s2, 1);
}

int main() {
    string s1 = "pale";
    string s2 = "bae";
    printf("oneEditAway(%s, %s) - %d\n",s1.c_str(), s2.c_str(), isOneEditAway(s1,s2));
    return 0;
}