/*
 * 注：由于BFS,DFS 的找结点的邻接数组 用的同一个函数*FindAdj(int u)，进行DFS，BFS切换时，需要替换两处注释：
 * 1.main函数有关两种不同遍历的内容，注释掉一个
 * 2.对应注释掉 FindAdj(int u) if判断
 * */
#include "Graph.h"
int main() {
    VisitedGraph graph;
    cout<<"BFS"<<endl;
    graph.BFS(0);

 /*   cout<<"DFS"<<endl;
    graph.DFS();
 */
    return 0;
}