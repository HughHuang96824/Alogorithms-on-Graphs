#include <iostream>
#include <vector>

using std::vector;

struct Vertex {
    int key;
    bool visited;
    int label;
    Vertex(): visited(false), label(0) {};
    Vertex(int k): key(k), visited(false), label(0) {};
};

void explore(vector<vector<Vertex*>>& adj, Vertex& start, const int& number) {
    start.visited = true;
    start.label = number;
    for (int i = 0; i < adj[start.key].size(); i++) {
        if (!(adj[start.key][i]->visited))
            explore(adj, *adj[start.key][i], number);
    }
}

int number_of_components(vector<Vertex>& vertices, vector<vector<Vertex*>>& adj) {
    int res = 0;
    for (int i = 0; i < vertices.size(); i++) {
        if ((vertices[i].label) == 0) {
            res++;
            explore(adj, vertices[i], res);
        }
    }
    return res;
}

int main() {
    //std::cout << "enter: " << std::endl;
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<Vertex*>> adj(n, vector<Vertex*>());
    vector<Vertex> vertices(n);
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i] = Vertex(i);
    }
    
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x-1].push_back(&vertices[y-1]);
        adj[y-1].push_back(&vertices[x-1]);
    }

    std::cout << number_of_components(vertices, adj);
}
