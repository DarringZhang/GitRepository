#include "Dijkstra.h"
int main() {
    Dijkstra dij;
    int n,m;
    cout <<"�������������·����"<<endl;
    while(scanf("%d%d",&n,&m),n+m){

        dij.CreateGraph(n,m);
        dij.Calculate_Dijkstra(1);
        cout<<dij.SumDistance();
    }

    return 0;
}