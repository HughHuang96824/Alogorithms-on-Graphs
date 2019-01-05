#include <iostream>
#include <vector>

using std::vector;

struct Vertex {
    int key;
    bool visited;
    Vertex() {};
    Vertex(int k): key(k), visited(false) {};
};

bool explore(vector<vector<Vertex>>& adj, Vertex& start, const int& target) {
    bool connected = false;
    
    if (start.key == target)
        return true;
    else {
        start.visited = true;
        for (int i = 0; i < adj[start.key].size(); i++) {
            if (adj[start.key][i].visited == false) {
                if (connected == true) break;
                else connected = explore(adj, adj[start.key][i], target);
            }
        }
    }
    return connected;
}

bool reach(vector<vector<Vertex> > &adj, const int& x, const int& y) {
    if (adj[x].size() == 0)
        return false;
  return explore(adj, adj[x][0], y);
}


int main() {
    //std::cout << "enter: \n";
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<Vertex> > adj(n, vector<Vertex>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        Vertex first(x - 1);
        Vertex second(y - 1);
        adj[first.key].push_back(second);
        adj[second.key].push_back(first);
    }
    int x, y;
    std::cin >> x >> y;
    std::cout << reach(adj, x - 1, y - 1);
}
