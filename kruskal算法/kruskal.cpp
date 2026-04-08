#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge {
    int u, v, weight;
};

bool compare(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

class UnionFind {
public:
    vector<int> parent, rank;
    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return false;
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

int main() {
    int n = 5;
    vector<Edge> edges = {
        {0, 1, 2},
        {0, 2, 3},
        {1, 2, 1},
        {1, 3, 4},
        {2, 3, 5},
        {3, 4, 6}
    };

    sort(edges.begin(), edges.end(), compare);

    UnionFind uf(n);
    vector<Edge> mst;
    int totalWeight = 0;

    for (auto& edge : edges) {
        if (uf.unite(edge.u, edge.v)) {
            mst.push_back(edge);
            totalWeight += edge.weight;
            cout << "Edge: " << edge.u << " - " << edge.v << ", Weight: " << edge.weight << endl;
        }
    }

    cout << "Total weight of MST: " << totalWeight << endl;

    return 0;
}