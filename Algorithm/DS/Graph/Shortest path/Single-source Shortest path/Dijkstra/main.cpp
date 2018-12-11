#include "Dijkstra.h"
int main() {
    Dijkstra dij;
    int n,m;
    cout <<"请输入结点个数和路径数"<<endl;
    while(scanf("%d%d",&n,&m),n+m){

        dij.CreateGraph(n,m);
        dij.Calculate_Dijkstra(1);
        cout<<dij.SumDistance();
    }

    return 0;
}