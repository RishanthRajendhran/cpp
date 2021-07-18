#include<stdio.h>
#include<stdlib.h>
#include <string>
#include<sstream>
#include<map>
#include<vector>
#include<math.h>
using namespace std; 

void zeroMatrix(vector<vector<int> > &M) {
    //Assuming the number of rows and columns of M is less than the number of bits in a int variable
    int zeroRows = 0;
    int zeroCols = 0;
    for(int i=0;i<M.size();i++) {
        for(int j=0;j<M[i].size();j++) {
            if(M[i][j] == 0) {
                zeroRows |= (1 << i);
                zeroCols |= (1 << j);
            }
        }
    }
    for(int i=0;i<M.size();i++) {
        if(zeroRows & (1 << i)) {
            for(int j=0;j<M[i].size();j++) {
                M[i][j]  = 0;
            }
        }
    }
    for(int j=0;j<M[0].size();j++) {
        if(zeroCols & (1 << j)) {
            for(int i=0; i<M.size(); i++) {
                M[i][j] = 0;
            }
        }
    }
}

int main() {
    vector<vector<int> > M{vector<int>{1,2,0,4,5}, vector<int>{16,0,18,19,6}, vector<int>{15,24,25,20,7}, vector<int>{14,23,22,21,8}, vector<int>{13,12,11,10,9}};
    for(int i=0;i<M.size();i++) {
        for(int j=0;j<M[i].size();j++) {
            printf("%5d ",M[i][j]);
        }
        printf("\n");
    }
    printf("---------------------------------\n");
    zeroMatrix(M);
    for(int i=0;i<M.size();i++) {
        for(int j=0;j<M[i].size();j++) {
            printf("%5d ",M[i][j]);
        }
        printf("\n");
    }
    return 0;
}