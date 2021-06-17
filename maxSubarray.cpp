#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<climits>
#include<tuple>
#include<ctime>
using namespace std;

pair< pair<int, int>, int> findMaxCrossSubarray(vector<int> arr, int low, int high) {
    int lsum = INT_MIN, rsum = INT_MIN, sum = 0;
    int left, right, mid = (low+high)/2;
    for(int i=mid;i>=0;i--) {
        sum += arr[i];
        if(sum >= lsum) {
            lsum = sum;
            left = i;
        }
    }
    sum = 0;
    for(int j=mid+1;j<=high;j++) {
        sum += arr[j];
        if(sum >= rsum) {
            rsum = sum;
            right = j;
        }
    }
    return make_pair(make_pair(left,right), lsum+rsum);
}

pair< pair<int, int>, int> findMaxSubarray(vector<int> arr, int low, int high) {
    if(low == high) {
        return make_pair(make_pair(low,high), arr[low]);
    } else {
        int mid = (low+high)/2;
        pair< pair<int, int>, int> left, right, cross;
        left = findMaxSubarray(arr, low, mid);
        right = findMaxSubarray(arr, mid+1, high);
        cross = findMaxCrossSubarray(arr, low, high);
        if(left.second >= right.second && left.second >= cross.second) {
            return left;
        }
        if(right.second >= left.second && right.second >= cross.second) {
            return right;
        }
        return cross;
    }
}

tuple<int, int, int> findMaxSubarrayBruteforce(vector<int> arr, int low, int high) {
    int maxSum = INT_MIN, maxl, maxr;
    for(int i=low; i<=high; i++) {
        int sum = 0;
        for(int j=i;j<=high;j++) {
            sum += arr[j];
            if(sum >= maxSum)  {
                maxSum = sum;
                maxl = i;
                maxr = j;
            }
        }
    }
    return tie(maxl, maxr, maxSum);
}

tuple<int, int, int> findMaxSubarrayNonrecursive(vector<int> arr, int low, int high) {
    int maxSum = arr[0], maxl = 0, maxr = 0;
    int curSum = 0;
    for(int i=1; i<=high;i++) {
        if(maxr == i-1) {
            if(arr[i] > 0) {
                maxSum += arr[i];
                maxr = i;
            }
        } else {
            for(int j=maxr+1; j<=i; j++) {
                curSum += arr[j];
            }
            if(curSum > 0) {
                maxSum += curSum;
                maxr = i;
            }
            curSum = 0;
        }
    }
    return tie(maxl, maxr, maxSum);
}


int main() {
    time_t start, finish;
    vector<int> arr{13,-2,-3,5,7,9,-8,1};
    tuple<int, int, int> res;
    time(&start);
    res = findMaxSubarrayNonrecursive(arr, 0, arr.size()-1);
    time(&finish);
    printf("left = %d, right = %d, sum = %d\n",get<0>(res), get<1>(res), get<2>(res));
    printf("Time taken = %f s\n",difftime(finish, start));
    // pair<pair<int, int>, int> res;
    // res = findMaxSubarray(arr, 0, arr.size()-1);
    // printf("left = %d, right = %d, sum = %d\n",res.first.first, res.first.second, res.second);
    return 0;
}