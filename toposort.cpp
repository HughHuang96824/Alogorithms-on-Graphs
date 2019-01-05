#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;

struct Vertex {
    int key;
    bool visited;
    int label;
    Vertex(): visited(false), label(0) {}
    Vertex(int k): key(k), visited(false), label(0) {}
};

// Depth first search
void dfs(const vector<vector<Vertex*>>& adj, vector<int>::iterator& iter, Vertex& v, const int& number) {
    v.visited = true;
    v.label = number;
    for (int i = 0; i < adj[v.key].size(); i++) {
        if (!(adj[v.key][i]->visited))
            dfs(adj, iter, *adj[v.key][i], number);
    }
    *iter++ = v.key;
}     

vector<int> toposort(vector<Vertex>& vertices, const vector<vector<Vertex*>>& adj) {
    vector<int> order(vertices.size());
    vector<int>::iterator iter = order.begin();
    int num = 0;
    bool cycle = false;
    for (int i = 0; i < vertices.size(); i++) {
        if ((vertices[i].label) == 0) {
            num++;
            dfs(adj, iter, vertices[i], num);
            if (cycle) break;
        }
    }
    return order;
}

int main() {
    //std::cout << "enter: \n";
    size_t n, m;
    std::cin >> n >> m;
    vector<Vertex> vertices(n);
    for (int i = 0; i < n; i++)
        vertices[i] = Vertex(i);
    
    vector<vector<Vertex*>> adj(n, vector<Vertex*>());
    
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(&(vertices[y-1]));
    }
    vector<int> order = toposort(vertices, adj);
    for (long i = order.size() - 1; i >= 0; i--) {
        std::cout << order[i] + 1 << " ";
    }
}
