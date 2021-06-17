#include<stdio.h>
#include<stdlib.h>
#include<vector>
using namespace std;
int _merge(int arr[], int low, int high) {
    vector<int> newArr(high-low+1, 0);
    int mid = (low+high)/2;
    int count = 0;
    int i, j, k;
    i = low;
    j = mid+1;
    k = 0;
    while(i <= mid && j<= high) {
        if(arr[i] <= arr[j]) {
            newArr[k++] = arr[i++];
        } else {
            newArr[k++] = arr[j++];
            count += (mid+1-i);
        }
    }

    while(i <= mid) {
        newArr[k++] = arr[i++];
    }

    while(j <= high) {
        newArr[k++] = arr[j++];
    }

    for(int i=low, k=0;i<=high;i++,k++) {
        arr[i] = newArr[k];
    }
    return count;
}

int _countInversionPairs(int arr[], int low, int high) {
    if(low >= high) {
        return 0;
    }
    int mid = (low+high)/2;
    int count = 0;
    count += _countInversionPairs(arr, low, mid);
    count += _countInversionPairs(arr, mid+1, high);
    count += _merge(arr, low, high);
    return count;
}

int countInversionPairs(int arr[], int low, int high) {
    int newArr[high+1];
    for(int i=0;i<=high;i++) {
        newArr[i] = arr[i];
    }
    return _countInversionPairs(newArr, low, high);
}

int main() {
    int arr[] = {13, 7, -2, -5, 11, 17, 9};
    printf("%d\n", countInversionPairs(arr, 0, 6));
    return 0;
}