#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<map>
#include<vector>
using namespace std;

class wordDictionary {
    map<string, bool> words;
    public:
    void addWord(string s) {
        auto it = words.find(s);
        if(it == words.end()) {
            words.insert(make_pair(s, true));
        }
    }

    void buildDictionary(vector<string> s) {
        for(int i=0;i<s.size();i++) {
            auto it = words.find(s[i]);
            if(it == words.end()) {
                words.insert(make_pair(s[i], true));
            }
        }
    }
    string findLongestWordComposedOfOtherWords() {
        if(words.size() == 0) {
            return "/*Dictionary is empty!*/";
        }
        string maxString = "";
        for(auto it=words.begin();it!=words.end();it++) {
            if(it->second && canBuildFromOtherWords(it->first)) {
                if(maxString.size() < (it->first).size()) {
                    maxString = it->first;
                }
            }
        }
        return maxString;
    }

    bool canBuildFromOtherWords(string s, bool oriWord = true) {
        auto it = words.find(s);
        if(it != words.end() && !oriWord) {
            return it->second;
        }

        for(int i=1;i<s.size(); i++) {
            string left = s.substr(0,i);
            string right = s.substr(i);
            auto check = words.find(left);
            if(check != words.end() && check->second) {
                if(canBuildFromOtherWords(right, false)) {
                    return true;
                }
            }
        }
        words.insert(make_pair(s, false));
        return false;
    }
};

int main() {
    vector<string>  words{"geeks", "what", "is", "your", "for", "geeksforgeekshellonamewhat is", "hello", "you", "name", " ", "what is your name"};
    wordDictionary wd;
    wd.buildDictionary(words);
    printf("%s\n",wd.findLongestWordComposedOfOtherWords().c_str());
    return 0;
}