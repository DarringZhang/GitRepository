#include "BellmanFord.h"
#include "SPFA.h"


int main() {
    int n,m;
    cout<<"请输入节点的个数和边数：";
    cin>>n>>m;


    cout<<"优化前："<<endl;
    BellmanFord bell;
    bell.CreateGraph(n,m);
    if(bell.Violence_Calculate_BellmanFord(1)){
        bell.PrintShortestPath();
    }
    else{
        cout<<"该图有负权重环"<<endl;
    }

    cout<<"SPFA优化后:"<<endl;
    SPFA spfa;
    spfa.CreateGraph(n,m);
    spfa.Caluculate_SPFA(1);
    spfa.PrintShortestPath();

    return 0;
}