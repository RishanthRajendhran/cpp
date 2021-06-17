#include<stdio.h>
#include<stdlib.h>
#include<vector>
using namespace std;

//Indexing starts from 1 and not 0
class priorityQueue {
    vector<int> arr;
    public:
    priorityQueue() {
        arr.push_back(INT_MIN); //Dummy to offset indices by 1 
    }
    void insert(int x) {
        int lastPos = arr.size();
        arr.push_back(INT_MIN);
        while(lastPos/2 >=1 && arr[lastPos/2] > x) {
            arr[lastPos] = arr[lastPos/2];
            lastPos /= 2;
        }
        arr[lastPos] = x;
    }

    int deleteMin() {
        int min = arr[1];
        int holePos = 1;
        while(2*holePos+1 < arr.size()) {
            if(arr[2*holePos] <= arr[2*holePos+1]) {
                arr[holePos] = arr[2*holePos];
                holePos = 2*holePos;
            } else {
                arr[holePos] = arr[2*holePos+1];
                holePos = 2*holePos+1;
            }
        }
        if(holePos != arr.size()-1) {
            int lastPos = arr.size()-1;
            arr[holePos] = arr[lastPos];
            arr.erase(arr.begin() + lastPos);
        }
        return min;
    }

    void decreaseKey(int pos, int decVal) {
        if(pos > arr.size() || pos == 0 || decVal < 0) {
             if(pos==0) {
                printf("decreaseKey : Indexing starts at 1 and not 0.\n");
            } else if(decVal < 0) {
                printf("decreaseKey : decVal cannot be negative.\n");
            } else {
                printf("decreaseKey : pos %d cannot be greater than heap size %ld\n", pos, arr.size());
            }
        }
        arr[pos] -= decVal;
        int valAfterDec = arr[pos];
        while(pos/2 >=1 && arr[pos/2] > valAfterDec) {
            arr[pos] = arr[pos/2];
            pos /= 2;
        }
        arr[pos] = valAfterDec;
    }

    void increaseKey(int pos, int incVal=1) {
        if(pos >= arr.size() || pos == 0 || incVal < 0) {
            if(pos==0) {
                printf("increaseKey : Indexing starts at 1 and not 0.\n");
            } else if(incVal < 0) {
                printf("increaseKey : incVal cannot be negative.\n");
            } else {
                printf("increaseKey : pos %d cannot be greater than heap size %ld\n", pos, arr.size());
            }
            return;
        }
        arr[pos] += incVal;
        int valAfterInc = arr[pos];
        while(2*pos < arr.size()) {
            if(valAfterInc > arr[2*pos] && (2*pos+1 >= arr.size() || arr[2*pos] <= arr[2*pos+1])) {
                arr[pos] = arr[2*pos];
                pos = 2*pos;
            } else if(2*pos+1 < arr.size() && valAfterInc > arr[2*pos+1] && arr[2*pos+1] <= arr[2*pos]) {
                arr[pos] = arr[2*pos+1];
                pos = 2*pos + 1;
            } else {
                break;
            }
        }
        arr[pos] = valAfterInc;
    }

    void print() {
        for(int i=1;i<arr.size();i++) {
            printf("%d ",arr[i]);
        }
        printf("\n");
    }
};

int main() {
    priorityQueue pq;
    pq.insert(13);
    pq.insert(14);
    pq.insert(16);
    pq.insert(19);
    pq.insert(21);
    pq.insert(19);
    pq.insert(68);
    pq.insert(65);
    pq.insert(26);
    pq.insert(32);
    pq.insert(31);
    // pq.print();
    // pq.insert(14);
    pq.print();
    printf("Deleting %d from the heap.\n",pq.deleteMin());
    pq.print();
    pq.increaseKey(2, 10);
    pq.print();
    return 0;
}