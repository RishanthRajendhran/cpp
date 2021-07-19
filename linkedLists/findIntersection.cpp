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

    node* loopDetection() {
        if(root == NULL) {
            return NULL;
        }
        node* slow = root;
        node* fast = root;
        while(slow && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) {  //Loop exists
                slow = root;
                while(slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
        return NULL;
    }
};

node* findIntersection(node* l1, node* l2) {
    int s1, s2;
    node* cur = l1;
    while(cur) {
        cur = cur->next;
        s1++;
    }
    cur = l2;
    while(cur) {
        cur = cur->next;
        s2++;
    }
    if(s1 >s2) {
        int k = s1 - s2;
        cur = l1;
        while(k) {
            cur = cur->next;
            k--;
        }   
        l1 = cur;
    } else if(s2 > s2) {
        int k = s2 - s1;
        cur = l2;
        while(k) {
            cur = cur->next;
            k--;
        }
        l2 = cur;
    }
    while(l1 && l2 && l1 != l2) {
        l1 = l1->next;
        l2 = l2->next;
    }
    return l1;
}

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