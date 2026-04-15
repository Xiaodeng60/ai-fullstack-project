#include <iostream>
using namespace std;
#include <climits>
#include <vector>

vector<int> dist;
vector<vector<int>> cost;
int dijkstra(const vector<vector<int>>& graph,int n, int start,int end){
    vector<int> dist(n,INT_MAX);
    vector<bool> visited(n,false);
    dist[start]=0;
    for(int i=0;i<n;i++){
        int u=-1;
        int minDist=INT_MAX;
        for(int j=0;j<n;j++){
            if(!visited[j]&&dist[j]<minDist){
                u=j;
                minDist=dist[j];
            }//找到距离前一个节点最近的未访问节点u
        }
        if(u==-1) break;
        visited[u]=true;
        for(int v=0;v<n;v++){
            if(!visited[v]&&graph[u][v]!=INT_MAX){
                dist[v]=min(dist[v],dist[u]+graph[u][v]);
            }
        }
    }
    return dist[end];
}
int main(){
    const int n=9;
    vector<vector<int>> graph(n,vector<int>(n,INT_MAX));
    graph[0][1] = 2; graph[0][2] = 3; graph[0][3] = 7;
    graph[1][4] = 6; graph[1][5] = 4;
    graph[2][5] = 7; graph[2][6] = 9;
    graph[3][5] = 5; graph[3][6] = 7;
    graph[4][7] = 11;
    graph[5][8] = 20;graph[5][7]=5;
    graph[6][7] = 10;
    graph[7][8] = 9;
    int start=5,end=8;
    int ans=dijkstra(graph,n,start,end);
    cout<<"The shortest path from "<<start<<" to "<<end<<" is: "<<ans<<endl;
    return 0;
 
}