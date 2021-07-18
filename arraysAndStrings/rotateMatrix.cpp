#include<stdio.h>
#include<stdlib.h>
#include <string>
#include<sstream>
#include<map>
#include<vector>
#include<math.h>
using namespace std; 

void rotateSquareMatrix(vector<vector<int> > &M, int start=0) {
    if(start < 0 || start >= M.size()/2) {
        return;
    }
    int end = M.size()-1-start;
    for(int i=start;i<end;i++) {
        int temp = M[i][end];
        M[i][end] = M[start][i];
        M[start][i] = M[end-(i-start)][start];
        M[end-(i-start)][start] = M[end][end-(i-start)];
        M[end][end-(i-start)] = temp; 
    }
    rotateSquareMatrix(M, start+1);
}

int main() {
    vector<vector<int> > M{vector<int>{1,2,3,4,5}, vector<int>{16,17,18,19,6}, vector<int>{15,24,25,20,7}, vector<int>{14,23,22,21,8}, vector<int>{13,12,11,10,9}};
    rotateSquareMatrix(M);
    for(int i=0;i<M.size();i++) {
        for(int j=0;j<M[i].size();j++) {
            printf("%5d ",M[i][j]);
        }
        printf("\n");
    }
    return 0;
}