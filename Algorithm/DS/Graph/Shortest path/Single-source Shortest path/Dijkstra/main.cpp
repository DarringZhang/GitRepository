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