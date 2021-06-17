#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<string>
#include<map>
#include<queue>
#include<stack>
using namespace std;

pair<bool, stack<int>> findHamiltonianPath(stack<int> path, vector<bool> visited, map<int, vector<int>> mappings, vector<string> seqs) {
    if(path.empty()) {
        return make_pair((path.size() == mappings.size()), path);
    }
    int lastNode = path.top();
    if(visited[lastNode] == 1) {
        return make_pair((path.size() == mappings.size()), path);
    }
    visited[lastNode] = 1;
    map<int, vector<int>>::iterator it = mappings.find(lastNode);
    if(it == mappings.end()) {
        return make_pair((path.size() == mappings.size()), path);
    }
    for(int i=0; i<it->second.size(); i++) {
        if(visited[it->second[i]] == 1) {
            continue;
        }
        path.push(it->second[i]);
        printf("Going from %s to %s\n", seqs[lastNode].c_str(), seqs[it->second[i]].c_str());
        pair<bool, stack<int>> pathFound = findHamiltonianPath(path, visited, mappings, seqs);
        if(pathFound.first == true) {
            return pathFound;
        }
        printf("Last move failed!\n");
        path.pop();
        visited[it->second[i]] = 0;
    }
    return make_pair((path.size() == mappings.size()), path);
}

int main() {
    vector<string> seqs = {"ACCG","ACGG","ACTA","ACTG","ATGC","ATTT","CCGA","CCTA","CGAC","CGAG","CGGC","CTAT","CTAT","CTGG","GACG","GACT","GCCT","GCGA","GGAC","GGCC","TACC","TATG","TATT","TGCG","TGGA","TTAC","TTTA"};
    vector<string> prefixes;
    vector<string> suffixes;
    vector<int> possibleEnds;
    map<int, vector<int>> mappings;
    int preSize = seqs[0].size()-1;
    int subStart = 1;
    do {
        prefixes.clear();
        suffixes.clear();
        possibleEnds.clear();
        for(int i=0;i<seqs.size();i++) {
            prefixes.push_back(seqs[i].substr(0, preSize));
            suffixes.push_back(seqs[i].substr(subStart));
        }
        for(int i=0;i<suffixes.size();i++) {
            bool found = false;
            for(int j=0;j<prefixes.size();j++) {
                if(prefixes[j] == suffixes[i] && seqs[i].c_str() != seqs[j].c_str()) {
                    found = true;
                    break;
                }
            }
            if(!found) {
                possibleEnds.push_back(i);
            }
        }
        preSize--;
        subStart++;
        if(preSize<=0 || subStart >= seqs[0].size()) {
            printf("Unable to find possible ending %ld-mer!\n",seqs[0].size());
            return 0;
        }
    }while(0);

    for(int i=0;i<prefixes.size();i++) {
        bool found = false;
        vector<int> possiblePrevs;
        for(int j=0;j<suffixes.size();j++) {
            if(suffixes[j] == prefixes[i]) {
                found = true;
                possiblePrevs.push_back(j);
            }
        }
        mappings.insert(make_pair(i, possiblePrevs));
    }
    int count = mappings.size()-1;
    queue<int> q;
    q.push(mappings.find(possibleEnds[0])->first);
    vector<bool> visited(seqs.size(), false);
    while(!q.empty()) {
        map<int, vector<int>>::iterator it = mappings.find(q.front());
        visited[q.front()] = true;
        q.pop();
        if(it != mappings.end()) {
            printf("%d. String: %s, Possible Prevs: ", count--, seqs[(it->first)].c_str());
            for(int j=0;j<it->second.size(); j++) {
                printf("%s ", seqs[it->second[j]].c_str());
                if(!visited[it->second[j]]) {
                    q.push(it->second[j]);
                    visited[it->second[j]] = true;
                }
            }
            printf("\n");
        }
    }
    printf("Searching for Hamiltonian Path...\n");
    visited.assign(seqs.size(), false);
    stack<int> path;
    path.push(possibleEnds[0]);
    pair<bool, stack<int>> pathFound = findHamiltonianPath(path, visited, mappings, seqs);
    if(pathFound.first == false) {
        printf("No Hamiltonian Path found!\n");
    } else {
        printf("Hamiltonian Path found:\n");
        string space = "";
        string output = "";
        while(!pathFound.second.empty()) {
            printf("%s%s\n",space.c_str(), seqs[pathFound.second.top()].c_str());
            if(output.size() == 0) {
                output = seqs[pathFound.second.top()];
            } else {
                output += seqs[pathFound.second.top()][seqs[pathFound.second.top()].size()-1];
            }
            pathFound.second.pop();
            space += " ";
        }
        printf("Output string: %s\n",output.c_str());
    }
    return 0;
}
