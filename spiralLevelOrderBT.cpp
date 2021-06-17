// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// Tree Node
struct Node
{
    int data;
    Node* left;
    Node* right;
};
// Utility function to create a new Tree Node
Node* newNode(int val)
{
    Node* temp = new Node;
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

vector<int> findSpiral(Node *root);

// Function to Build Tree
Node* buildTree(string str)
{
    // Corner Case
    if(str.length() == 0 || str[0] == 'N')
        return NULL;

    // Creating vector of strings from input
    // string after spliting by space
    vector<string> ip;

    istringstream iss(str);
    for(string str; iss >> str; )
        ip.push_back(str);

    // Create the root of the tree
    Node* root = newNode(stoi(ip[0]));

    // Push the root to the queue
    queue<Node*> queue;
    queue.push(root);

    // Starting from the second element
    int i = 1;
    while(!queue.empty() && i < ip.size()) {

        // Get and remove the front of the queue
        Node* currNode = queue.front();
        queue.pop();

        // Get the current node's value from the string
        string currVal = ip[i];

        // If the left child is not null
        if(currVal != "N") {

            // Create the left child for the current node
            currNode->left = newNode(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->left);
        }

        // For the right child
        i++;
        if(i >= ip.size())
            break;
        currVal = ip[i];

        // If the right child is not null
        if(currVal != "N") {

            // Create the right child for the current node
            currNode->right = newNode(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }

    return root;
}


int main() {
    int t;
    string  tc;
    getline(cin,tc);
    t=stoi(tc);
    while(t--)
    {
        string s;
        getline(cin,s);
        Node* root = buildTree(s);

        vector<int> vec = findSpiral(root);
        for(int x : vec)
        cout<<x<<" ";
        cout << endl;
    }
    return 0;
}


// } Driver Code Ends


/* A binary tree node has data, pointer to left child
   and a pointer to right child  
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
}; */
vector<Node*> getNextLevel(vector<Node*> curLevel) {
    vector<Node*> nextLevel;
    for(int i=0;i<curLevel.size();i++) {
        Node* x= curLevel[i];
        if(x && x->left) nextLevel.push_back(x->left);
        if(x && x->right) nextLevel.push_back(x->right);
    }
    return nextLevel;
}

//Function to return a list containing the level order traversal in spiral form.
vector<int> findSpiral(Node *root)
{
    if(root == NULL) {
        return vector<int>{};
    }
    map<int, bool> visited;
    vector<int> path{};
    path.push_back(root->data);
    vector<Node*> curLevel;
    curLevel.push_back(root);
    bool rev = false;
    do {
        vector<Node*> nextLevel = getNextLevel(curLevel);
        curLevel = nextLevel;
        if(rev) {
            reverse(nextLevel.begin(), nextLevel.end());
        }
        for(int i=0;i<nextLevel.size();i++) {
            path.push_back(nextLevel[i]->data);
        }
        rev = !rev;
    }while(curLevel.size());
    return path;
}
