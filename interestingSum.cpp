#include<stdio.h>
#include<stdlib.h>
#include<vector>
using namespace std;

int findInterestingSum(vector<int> a) {
    int n = a.size();
    vector<pair<int, int> > minMaxSums(n, make_pair(0, 0));
    minMaxSums[n-1] = make_pair(a[n-1], a[n-1]);
    for(int i=n-3;i>=0;i-=2) {
        minMaxSums[i] = make_pair(min(a[i], a[i] + minMaxSums[i+2].first), max(a[i], a[i] + minMaxSums[i+2].second));
    }
    minMaxSums[n-2] = make_pair(a[n-2], a[n-2]);
    for(int i=n-2;i>=0;i-=2) {
        minMaxSums[i] = make_pair(min(a[i], a[i] + minMaxSums[i+2].first), max(a[i], a[i] + minMaxSums[i+2].second));
    }
    int maxInterestingSum = INT_MIN;
    for(int i=0;i<n;i++) {
        printf("%d: (%d, %d)\n",a[i], minMaxSums[i].first, minMaxSums[i].second);
        int a, b;
        a = minMaxSums[i].second;
        b = (i!=n-1)?minMaxSums[i+1].first:0;
        if((a-b) > maxInterestingSum) {
            maxInterestingSum = a-b;
        }
        if(a > maxInterestingSum) {
            maxInterestingSum = a;
        }
    }
    return maxInterestingSum;
}

int main() {
    vector<int> a{-1, 7, 13, 1, 9, 1, -11, -2, 4};
    printf("%d\n",findInterestingSum(a));
    return 0;
}