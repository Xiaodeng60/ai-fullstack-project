#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max() / 2;

void printDistanceMatrix(const vector<vector<int>>& dist) {
    int n = dist.size();
    cout << "\nAll-pairs shortest distance matrix:" << endl;
    cout << "     ";
    for (int i = 0; i < n; ++i) cout << setw(5) << i;
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << setw(3) << i << "  ";
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] >= INF / 2) cout << setw(5) << "INF";
            else cout << setw(5) << dist[i][j];
        }
        cout << endl;
    }
}

// 迭代打印路径
void printPath(int i, int j, const vector<vector<int>>& next) {
    cout << i;
    while (next[i][j] != -1) {
        i = next[i][j];
        cout << " -> " << i;
    }
    // 当 next[i][j] == -1 时，i 已经等于 j，无需额外输出
}

void printAllPaths(const vector<vector<int>>& dist, const vector<vector<int>>& next) {
    int n = dist.size();
    cout << "\nAll-pairs shortest paths:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                cout << i << " -> " << j << " : self path (length 0)" << endl;
                continue;
            }
            if (dist[i][j] >= INF / 2) {
                cout << i << " -> " << j << " : unreachable" << endl;
            } else {
                cout << i << " -> " << j << " : ";
                printPath(i, j, next);
                cout << " (distance = " << dist[i][j] << ")" << endl;
            }
        }
        cout << endl;
    }
}

int main() {
    int n = 5;
    vector<vector<int>> graph(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) graph[i][i] = 0;

    auto addEdge = [&](int u, int v, int w) {
        graph[u][v] = w;
        graph[v][u] = w;
    };

    addEdge(0, 1, 3);
    addEdge(0, 2, 8);
    addEdge(0, 4, 4);
    addEdge(1, 3, 1);
    addEdge(1, 4, 7);
    addEdge(2, 1, 4);
    addEdge(3, 0, 2);
    addEdge(3, 2, 5);
    addEdge(4, 3, 6);

    cout << "Generated graph (undirected, non-negative weights):" << endl;
    printDistanceMatrix(graph);

    vector<vector<int>> dist = graph;
    vector<vector<int>> next(n, vector<int>(n, -1));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && dist[i][j] < INF / 2) {
                next[i][j] = j;
            }
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF / 2 && dist[k][j] < INF / 2 &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    printDistanceMatrix(dist);
    printAllPaths(dist, next);

    return 0;
}