#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<string>
#include<vector>
#include<stack>
#include<climits>
using namespace std;

class binaryTree {
    vector<int> tree;
    map<int, int> counts;
    public:
    binaryTree() {
        tree.push_back(INT_MIN); //Dummy to offset starting index
    }
    void insertNode(int d) {
        tree.push_back(d);
    }
    void deleteNode(int d) {
        for(int i=0;i<tree.size();i++) {
            if(tree[i] == d) {
                tree.erase(tree.begin()+i);
                break;
            }
        }
    }

    int getCount(int sum) {
        map<int, int>::iterator it = counts.find(sum);
        if(it == counts.end()) {
            return 0;
        } else {
            return it->second;
        }
    }

    void changeCount(int curSum, int del) {
        map<int, int>::iterator it = counts.find(curSum);
        if(it != counts.end()) {
            int newCount = it->second + del;
            if(newCount == 0) {
                counts.erase(it);
            } else {
                it->second = newCount;
            }
        } else if(del > 0) {
            counts.insert(make_pair(curSum, del));
        }
    }

    int _countPathWithSum(int pos, int sum, int curSum) { //For internal use only
        if(pos >= tree.size() || pos == 0 || tree[pos] == 0) {
            return 0;
        }
        curSum = curSum + tree[pos];
        int runningSum = curSum - sum;
        printf("pos = %d, curEle = %d, curSum = %d, runningSum = %d\n",pos, tree[pos], curSum, runningSum);
        int count = 0;
        if(curSum == sum) {
            count++;
        }
        count += getCount(runningSum);

        changeCount(curSum, 1);
        count += _countPathWithSum(2*pos, sum, curSum);
        count += _countPathWithSum(2*pos+1, sum, curSum);
        changeCount(curSum, -1);

        return count;
    }

    int countPathWithSum(int sum) {
        counts.clear();
        return _countPathWithSum(1, sum, 0);
    }

    void printCounts() {
        for(auto it=counts.begin(); it!=counts.end();it++) {
            printf("%d ==> %d\n",it->first, it->second);
        }
    }
};

int main() {
    binaryTree bt;
    bt.insertNode(10);
    bt.insertNode(5);
    bt.insertNode(-3);
    bt.insertNode(3);
    bt.insertNode(1);
    bt.insertNode(0);
    bt.insertNode(11);
    bt.insertNode(3);
    bt.insertNode(-2);
    bt.insertNode(0);
    bt.insertNode(2);
    printf("%d\n", bt.countPathWithSum(6));
    bt.printCounts();
    return 0;
}