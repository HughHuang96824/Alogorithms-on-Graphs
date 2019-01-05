#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;

struct Vertex {
    int processed;
    int distance;
    int key;
    vector<Vertex*> adj;
    vector<int> separation;
    Vertex* prev;
    Vertex() {}
    Vertex(int k): key(k), distance(std::numeric_limits<int>::max()), prev(NULL), processed(0) {}
};

int negative_cycle(vector<Vertex>& vertices) {
    bool relaxed = false;
    int processed = 1;
    for (int k = 0; k < vertices.size(); k++) {
        relaxed = false;
        queue<Vertex*> q;
        for (int j = 0; j < vertices.size(); j++) {
            if (vertices[j].processed != processed) {
                vertices[j].processed = processed;
                if (vertices[j].distance == std::numeric_limits<int>::max())
                    vertices[j].distance = 0;
                q.push(&vertices[j]);
                while (q.size()) {
                    for (int i = 0; i < q.front()->adj.size(); i++)
                        if (q.front()->adj[i]->distance > q.front()->distance + q.front()->separation[i]) {
                            q.front()->adj[i]->distance = q.front()->distance + q.front()->separation[i];
                            relaxed = true;
                            
                            if (q.front()->adj[i]->processed != q.front()->processed)
                                q.push(q.front()->adj[i]);
                            q.front()->adj[i]->processed = processed;
                        }
                    q.pop();
                }
            }
        }
        if (!relaxed)
            return 0;
        processed = -processed;
    }
    return 1;
}

int main() {
    std::cout << "enter: \n";
    int n, m;
    std::cin >> n >> m;
    vector<Vertex> vertices(n);
    
    for (int i = 0; i < n; i++)
        vertices[i] = Vertex(i);
    
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        vertices[x - 1].adj.push_back(&vertices[y - 1]);
        vertices[x - 1].separation.push_back(w);
    }
    std::cout << negative_cycle(vertices);
}
