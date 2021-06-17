#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<string>
#include<vector>
#include<stack>
#include<climits>
using namespace std;

class Stack {
    stack<int> s;
    stack<int> min;
    public:
    void insert(int d) {
        if(min.empty()) {
            min.push(d);
        } else {
            if(min.top() > d) {
                min.push(d);
            }
        }
        s.push(d);
    }
    void del() {
        if(s.empty()) {
            return;
        }
        int toDel = s.top();
        s.pop();
        if(min.top() == toDel) {
            min.pop();
        }
    }
    int getMin() {
        return (min.empty())?INT_MIN:min.top();
    }

    void printMin() {
        if(s.empty()) {
            return;
        }
        printf("Current Top: %d, Current Min: %d\n",s.top(), min.top());    
    }
};

int main() {
    Stack st;
    st.insert(5);
    st.printMin();
    st.insert(6);
    st.printMin();
    st.insert(13);
    st.printMin();
    st.insert(7);
    st.printMin();
    st.insert(35);
    st.printMin();
    st.insert(62);
    st.printMin();
    st.insert(-3);
    st.printMin();
    st.insert(21);
    st.printMin();
    st.del();
    st.printMin();
    st.del();
    st.printMin();
    st.del();
    st.printMin();
    st.del();
    st.printMin();
    st.del();
    st.printMin();
    st.del();
    return 0;
}