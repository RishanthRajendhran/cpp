#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<map>
using namespace std;


long long findSplit(int pos, long long leftSum, int arr[], int n, int k, map<pair<pair<int, int>, int>, long long> & minTimes) {
    map<pair<pair<int, int>, int>, long long>::iterator it = minTimes.find(make_pair(make_pair(pos, leftSum), k));
    if(it != minTimes.end()) {
        return it->second;
    } else {
        if((n-pos)<=0) {
            if(k==0) {  //Empty split
                return leftSum;
            } else {    //Invalid split
                return LLONG_MAX;
            }
        } else if((n-pos)==1) { //Last element left
            if(k==0) {  //No more splits to make
                return leftSum+arr[pos];
            } else {    //More splits needed but only one ele left => INVALID
                return LLONG_MAX;
            }
        } else if(k==0 && (n-1-pos) > 0) {
            long long t = 0;
            for(int i=pos;i<n;i++) {
                t += arr[i];
            }
            minTimes.insert(make_pair(make_pair(make_pair(pos, leftSum), k), leftSum+t));
            return leftSum + t;
        }
        long long t1, t2, t;
        //Make a split right after the current position
        t1 = max(leftSum + arr[pos], findSplit(pos+1, 0, arr, n, k-1, minTimes));
        //Choose not to make a split after the current position
        t2 = findSplit(pos+1, leftSum + arr[pos], arr, n, k, minTimes);
        t = min(t1, t2);
        // cout<<"k :"<<k<<", pos :"<<pos<<", leftSum :"<<leftSum<<", t1 :"<<t1<<", t2 :"<<t2<<", t :"<<t<<endl;
        minTimes.insert(make_pair(make_pair(make_pair(pos,leftSum), k), t));
        return t;
    }
}
long long minTime(int arr[], int n, int k)
{
    // code here
    // return minimum time
    map<pair<pair<int, int>, int>, long long> minTimes;
    if(k-1 >= n) {
        return *max_element(arr, arr+n);
    } else {
        return findSplit(0, 0, arr, n, k-1, minTimes);
    }
}

long long minTime_binarysearch(int arr[], int n, int k)
{
    // code here
    // return minimum time
    int max = INT_MIN;
    long long sum = 0;
    for(int i=0;i<n;i++) {
        sum +=arr[i];
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    long long left, right, mid;
    left = max;
    right = sum;
    long long answer;
    while(left <= right) {
        // cout<<left<<", "<<right<<endl;
        mid = (left + right)/2;
        long long sum = 0;
        int split = 0;
        bool invalid = false;
        for(int i=0;i<n;i++) {
            sum += arr[i];
            if(sum > mid) {
                split++;
                sum = arr[i];
            }
            if(split >= k) {
                invalid = true;
                break;
            }
        }
        if(!invalid) {
            answer = mid;
            right = mid-1;
        } else {
            left = mid+1;
        }
    }
    return answer;
}


int main() {
    int arr[] = {5, 10, 30, 20, 15};
    int n = sizeof(arr)/sizeof(int);
    printf("%lli\n", minTime(arr, n, 3-1));
    return 0;
}