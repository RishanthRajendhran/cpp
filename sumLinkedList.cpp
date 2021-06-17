// { Driver Code Starts
// driver

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/* Linked list Node */
struct Node {
    int data;
    struct Node* next;
    Node(int x) {
        data = x;
        next = NULL;
    }
};

struct Node* buildList(int size)
{
    int val;
    cin>> val;
    
    Node* head = new Node(val);
    Node* tail = head;
    
    for(int i=0; i<size-1; i++)
    {
        cin>> val;
        tail->next = new Node(val);
        tail = tail->next;
    }
    
    return head;
}

void printList(Node* n)
{
    while(n)
    {
        cout<< n->data << " ";
        n = n->next;
    }
    cout<< endl;
}


 // } Driver Code Ends
/* node for linked list:

struct Node {
    int data;
    struct Node* next;
    Node(int x) {
        data = x;
        next = NULL;
    }
};

*/
#include<vector> 
class Solution
{
    public:
    pair<struct Node*, int> addNodes(struct Node* first, struct Node* second) {
        if(first == NULL || second == NULL) {
            return make_pair((Node*)NULL,0);
        }
        int sum = first->data + second->data;
        int carry = sum/10;
        sum = sum%10;
        pair<struct Node*, int> res = addNodes(first->next, second->next);
        int toAdd = res.second;
        if(toAdd != 0) {
            sum += toAdd;
            carry += sum/10;
            sum = sum%10;
        }
        Node* newNode = new Node(sum);
        newNode->next = res.first;
        return make_pair(newNode, carry);
    }
    //Function to add two numbers represented by linked list.
    struct Node* addTwoLists(struct Node* first, struct Node* second)
    {
        // code here
        int m = 0, n = 0;
        Node *f, *s, *pf = NULL, *ps = NULL;
        f = first;
        s = second;
        while(f) {
            m++;
            f = f->next;
        }
        while(s) {
            n++;
            s = s->next;
        }
        f = first;
        s = second;
        vector<Node* > prevFs;
        vector<Node* > prevSs;
        if(m>n) {
            int c = 0;
            while(c<(m-n)) {
                prevFs.push_back(first);
                pf = first;
                first = first->next;
                c++;
            }
        } else if(n>m) {
            int c = 0;
            while(c<(n-m)) {
                prevSs.push_back(second);
                ps = second;
                second = second->next;
                c++;
            }
        }
        pair<struct Node*, int> res = addNodes(first->next, second->next);
        int toAdd = res.second;
        int sum, carry;
        sum = first->data + second->data;
        carry = sum/10;
        sum = sum%10;
        if(m != n) {
            sum += toAdd;
            carry += sum/10;
            sum = sum%10;
            if(m > n) {
                Node *newNode1 = new Node(sum);
                newNode1->next = res.first;
                pf->next = newNode1;
                int pos = prevFs.size()-1;
                while(pos>=0 && carry) {
                    pf = prevFs[pos--];
                    pf->data += carry;
                    carry = pf->data/10;
                    pf->data = pf->data % 10;
                }
                if(pos < 0 && carry) {
                    Node* newFirst = new Node(carry);
                    newFirst->next = f;
                    f = newFirst;
                }
                return f;
            } else if(m < n) {
                Node *newNode1 = new Node(sum);
                newNode1->next = res.first;
                ps->next = newNode1;
                int pos = prevSs.size()-1;
                while(pos>=0 && carry) {
                    ps = prevSs[pos--];
                    ps->data += carry;
                    carry = ps->data/10;
                    ps->data %= 10;
                }
                if(pos < 0 && carry) {
                    Node* newSecond = new Node(carry);
                    newSecond->next = s;
                    s = newSecond;
                }
                return s;
            } 
        } else {
            sum += toAdd;
            carry += sum/10;
            sum = sum % 10;
            if(carry) {
                Node *newNode1 = new Node(carry), *newNode2 = new Node(sum);
                newNode1->next = newNode2;
                newNode2->next = res.first;
                return newNode1;
            } else {
                Node* newNode = new Node(sum);
                newNode->next = res.first;
                return newNode;
            }
        }
    }
};


// { Driver Code Starts.

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n, m;
        
        cin>>n;
        Node* first = buildList(n);
        
        cin>>m;
        Node* second = buildList(m);
        Solution ob;
        Node* res = ob.addTwoLists(first,second);
        printList(res);
    }
    return 0;
}
  // } Driver Code Ends