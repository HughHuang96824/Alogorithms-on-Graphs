#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <cmath>

using std::vector;
using std::priority_queue;

struct Edge;

struct Vertex {
    int x;
    int y;
    int rank;
    Vertex* parent;
    Vertex() {}
    Vertex(int x_, int y_): x(x_), y(y_), parent(NULL), rank(1) {}
};

struct Edge {
    Vertex* one;
    Vertex* two;
    double distance;
    Edge() {}
    Edge(Vertex& a, Vertex& b): one(&a), two(&b), distance(sqrt(pow((a.x-b.x), 2) + pow((a.y-b.y), 2))){}
    friend bool operator < (const Edge& a, const Edge& b) {
        return a.distance < b.distance;
    }
};

struct DistCompare
{
    bool operator()(const Edge& a, const Edge& b)
    {
        return a.distance > b.distance;
    }
};

vector<Edge> CreateEdge(vector<Vertex>& vertices) {
    vector<Edge> edges((pow(vertices.size(), 2) - vertices.size()) / 2);
    int n = 0;
    for (int i = 0; i < vertices.size(); i++) {
        for (int j = i + 1; j < vertices.size(); j++) {
            edges[n] = Edge(vertices[i], vertices[j]);
            n++;
        }
    }
    return edges;
}

Vertex* Find(Vertex& v) {
    if (v.parent == NULL)
        return &v;
    v.parent = Find(*v.parent);
    return v.parent;
}

double minimum_distance(vector<Vertex>& vertices) {
    double result = 0.;
    vector<Edge> edges = CreateEdge(vertices);
    priority_queue<Edge, vector<Edge>, DistCompare> sorted;

    for (int i = 0; i < edges.size(); i++)
        sorted.push(edges[i]);
    
    int count = 0;
    while (count < vertices.size() - 1) {
        Vertex* root_1 = Find(*sorted.top().one);
        Vertex* root_2 = Find(*sorted.top().two);
        if (root_1 != root_2) {
            result += sorted.top().distance;
            if (root_1->rank > root_2->rank)
                root_2->parent = root_1;
            else {
                root_1->parent = root_2;
                if (root_1->rank == root_2->rank)
                    root_2->rank += 1;
            }
            
            count++;
        }
        sorted.pop();
    }
    return result;
} 

int main() {
    //std::cout << "enter: " << std::endl;
    size_t n;
    std::cin >> n;
    vector<Vertex> vertices(n);
    
    
    int x, y;
    for (size_t i = 0; i < n; i++) {
        std::cin >> x >> y;
        vertices[i] = Vertex(x, y);
    }
    std::cout << std::setprecision(10) << minimum_distance(vertices) << std::endl;
}
