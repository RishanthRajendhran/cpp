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
    return 0;
}