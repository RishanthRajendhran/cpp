#include<stdio.h>
#include<stdlib.h>
#include <string>
#include<sstream>
#include<map>
#include<vector>
#include<math.h>
using namespace std;

struct node {
    int data;
    node* next;
};

class LinkedList {
    node* root;
    public:
    LinkedList() {
        root = NULL;
    }

    void appendToHead(int d) {
        node* newNode = new node;
        newNode->data = d;
        newNode->next = NULL;
        if(root==NULL) {
            root = newNode;
        } else {
            newNode->next = root;
            root = newNode;
        }
    }

    void appendToTail(int d) {
        node* newNode = new node;
        newNode->data = d;
        newNode->next = NULL;
        if(root==NULL) {
            root = newNode;
        } else {
            node* cur = root;
            while(cur->next) {
                cur = cur->next;
            }
            cur->next = newNode;
        }
    }

    void printList() {
        if(root == NULL) {
            return;
        }
        node* cur = root;
        while(cur) {
            printf("%d->",cur->data);
            cur = cur->next;
        }
        printf("\b\b  \n");
    }

    void removeDuplicates() {
        if(root == NULL) {
            return;
        }
        map<int, bool> seenNodes;
        node* cur = root;
        node* prev = NULL;
        while(cur) {
            auto it = seenNodes.find(cur->data);
            if(it == seenNodes.end()) {
                seenNodes.insert(make_pair(cur->data,true));
            } else {
                if(prev) {
                    prev->next = cur->next;
                } else {
                    root = cur->next;
                }
            }
            prev = cur;
            cur = cur->next;
        }
    }
    node* posOfNodeFromLast(node* cur, int &k) {
        if(cur == NULL) {
            k--;
            return NULL;
        }
        node* ret = posOfNodeFromLast(cur->next, k);
        if(k==0) {
            if(ret == NULL) {
                ret = cur;
            }
            return ret;
        } else {
            k--;
            return NULL;
        }

    }

    node* kthToLast(int k) {
        node* toRet = posOfNodeFromLast(root, k);
        if(toRet == NULL) {
            node* dummyNode = new node;
            dummyNode->data = INT_MIN;
            dummyNode->next = NULL;
            toRet = dummyNode;
        }
        return toRet;
    }

    node* kthToLastIterative(int k) {
        node* p1 = root;
        node* p2  = root;
        for(int i=0;i<k;i++) {
            if(p2==NULL) {
                node* dummyNode = new node;
                dummyNode->data = INT_MIN;
                dummyNode->next = NULL;
                return dummyNode;
            }
            p2 = p2->next;
        }
        while(p2!=NULL) {
            p1 = p1->next;
            p2 = p2->next;
        }
        return p1;
    }

    void deleteMiddleNode(node* toDel) {
        if(toDel->next) {
            toDel->data = toDel->next->data;
            toDel->next = toDel->next->next;
            delete toDel->next;
            return;
        } else {    //toDel cannot be the last node
            return;
        }
    }

    void partition(int d) {
        node* leftStart = NULL;
        node* leftEnd = NULL;
        node* rightStart = NULL;
        node* rightEnd = NULL;
        node* temp = root;
        while(temp) {
            if(temp->data < d) {
                if(leftStart == NULL) {
                    leftStart = temp;
                    leftEnd = root;
                } else {
                    leftEnd->next = temp;
                    leftEnd = temp;
                }
            } else {
                if(rightStart == NULL) {
                    rightStart = temp;
                    rightEnd = temp;
                } else {
                    rightEnd->next = temp;
                    rightEnd = temp;
                }
            }
            temp = temp->next;
        }
        if(leftEnd == NULL) {
            root = rightStart;
        } else {
            root =  leftStart;
            leftEnd->next = rightStart;
        }
        if(rightEnd) {
            rightEnd->next = NULL;
        } else  if(leftEnd && rightStart == NULL) {
            leftEnd->next  = NULL;
        }
        return;
    }
};

int main() {
    LinkedList ll;
    ll.appendToTail(1);
    ll.appendToTail(5);
    ll.appendToTail(2);
    ll.appendToTail(1);
    ll.appendToTail(13);
    ll.appendToTail(13);
    ll.appendToTail(7);
    ll.appendToTail(5);
    ll.printList();
    ll.removeDuplicates();
    ll.printList();
    ll.partition(13);
    ll.printList();
    return 0;
}