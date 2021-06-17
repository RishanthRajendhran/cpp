#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<string>
#include<map>
#include<queue>
#include<stack>
using namespace std;
int m = 12, s = 7, d = 3;

vector<pair<int, vector<char> > > findPath(int str1Start, int str2Start, string str1, string str2, vector<char> path, int score) {
    if(str1Start == str1.size() || str2Start == str2.size()) {
        return vector<pair<int, vector<char> > >(1, make_pair(score, path));
    }
    if(str1.at(str1Start) == str2.at(str2Start)) {  //Match
        path.push_back('M');
        return findPath(str1Start+1, str2Start+1, str1, str2, path, score+m);
    } else {    //Mismatch, insertion or deletion
        vector<pair<int, vector<char> > > allPaths;
        vector<string> possibleMoves {"misMatch", "insertion", "deletion"};
        for(int i=0; i<possibleMoves.size(); i++) {
            if(possibleMoves[i] == "misMatch") {
                path.push_back('X');
                vector<pair<int, vector<char> > > newPaths = findPath(str1Start+1, str2Start+1, str1, str2, path, score-s);
                allPaths.insert(allPaths.end(), newPaths.begin(), newPaths.end());
                path.pop_back();
            } else if(possibleMoves[i] == "insertion") {
                path.push_back('I');
                vector<pair<int, vector<char> > > newPaths = findPath(str1Start, str2Start+1, str1, str2, path, score-d);
                allPaths.insert(allPaths.end(), newPaths.begin(), newPaths.end());
                path.pop_back();
            } else if(possibleMoves[i] == "deletion") {
                path.push_back('D');
                vector<pair<int, vector<char> > > newPaths = findPath(str1Start+1, str2Start, str1, str2, path, score-d);
                allPaths.insert(allPaths.end(), newPaths.begin(), newPaths.end());
                path.pop_back();
            }
        }
        return allPaths;
    }
}

static bool comparator(pair<int, vector<char> > a, pair<int, vector<char> > b)  {
    return a.first > b.first;
}

int main() {
    string str1 = "TAACATTTTGGCACGGTGTG", str2 = "TAATTTTGCCGGTGTG";
    vector<char> rows(str1.begin(), str1.end());
    vector<char> cols(str2.begin(), str2.end());
    int str1Start = 0, str2Start = 0;
    vector<char> path;
    vector<pair<int, vector<char> > > pathFound; 
    pathFound = findPath(str1Start, str2Start, str1, str2, path, 0);
    sort(pathFound.begin(), pathFound.end(), comparator);
    printf("Top 10 sequence alignments:\n");
    for(int i=0;i<min(10, int(pathFound.size()));i++) {
        printf("Score: %d\n",pathFound[i].first);
        printf("String: %s\n",string(pathFound[i].second.begin(), pathFound[i].second.end()).c_str());
    }
    return 0;
}