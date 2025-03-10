/*
    all algos -- adjacency list representation
*/
 // can change to custom types
#include<vector>
#include<iostream>
typedef int elt;

class Graph{
    std::vector<std::vector<elt>>adj;
    public:
    friend std::istream& operator>>(std::istream&,Graph&);
    friend std::ostream& operator<<(std::ostream&,Graph&);

    void bfs(std::vector<int>&);
    bool isBipartite();
    void dfs(std::vector<int>&);
    std::vector<int>& topo_sort();
    bool isCyclic_undir();
    bool isCyclic_dir();
    void print(std::vector<int>&);

    // s;
    // kosaraju, dijkstra, bellman ford, floyd warshall, more algos in clrs 
};


