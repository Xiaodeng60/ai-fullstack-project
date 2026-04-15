#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();


const int N = 9;    
const int STAGES = 5; 


const int stage[N] = {0, 1, 1, 2, 2, 2, 3, 3, 4};


struct Edge {
    int to;
    int weight;
};


vector<Edge> graph[N];

void buildGraph() {

    graph[0].push_back({1, 2});
    graph[0].push_back({2, 4});


    graph[1].push_back({3, 7});
    graph[1].push_back({4, 5});
    graph[2].push_back({4, 3});
    graph[2].push_back({5, 2});


    graph[3].push_back({6, 6});
    graph[3].push_back({7, 8});
    graph[4].push_back({6, 4});
    graph[4].push_back({7, 5});
    graph[5].push_back({7, 3});


    graph[6].push_back({8, 3});
    graph[7].push_back({8, 4});
}

int main() {
    buildGraph();

    int source = 0;   
    int sink = 8;    

    // dp[v] = 从源点到顶点v的最短路径长度
    vector<int> dp(N, INF);
    // prev[v] = 最短路径上顶点v的前驱
    vector<int> prev(N, -1);

    dp[source] = 0;

    for (int s = 0; s < STAGES; ++s) {
        for (int u = 0; u < N; ++u) {
            if (stage[u] != s) continue;   
            if (dp[u] == INF) continue;  
            for (const Edge& e : graph[u]) {
                int v = e.to;
                int w = e.weight;
                if (dp[u] + w < dp[v]) {
                    dp[v] = dp[u] + w;
                    prev[v] = u;
                }
            }
        }
    }

    // 输出结果
    if (dp[sink] == INF) {
        cout << "the shortest path from source to sink does not exist" << endl;
    }
    else {
        cout << "the shortest path length is: " << dp[sink] << endl;

        // 路径重构
        vector<int> path;
        for (int v = sink; v != -1; v = prev[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        cout << "the shortest path is: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }

    return 0;
}