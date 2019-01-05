#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

struct Vertex {
    bool visited;
    int key;
    int color;
    Vertex() {};
    Vertex(int k): key(k), visited(0), color(0) {}
};

//Breadth first search
bool bfs(queue<Vertex*>& layer, vector<vector<Vertex*>>& adj) {
    while (layer.size()) {
        for (int i = 0; i < adj[layer.front()->key].size(); i++) {
            if (!(adj[layer.front()->key][i]->visited)) {
                    adj[layer.front()->key][i]->visited = true;
                    adj[layer.front()->key][i]->color = -layer.front()->color;
                    layer.push(adj[layer.front()->key][i]);
            }
            else if (adj[layer.front()->key][i]->color == layer.front()->color)
                return false;
        }
    
        layer.pop();
    }
    return true;
}

int bipartite(vector<Vertex>& vertices, vector<vector<Vertex*>>& adj) {
    bool bipartite = true;
    queue<Vertex*> layer;
    for (int i = 0; i < vertices.size(); i++) {
        if (!vertices[i].visited) {
            vertices[i].color = 1;
            vertices[i].visited = true;
            layer.push(&vertices[0]);
            bipartite = bfs(layer, adj);
        }
        if (!bipartite)
            return bipartite;
    }
    return bipartite;
}


int main() {
    //std::cout << "enter: \n";
    int n, m;
    std::cin >> n >> m;
    vector<Vertex> vertices(n);
    for (int i = 0; i < n; i++)
        vertices[i] = Vertex(i);
    
    vector<vector<Vertex*>> adj(n, vector<Vertex*>());
    
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(&vertices[y - 1]);
        adj[y - 1].push_back(&vertices[x - 1]);
    }
    
    std::cout << bipartite(vertices, adj);
}
