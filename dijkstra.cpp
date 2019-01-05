#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::priority_queue;

struct Vertex {
    bool processed;
    int distance;
    int key;
    vector<Vertex*> adj;
    vector<int> separation;
    Vertex* prev;
    Vertex() {}
    Vertex(int k): key(k), distance(std::numeric_limits<int>::max()), prev(NULL), processed(false) {}
    friend bool operator < (const Vertex& a, const Vertex& b) {
        return a.distance < b.distance;
    }
};

struct DistCompare
{
    bool operator()(const Vertex* a, const Vertex* b)
    {
        return a->distance > b->distance;
    }
};

int distance(vector<Vertex>& vertices, Vertex& s, Vertex& t) {
    priority_queue<Vertex*, vector<Vertex*>, DistCompare> sorted;
    
    sorted.push(&s);
    
    while (sorted.size()) {
        Vertex* u = sorted.top();
        sorted.pop();
        
        if (u->prev == NULL || u == &t) break;
        
        if (!(u->processed)) {
            u->processed = true;
            for (int i = 0; i < u->adj.size(); i++) {
                if (u->adj[i]->distance > u->distance + u->separation[i]) {
                    u->adj[i]->distance = u->distance + u->separation[i];
                    u->adj[i]->prev = u;
                   
                    if (!u->adj[i]->processed)
                        sorted.push(u->adj[i]);
                }
            }
        }
    }
    if (t.prev == NULL) return -1;
    else return t.distance;
    
}

int main() {
    //std::cout << "enter: " << std::endl;
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
    
    int s, t;
    std::cin >> s >> t;
    s--; t--;
    vertices[s].distance = 0;
    vertices[s].prev = &vertices[s];
    std::cout << distance(vertices, vertices[s], vertices[t]);
}
