#include<stdio.h>
#include<stdlib.h>
#include<stack>
#include<vector>
using namespace std;

struct node {
    int data;
    int height;
    node* left;
    node* right;
};
class AVLtree {
    node* root;
    public:
    AVLtree() {
        root = NULL;
    }

    node* newNode(int data) {
        node* n = new node;
        n->data = data;
        n->height = 1;
        n->left = n->right = NULL;
    }

    void insert(node* curNode, int data) {
        if(curNode == NULL) {
            return newNode(data);
        }
        if(data < curNode->data) {
            curNode->left = insert(curNode->left, data);
        } else if(data < curNode->data) {
            curNode->right = insert(curNode->right, data);
        } else {
            return curNode;
        }

        curNode->height = 1 + max(curNode->left, curNode->right);
        int balance = (findHeight(curNode->left), findHeight(curNode->right));
        if(balance > 1 && data < curNode->left->data) //Left-left
        {
            return rightRotate(curNode);
        } 
        if(balance > 1 && data > curNode->left->data) //Left-right
        {   
            curNode->left = leftRotate(curNode);
            return rightRotate(curNode);
        }
        if(balance < -1 && data > curNode->right->data) {   //Right-right
            return leftRotate(curNode);
        }
        if(balance < -1 && data < curNode->right->data) {   //Right-left
            curNode->right = rightRotate(curNode);
            return leftRotate(curNode);
        }
        return curNode;
    }

    node* rightRotate(node* curNode) {
        node* x = curNode->left;
        node* T3 = x->right;

        x->right = curNode;
        curNode->left = T3;

        curNode->height = 1 + max(findHeight(curNode->left), findHeight(curNode->right));
        x->height = 1 + max(findHeight(x->left), findHeight(x->right));

        return x;
    }

    node* leftRotate(node* curNode) {   //usual textbook notations
        node* y = curNode->right;
        node* T2 = curNode->left;

        y->left = curNode;
        curNode->right = T2;

        curNode->height = 1 + max(findHeight(curNode->left), findHeight(curNode->right));
        y->height = 1 + max(findHeight(y->left), findHeight(y->right));

        return y;
    }

    int findHeight(node* cur) {
        return (cur==NULL)?0:cur->height;
    }
};