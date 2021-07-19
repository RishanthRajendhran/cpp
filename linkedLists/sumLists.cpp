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

    int returnCarry(node* n1, node* n2) {   //The two lists should be of equal length
        if(n1 == NULL && n2 == NULL) {
            return 0;
        } 
        int carry = returnCarry(n1->next, n2->next);
        n1->data += n2->data + carry;
        carry = n1->data/10;
        n1->data %= 10;
        return carry;
    }

    int addCarry(node* n, int c, node* endNode) {
        if(n == endNode) {
            return c;
        }
        int carry = addCarry(n->next,c,endNode);
        n->data  +=  c;
        c = n->data/10;
        n->data %= 10;
        return c;
    }

    node* makeDupes(node* n, node* endNode) {
        if(n == endNode) {
            return NULL;
        }
        node* newNode = new node;
        newNode->data = n->data;
        newNode->next = makeDupes(n->next, endNode);
        return newNode;
    }

    void sumLists(node* l2) {
        node* l1 = root;
        int s1 = 0, s2 = 0;
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
            int carry = returnCarry(cur, l2);
            if(carry) {
                carry = addCarry(l1,carry,cur);
                if(carry) {
                    node* newNode = new node;
                    newNode->data = carry;
                    newNode->next = l1;
                    root = newNode;
                    return;
                }
                return;
            }
        } else if(s2 > s1) {
            int k = s2 - s1;
            cur = l2;
            while(k) {
                cur = cur->next;
                k--;
            }
            int carry = returnCarry(l1, cur);
            node* newRoot = makeDupes(l2,cur);
            node* temp = newRoot;
            while(temp->next) {
                temp = temp->next;
            }            
            temp->next = l1;
            if(carry) {
                carry = addCarry(newRoot,carry,l1);
                if(carry) {
                    node* newNode = new node;
                    newNode->data = carry;
                    newNode->next = newRoot;
                    root = newNode;
                    return;
                }
                root = newRoot;
                return;
            }
        } else {    //s1 == s2
            int carry = returnCarry(l1, l2);
            if(carry) {
                node* newNode = new node;
                newNode->data = carry;
                newNode->next = l1;
                root = newNode;
            }
            return;
        }
    }

    node* getRoot() {
        return root;
    }
};

int main() {
    LinkedList ll, ll2;
    // ll2.appendToTail(9);
    ll2.appendToTail(5);
    ll2.appendToTail(2);
    ll.appendToTail(9);
    ll.appendToTail(4);
    ll.appendToTail(9);
    ll.printList();
    ll2.printList();
    ll.sumLists(ll2.getRoot());
    ll.printList();
    ll2.printList();
    return 0;
}