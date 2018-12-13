//注：本Dijkstra基于最小堆的优化实现， 普通实现请关注我的GitHUb：DarringZhang,  experiment4/4-2里面
#include "Dijkstra.h"
int main() {
    int n,m;
    Dijkstra Dij;
    cin>>n>>m;
    Dij.CreateGraph(n,m);
    Dij.Calculate_Dijkstra(1);
    Dij.PrintShortestPath();
    return 0;
}