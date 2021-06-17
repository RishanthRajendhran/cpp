//c++11
#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<string>
#include<vector>
#include<math.h>
#include<string>
#include<stack>
using namespace std;

class graph {
    map< int, vector<int> > nodes;
    int numNodes;
    public:
    graph(int num) {
        numNodes = num;
    }

    void insertEdge(int node, int neigh) {
        map<int, vector<int> >::iterator it = nodes.find(node);
        if(it == nodes.end()) {
            nodes.insert(make_pair(node, vector<int>{neigh}));
        } else {
            it->second.push_back(neigh);
        }
    }

    void addNewEdge(pair<int, int> edge) {
        insertEdge(edge.first, edge.second);
        // insertEdge(edge.second, edge.first);     //Only for undirected graphs
    }

    void buildGraph(vector< pair<int, int> > edges) {
        for(int i=0; i<edges.size(); i++) {
            addNewEdge(edges[i]);
        }
    }

    void printGraph() {
        for(auto it = nodes.begin(); it!=nodes.end(); it++) {
            printf("Node %c\n",97 + it->first);
            printf("\tNeighbours: ");
            for(int i=0;i<it->second.size();i++) {
                printf("%c ",97 + it->second[i]);
            }
            printf("\n");
        }
    }

    void depthFirstSearch(int node, vector<int> & visited, stack<int> & st) {
        if(visited[node]) {
            return;
        }
        visited[node] = 1;
        map<int, vector<int> >::iterator it = nodes.find(node);
        if(it != nodes.end()) {
            for(int i=0;i<it->second.size();i++) {
                depthFirstSearch(it->second[i], visited, st);
            }
        }
        st.push(node);
    }

    int findUnvisited(vector<int> visited) {
        int node = -1;
        for(int i=0;i<visited.size();i++) {
            if(visited[i] == 0) {
                return i;
            }
        }
        return node;
    }

    pair<bool, vector<int> > shortestPath(int node, int dest, vector<int> & visited, vector<int> & path) {
        if(node == dest) {
            return make_pair(true, path);
        }

        if(visited[node]) {
            return make_pair(false, path);
        }

        printf("Visiting %c\n",97+node);
        visited[node] = 1;
        map<int, vector<int> >::iterator it = nodes.find(node);
        if(it == nodes.end()) { 
            return make_pair(false, path);
        }

        for(int i=0;i<it->second.size();i++) {
            path.push_back(it->second[i]);
            pair<bool, vector<int> > res = shortestPath(it->second[i], dest, visited, path);
            if(res.first) {
                return res;
            }
            path.pop_back();
        }
        return make_pair(false, path);
    }

    void topologicalSort() {
        vector<int> visited(numNodes,0);
        stack<int> st;
        int node = findUnvisited(visited);
        while(node != -1) {
            depthFirstSearch(node, visited, st);
            node = findUnvisited(visited);
        }
        while(st.empty() == false) {
            printf("%c ",97+st.top());
            st.pop();
        }
        printf("\n");
    }

    void shortestPath(int start, int stop) {
        vector<int> visited(numNodes,0);
        vector<int> path{start};
        pair<bool, vector<int> > res = shortestPath(start, stop, visited, path);
        if(res.first) {
            printf("Path found between %c and %c: ",97+start, 97+stop);
            for(int i=0;i<path.size();i++) {
                printf("%c",97+path[i]);
                if(i!=path.size()-1) {
                    printf("->");
                }
            }
            printf("\n");
        } else {
            printf("No path found between %c and %c\n",97+start, 97+stop);
        }
    }
};

int main() {
    graph g(6);
    vector< pair<int, int> > edges{make_pair(0, 4), make_pair(1, 0), make_pair(1, 4), make_pair(1, 7), make_pair(2, 0), make_pair(3, 6), make_pair(5, 0), make_pair(5, 1), make_pair(5, 2) };
    g.buildGraph(edges);
    g.printGraph();
    g.topologicalSort();
    g.shortestPath(5, 6);
    return 0;
}