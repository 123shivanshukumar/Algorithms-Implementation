/*
    all algos -- adjacency structure 
*/
typedef int elt; // can change to long long int later 
#include<vector>
#include<iostream>
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


