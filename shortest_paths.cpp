#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::priority_queue;

struct Vertex {
    int processed;
    long long distance;
    int key;
    vector<Vertex*> adj;
    vector<int> separation;
    Vertex* prev;
    Vertex() {}
    Vertex(int k): key(k), distance(std::numeric_limits<long long>::max()), prev(NULL), processed(0) {}
};


queue<Vertex*> negative_cycle(vector<Vertex>& vertices, Vertex*& s) {
    queue<Vertex*> cycle;
    s->distance = 0;
    int processed = 1;
    for (int k = 0; k < vertices.size(); k++) {
        s->processed = processed;
        queue<Vertex*> q;
        q.push(s);
        int change = 0;
        while (q.size()) {
            for (int i = 0; i < q.front()->adj.size(); i++) {
                
                if (q.front()->adj[i]->processed != processed) {
                    q.push(q.front()->adj[i]);
                    q.front()->adj[i]->processed = processed;
                }
                
                if (q.front()->adj[i]->distance > q.front()->distance + q.front()->separation[i]) {
                    q.front()->adj[i]->distance = q.front()->distance + q.front()->separation[i];
                    change++;
                    
                    if (k == vertices.size() - 1)
                        cycle.push(q.front()->adj[i]);
                }
            }
            q.pop();
        }
        if (!change) break;
        processed = -processed;
    }
    return cycle;
}


void explore(vector<Vertex>& vertices, Vertex*& start) {
    
    start->processed = 2;
    for (int i = 0; i < start->adj.size(); i++)
        if (start->adj[i]->processed != 2)
            explore(vertices, start->adj[i]);
}


void shortest_paths(vector<Vertex>& vertices, Vertex*& s, vector<int>& reachable, vector<int>& shortest) {
    queue<Vertex*> cycle = negative_cycle(vertices, s);
    
    explore(vertices, s);
    for (int i = 0; i < vertices.size(); i++)
        if (vertices[i].processed == 2)
            reachable[i] = 1;
    
    while (cycle.size()) {
        cycle.front()->processed = 0;
        shortest[cycle.front()->key] = 0;
        for (int i = 0; i < cycle.front()->adj.size(); i++) {
            if (cycle.front()->adj[i]->processed != 0) {
                cycle.front()->adj[i]->processed = 0;
                shortest[cycle.front()->adj[i]->key] = 0;
                cycle.push(cycle.front()->adj[i]);
            }
        }
        cycle.pop();
    }
}



int main() {
    //std::cout << "enter: \n";
    int n, m, s;
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
    std::cin >> s;
    s--;
    Vertex* v = &vertices[s];
    vector<long long> distance(n, std::numeric_limits<long long>::max());
    vector<int> reachable(n, 0);
    vector<int> shortest(n, 1);
    shortest_paths(vertices, v, reachable, shortest);
    for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
        std::cout << "*\n";
    } else if (!shortest[i]) {
        std::cout << "-\n";
    } else {
        std::cout << vertices[i].distance << "\n";
    }
  }
}
