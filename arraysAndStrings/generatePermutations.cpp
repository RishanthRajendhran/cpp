#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<map>
#include<vector>
using namespace std;

vector<string> generateAllPermutations(string s) {
    if(s.size()==0) {
        return vector<string>{""};
    }
    vector<string> curPerms = generateAllPermutations(s.substr(1));
    vector<string> newPerms;
    for(int i=0;i<curPerms.size();i++) {
        for(int pos=0;pos<=curPerms[i].size();pos++) {
            string curStr = curPerms[i].substr(0,pos);
            curStr.push_back(s[0]);
            curStr.append(curPerms[i].substr(pos));
            newPerms.push_back(curStr);
        }
    }
    return newPerms;
}

int main() {
    string s = "amrit";
    vector<string> perms = generateAllPermutations(s);
    for(int i=0;i<perms.size();i++) {
        printf("%s\n",perms[i].c_str());
    }
    return 0;
}