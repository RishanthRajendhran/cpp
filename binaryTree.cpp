#include<stdio.h>
#include<stdlib.h>
#include<stack>
#include<vector>
using namespace std;

struct node {
    int data;
    node* left;
    node* right;
};
class binarySearchTree {
    node* root;
    public:
    binarySearchTree() {
        root = NULL;
    }

    void insertnode(int data) {
        node* newnode = new node;
        newnode->data = data;
        newnode->left = NULL;
        newnode->right = NULL;
        if(root == NULL) {
            root = newnode;
            return;
        }
        node* temp = root;
        node* prev = root;
        while(temp) {
            if(data < temp->data) {
                prev = temp;
                temp = temp->left;
            } else if(data > temp->data) {
                prev = temp;
                temp = temp->right;
            } else {
                return; //No duplicates
            }
        }
        if(data <= prev->data) {
            prev->left = newnode;
        } else {
            prev->right = newnode;
        }
    }

    void insertnodeRecursive(int data, node* parent) {
        if(parent == NULL) {
            node* newnode = new node;
            newnode->data = data;
            newnode->left = newnode->right = NULL;
            root = newnode;
            return;
        }
        if(parent->data >= data) {
            if(parent->left == NULL) {
                node* newnode = new node;
                newnode->data = data;
                newnode->left = newnode->right = NULL;
                parent->left = newnode;
            } else {
                insertnodeRecursive(data, parent->left);
            }
        } else if(parent->data < data) {
            if(parent->right == NULL) {
                node* newnode = new node;
                newnode->data = data;
                newnode->left = newnode->right = NULL;
                parent->right = newnode;
            } else {
                insertnodeRecursive(data, parent->right);
            }
        } else {    //No duplicates
            return;
        }
    }

    void preorder(node* root) {
        if(root == NULL) {
            return;
        }
        stack<node*> st;
        st.push(root);
        node* lastnode = root;
        node* curnode = root;
        while(!st.empty()) {
            curnode = st.top();
            if((lastnode && lastnode == curnode->right) || (curnode->left == NULL && curnode->right == NULL)) {
                printf("%d ",curnode->data);
                st.pop();
            } else {
                if(curnode->right) st.push(curnode->right);
                if(curnode->left) st.push(curnode->left);
            }
            lastnode = curnode;
        }
    }

    void preorderRecursive(node* root) {
        if(root == NULL) {
            return;
        }
        preorderRecursive(root->left);
        preorderRecursive(root->right);
        printf("%d ",root->data);
    }

    void printPreorder() {
        preorder(root);
    }

    void postorder(node* root) {
        if(root == NULL) {
            return;
        }
        stack<node*> st;
        st.push(root);
        node* lastnode = root;
        node* curnode = root;
        while(!st.empty()) {
            curnode = st.top();
            printf("%d ", curnode->data);
            st.pop();
            if(curnode->right) st.push(curnode->right);
            if(curnode->left) st.push(curnode->left);
        }
    }

    void postorderRecursive(node* root) {
        if(root == NULL) {
            return;
        }
        printf("%d ",root->data);
        postorderRecursive(root->left);
        postorderRecursive(root->right);
    }

    void printPostorder() {
        postorder(root);
    }

    void inorder(node* root) {
        if(root == NULL) {
            return;
        }
        stack<node*> st;
        st.push(root);
        node* curnode = root;
        node* lastnode = root;
        while(!st.empty()) {
            curnode = st.top();
            st.pop();
            if((curnode->left == lastnode) || (!st.empty() && curnode->right &&  curnode->right == st.top()) || (curnode->left == NULL && curnode->right == NULL)) {
                printf("%d ", curnode->data);
            } else {
                if(curnode->right) st.push(curnode->right);
                if(curnode->left) {
                    st.push(curnode);
                    st.push(curnode->left);
                } else {
                    printf("%d ", curnode->data);
                }
            }
            lastnode = curnode;
        }
    }

    void inorderRecursive(node* root) {
        if(root == NULL) {
            return;
        }
        inorderRecursive(root->left);
        printf("%d ",root->data);
        inorderRecursive(root->right);
    }

    void printInorder() {
        inorder(root);
    }

    void deletenode(int data) {
        if(root == NULL) {
            return;
        }
        if(root->data == data) {

        }
        node* prev = root;
        node* cur = root;
        while(cur) {
            if(cur->data == data) {
                if(cur->left == NULL && cur->right == NULL) {
                    if(prev->left == cur) {
                        prev->left = NULL;
                    } else if(prev->right == cur) {
                        prev->right = NULL;
                    }
                    if(cur == root) {
                        root = NULL;
                    }
                    delete cur;
                    break;
                } else if(cur->left == NULL || cur->right == NULL) {
                    if(cur->left) {
                        if(cur == root) {
                            root = cur->left;
                        } else {
                            if(prev->left == cur) {
                                prev->left = cur->left;
                            } else {
                                prev->right = cur->left;
                            }
                        }
                        delete cur;
                        break;
                    } else {
                        if(cur == root) {
                            root = cur->right;
                        } else {
                            if(prev->left == cur) {
                                prev->left = cur->right;
                            } else {
                                prev->right = cur->right;
                            }
                        }
                        delete cur;
                        break;
                    }
                } else {
                    node* leftmostOfRightChild = cur->right;
                    node* parent = cur;
                    while(leftmostOfRightChild->left) {
                        parent = leftmostOfRightChild;
                        leftmostOfRightChild = leftmostOfRightChild->left;
                    }
                    parent->left = leftmostOfRightChild->right;
                    cur->data = leftmostOfRightChild->data;
                    delete leftmostOfRightChild;
                    break;
                }
            } else if(cur->data < data) {
                prev = cur;
                cur = cur->right;
            } else {
                prev = cur;
                cur = cur->left;
            }
        }
    }

    vector< pair<int, node*> > updateHorizontalDist(node* root, int dist, vector< pair<int, vector<node*> > > horizontalDist) {
        if(root == NULL) {
            return horizontalDist;
        }
        int pos = -1;
        for(int i=0;i<horizontalDist.size();i++) {
            if(horizontalDist[i].first == dist) { 
                pos = i;
                break;
            }
        }
        if(pos != -1) {
            horizontalDist.push_back(make_pair(dist,{root}));
        } else {
            horizontalDist[pos].second.push_back(root);
        }
        horizontalDist = updateHorizontalDist(root->left, dist-1, horizontalDist);
        horizontalDist = updateHorizontalDist(root->right, dist+1, horizontalDist);
        return horizontalDist;
    }
    
    static bool compareDist(pair<int, node*> a, pair<int, node*> b) {
        return a.first <= b.first;
    }

    void topView() {
        vector< pair<int, node*> > horizontalDist;
        horizontalDist = updateHorizontalDist(root, 0, horizontalDist);
        std::sort(horizontalDist.begin(), horizontalDist.end(), compareDist);
        for(int i=0;i<horizontalDist.size();i++) {
            printf("%d %d\n",horizontalDist[i].first, horizontalDist[i].second->data);
        }
    }

};

int main() {
    binarySearchTree bst;
    bst.insertnode(13);
    bst.insertnode(3);
    bst.insertnode(19);
    bst.insertnode(15);
    bst.insertnode(17);
    bst.insertnode(23);
    bst.insertnode(1);
    bst.insertnode(6);
    bst.printPreorder();
    printf("\n");
    bst.printPostorder();
    printf("\n");
    bst.printInorder();
    printf("\n");
    bst.deletenode(6);
    bst.printInorder();
    printf("\n");
    bst.topView();
    return 0;
}