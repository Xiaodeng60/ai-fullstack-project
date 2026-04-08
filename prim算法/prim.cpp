#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n = 5;
    vector<vector<int>> graph(n, vector<int>(n, 0));
    graph[0][1] = graph[1][0] = 2;
    graph[0][2] = graph[2][0] = 3;
    graph[1][2] = graph[2][1] = 1;
    graph[1][3] = graph[3][1] = 4;
    graph[2][3] = graph[3][2] = 5;
    graph[3][4] = graph[4][3] = 6;

    vector<bool> visited(n, false);
    visited[0] = true;
    int totalWeight = 0;

    for (int count = 0; count < n - 1; ++count) {
        int minEdge = INT_MAX;
        int u, v;
        for (int i = 0; i < n; ++i) {
            if (visited[i]) {
                for (int j = 0; j < n; ++j) {
                    if (!visited[j] && graph[i][j] != 0 && graph[i][j] < minEdge) {
                        minEdge = graph[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }
        visited[v] = true;
        totalWeight += minEdge;
        cout << "Edge: " << u << " - " << v << ", Weight: " << minEdge << endl;
    }

    cout << "Total weight of MST: " << totalWeight << endl;
}