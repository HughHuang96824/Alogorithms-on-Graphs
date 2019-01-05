#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::stack;

struct Vertex {
    int key;
    bool visited;
    int pre, post;
    Vertex(): visited(false), pre(-1), post(-1) {}
    Vertex(int k): key(k), visited(false), pre(-1), post(-1) {}
};

stack<Vertex*>& dfs(vector<vector<Vertex*>>& adj, Vertex& v, int& time, stack<Vertex*>& reorder) {
    v.visited = true;
    v.pre = time++;
    
    for (int i = 0; i < adj[v.key].size(); i++) {
        if (!(adj[v.key][i]->visited))
            dfs(adj, *(adj[v.key][i]), time, reorder);
    }
    v.post = time++;
    reorder.push(&v);
    return reorder;
}

void explore(vector<vector<Vertex*>>& adj, Vertex& v) {
    v.visited = false;
    for (int i = 0; i < adj[v.key].size(); i++) {
        if (adj[v.key][i]->visited)
            explore(adj, *adj[v.key][i]);
    }
}


int number_of_strongly_connected_components
(vector<Vertex>& vertices, vector<vector<Vertex*>>& adj, vector<vector<Vertex*>>& reverse) {
    int result = 0;
    int time = 0;
    stack<Vertex*> reorder;
    for (int i = 0; i < vertices.size(); i++) {
        if (!(vertices[i].visited))
            reorder = dfs(reverse, vertices[i], time, reorder);
    }

    while (reorder.size() > 0) {
        if (reorder.top()->visited) {
            explore(adj, *reorder.top());
            for (int j = 0; j < adj.size(); j++) {
                adj[j].erase(std::remove_if(
                                       adj[j].begin(), adj[j].end(),
                                       [](Vertex*& x) {
                                           return (x->visited == false);
                                       }), adj[j].end());
            }
            result++;
        }
        reorder.pop();
    }

  return result;
}

int main() {
    //std::cout << "enter: \n";
    size_t n, m;
    std::cin >> n >> m;
    vector<Vertex> vertices(n);
    for (int i = 0; i < n; i++)
        vertices[i] = Vertex(i);
    
    vector<vector<Vertex*>> reverse(n, vector<Vertex*>());
    vector<vector<Vertex*>> adj(n, vector<Vertex*>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        reverse[y - 1].push_back(&(vertices[x-1]));
        adj[x - 1].push_back(&(vertices[y-1]));
  }
  std::cout << number_of_strongly_connected_components(vertices, adj, reverse);
}
