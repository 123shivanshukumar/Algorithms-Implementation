/*
    all algos -- adjacency list representation
*/

#include<vector>
#include<iostream>
typedef int elt;  // can change to custom types

class Graph{
    std::vector<std::vector<elt>>adj;
    public:
    friend std::istream& operator>>(std::istream&,Graph&);
    friend std::ostream& operator<<(std::ostream&,Graph&);

    std::vector<int> bfs();
    bool isBipartite();
    std::vector<int> dfs();
    std::vector<int> topo_sort();
    bool isCyclic_undir();
    bool isCyclic_dir();
    void print(std::vector<int>&);

    // s;
    // kosaraju, dijkstra, bellman ford, floyd warshall, more algos in clrs 
};
std::vector<int> bfs(){
    int n = adj.size();
    std::vector<int> traversal;
    std::vector<bool> visited(n,false);
    std::queue<int> bfs;
    
    bfs.push(0);
    visited[0] = true;
    
    int v;
    while(!bfs.empty()){
        v = bfs.front();
        bfs.pop();
        traversal.push_back(v);
        for(auto u : adj[v]){
            if(!visited[u]){
                bfs.push(u);
                visited[u] = true;
            }
        }
    }
    return traversal;
}


