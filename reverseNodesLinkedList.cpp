#include<stdio.h>
#include<stdlib.h>
#include<vector>
using namespace std;

struct node {
    int data;
    node* next;
};

class linkedList {
    node* root;
    int numNodes;
    public:
    linkedList() {
        root = NULL;
    }

    void insert(node* cur, node* newNode) {
        if(cur->next == NULL) {
            cur->next = newNode;
            return;
        }
        insert(cur->next, newNode);
    }

    void insert(int d) {
        node* newNode = new node;
        newNode->data = d;
        newNode->next = NULL;
        numNodes++;
        if(root == NULL) {
            root = newNode;
            return;
        }
        insert(root, newNode);
    }

    void deleteNode(node* cur, node* prev, int d) {
        if(cur->data == d) {
            node* toDel = cur;
            prev->next = cur->next;
            delete toDel;
            return;
        }
        deleteNode(cur->next, cur, d);
    }

    void deleteNode(int d) {
        if(root == NULL) {
            return;
        }
        numNodes--;
        if(root->data == d) {
            node* toDel = root;
            root = root->next;
            delete toDel;
            return;
        }
        deleteNode(root->next, root, d);
    }

    pair<node*, node*> reverseList(node* cur, node* prev, node* next, int  count) {
        if(cur == NULL || count == 0) {
            return make_pair(prev, cur);
        }
        cur->next = prev;
        prev = cur;
        cur = next;
        if(cur!=NULL) {
            next = cur->next;
        }
        count--;
        return reverseList(cur, prev, next, count);
    }

    void reverseList(int k=-1) {
        if(k==-1) {
            k = numNodes;
        }
        node *start, *end, *prevStart = NULL;
        start = root;
        do {
            pair<node*, node*> res = reverseList(start, prevStart, start->next,k);
            if(prevStart)
                prevStart->next = res.first;
            start->next = res.second;
            if(start == root) {
                root = res.first;
            }
            prevStart = start;
            start = res.second;
        } while(start);
    }

    void printList() {
        if(root == NULL) {
            printf("List is empty!\n");
            return;
        }
        node* start = root;
        printf("Printing list: ");
        while(start) {
            printf("%d ",start->data);
            start = start->next;
        }
        printf("\n");
    }
};

int main() {
    linkedList ll;
    ll.insert(1);
    ll.insert(2);
    ll.insert(2);
    ll.insert(4);
    ll.insert(5);
    ll.insert(6);
    ll.insert(7);
    ll.insert(8);
    ll.reverseList(4);
    ll.printList();
    return 0;
}