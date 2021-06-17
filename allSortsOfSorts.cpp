#include<stdio.h>
#include<stdlib.h>
#include <type_traits>
using namespace std;

template <class T>
bool comparator(T a, T b) {
    return a > b;
}

template <class T>
void swap(T *a, T *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
    return;
}

template <class T>
void bubbleSort(T arr[], int n) {
    for(int i=0;i<n;i++) {
        for(int j=0;j<n-i-1;j++) {
            if(comparator(arr[j], arr[j+1])) {
                arr[j] = arr[j] + arr[j+1];
                arr[j+1] = arr[j] - arr[j+1];
                arr[j] = arr[j] - arr[j+1];
            }
        }
    }
    return;
}

template <class T>
void recursiveBubbleSort(T arr[], int n) {
    if(n==1) {
        return;
    }
    for(int i=0;i<n-1;i++) {
        if(comparator(arr[i], arr[i+1])) {
            swap(arr[i], arr[i+1]);
        }
    }
    bubbleSort(arr, n-1);
}

template <class T>
void selectionSort(T arr[], int n) {
    for(int i=0;i<n-1;i++) {
        T smallest = i;
        for(int j=i+1;j<n;j++) {
            if(comparator(arr[smallest], arr[j])) {
                smallest = j;
            }
        }
        swap(arr[smallest], arr[i]);
    }
    return;
}

template <class T>
void insertionSort(T arr[], int n) {
    for(int i=1;i<n;i++) {
        for(int j=i;j>0;j--) {
            if(comparator(arr[j-1], arr[j])) {
                swap(arr[j-1], arr[j]);
            } else {
                break;
            }
        }
    }
    return;
}

template <class T>
void recursiveInsertionSort(T arr[], int n) {
    if(n==1) {
        return;
    }
    recursiveInsertionSort(arr, n-1);
    int lastElePos = n-1;
    for(int i=n-2;i>=0;i--) {
        if(comparator(arr[i], arr[lastElePos])) {
            swap(arr[i], arr[lastElePos]);
            lastElePos = i;
        } else {
            break;
        }
    }
    return;
}

template <class T>
void merge(T arr[], int l, int m, int r) {
    T newArr[r-l+1];
    int i, j, k;
    i = l;
    j = m+1;
    k = 0;
    while(i <= m && j <=r) {
        if(arr[i] < arr[j]) {
            newArr[k++] = arr[i++];
        } else {
            newArr[k++] = arr[j++];
        }
    }
    while(i <= m) {
        newArr[k++] = arr[i++];
    }
    while(j<=r) {
        newArr[k++] = arr[j++];
    }
    for(int i=0;i<=(r-l);i++) {
        arr[l+i] = newArr[i]; 
    }
    return;
}

template <class T>
void mergeSort(T arr[], int n) {
    for(int subSize=1;subSize<=n-1;subSize*=2) {
        for(int l=0;l<n-1;l+=2*subSize) {
            int m = (n-1>l+subSize-1)?l+subSize-1:n-1;
            int r = (n-1>l+2*subSize-1)?l+2*subSize-1:n-1;
            merge(arr, l, m, r);
        }
    }
}

template <class T>
void recursiveMergeSort(T arr[], int l, int r) {
    if(l >= r) {
        return;
    }
    int m = (l+r)/2;
    mergeSort(arr, l, m);
    mergeSort(arr, m+1, r);
    merge(arr, l, m, r);
    return;
}

template <class T>
int partition(T arr[], int l, int r) {
    T pivot = arr[l];
    int firstLargest = r+1;
    for(int i=r;i>=l+1;i--) {
        if(arr[i] > pivot) {
            firstLargest--;
            swap(arr[i],arr[firstLargest]);
        }
    }
    swap(arr[firstLargest-1], arr[l]);
    return firstLargest - 1;
}

template <class T>
void quickSort(T arr[], int l, int r) {
    if(l >= r) {
        return;
    }
    int pi = partition(arr, l, r);
    quickSort(arr, l, pi-1);
    quickSort(arr, pi+1, r);
}

template <class T>
void quickSort(T arr[], int n) {
    quickSort(arr, 0, n-1);
}

template <class T>
void print(T a[], int n)  {
    for(int i=0;i<n;i++) {
        if(std::is_same<T, int>::value) {
            printf("%d ", a[i]);
        }
    }
    printf("\n");
    return;
}

int main() {
    int a[] = {13, 2, 19, 21, 5 , 1, 0};
    int n = 7;
    quickSort(a, n);
    print(a, n);
    return 0;
}