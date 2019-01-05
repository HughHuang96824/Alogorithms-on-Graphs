#include <iostream>
#include <vector>

using std::vector;

struct Vertex {
    int key;
    bool visited;
    int label;
    int pre, post;
    Vertex(): visited(false), label(0), pre(-1), post(-1) {}
    Vertex(int k): key(k), visited(false), label(0), pre(-1), post(-1) {}
};

bool explore(vector<vector<Vertex*> > &adj, Vertex& v, const int& number, int& time) {
    bool cycle = false;
    v.visited = true;
    v.label = number;
    v.pre = time++;
    
    for (int i = 0; i < adj[v.key].size(); i++) {
        if (cycle) break;
        
        if (adj[v.key][i]->visited && adj[v.key][i]->post == -1) return true;
        else cycle = explore(adj, *(adj[v.key][i]), number, time);
    }
    v.post = time++;
    
    return cycle;
}

int acyclic(vector<Vertex>& vertices, vector<vector<Vertex*>> &adj) {
    int time = 0;
    int num = 0;
    bool cycle = false;
    for (int i = 0; i < vertices.size(); i++) {
        if ((vertices[i].label) == 0) {
            num++;
            cycle = explore(adj, vertices[i], num, time);
            if (cycle) break;
        }
    }
  return cycle;
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

    std::cout << acyclic(vertices, adj);
}
