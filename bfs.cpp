#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

struct Vertex {
    int distance;
    int key;
    Vertex() {};
    Vertex(int k): key(k), distance(-1) {}
};

//Breadth first search
void bfs(queue<Vertex*>& layer, vector<vector<Vertex*>>& adj) {
    while (layer.size()) {
        for (int i = 0; i < adj[layer.front()->key].size(); i++) {
            if (adj[layer.front()->key][i]->distance == -1) {
                adj[layer.front()->key][i]->distance = layer.front()->distance + 1;
                layer.push(adj[layer.front()->key][i]);
            }
        }
        layer.pop();
    }
}
    

int distance(vector<vector<Vertex*>>& adj, Vertex& s, Vertex& t) {
    queue<Vertex*> layer;
    layer.push(&s);
    s.distance = 0;
    bfs(layer, adj);
  return t.distance;
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
    
  int s, t;
  std::cin >> s >> t;
    s--;
    t--;
  std::cout << distance(adj, vertices[s], vertices[t]);
}
