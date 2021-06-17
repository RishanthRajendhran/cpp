#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<string>
#include<vector>
#include<math.h>
using namespace std;

void swap(pair<int, int> *a, pair<int, int> *b) {
    int x,y;
    x = a->first;
    y = a->second;
    a->first = b->first;
    a->second = b->second;
    b->first = x;
    b->second = y;
    return;
}

int partition(vector< pair<int, int> > arr, int low, int high, int basedOn = 1) {
    //Partition w.r.t. first element 
    int pivot = (low+high)/2;
    int firstLargest = high+1;
    int i = high;
    while(i >= low) {
        if( (basedOn == 1 && arr[i].first > arr[pivot].first) || (basedOn == 2 && arr[i].second > arr[pivot].second) ) {
            firstLargest--;
            swap(arr[i], arr[firstLargest]);
        }
        i--;
    }
    firstLargest--;
    swap(arr[pivot] , arr[firstLargest]);
    return firstLargest;
}

void quickSort(vector< pair<int, int> > arr, int low, int high, int basedOn = 1) {
    if(low<=high) {
        return;
    }
    int pi = partition(arr, low, high, basedOn);
    quickSort(arr, low, pi, basedOn);
    quickSort(arr, pi+1, high, basedOn);
    return;
}

float calcDist(pair<int,int> a, pair<int,int> b) {
    return sqrt(pow((a.first - b.first),2) + pow((a.second - b.second),2));
}

float closestInStrip(vector< pair<int, int> > strip, int n, int d) {
    float min;
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n && (strip[j].second - strip[i].second < d);j++) {
            float curDist = calcDist(strip[i], strip[j]);
            if(curDist < d) {
                min = curDist;
            }
        }
    }
    return min;
}

float bruteForce(vector< pair<int,int> > arr, int n) {
    if(n<2) {
        return -1;
    }
    float min = -1;
    for(int i=0;i<n;i++) {
        for(int j=i+1; j<n; j++) {
            float dist = calcDist(arr[i], arr[j]);
            if(min == -1 || min > dist) {
                min = dist;
            }
        }
    }
    return min;
}

float splitRegion(vector< pair<int,int> > arrX, vector< pair<int,int> > arrY, int n) {
    if(n <= 3) {
        return bruteForce(arrX, n);
    }

    int mid = n/2;
    pair<int, int> midPt = arrX[mid];
    vector< pair<int, int> > arrL, arrR;
    for(int i=0;i<n;i++) {
        if(arrY[i].first <= midPt.first && arrL.size() < mid) {
            arrL.push_back(arrY[i]);
        } else {
            arrR.push_back(arrY[i]);
        }
    }

    float l, r, d;
    l = splitRegion(arrX, arrL, mid);
    r = splitRegion(arrX, arrL, n-mid);
    d = min(l, r);

    vector< pair<int, int> > strip;
    for(int i=0;i<n;i++) {
        if(abs(arrX[i].first - midPt.first) <  d) {
            strip.push_back(arrX[i]);
        }
    }
    return closestInStrip(strip, strip.size(), d);
}

float findClosestPoints(vector< pair<int, int> > arr) {
    vector< pair<int, int> > arrX = arr;
    vector< pair<int, int> > arrY = arr;
    quickSort(arrX, 0, arrX.size()-1, 1);
    quickSort(arrY, 0, arrX.size()-1, 1);
    return splitRegion(arrX, arrY, arrX.size());
}

int main() {
    return 0;
}