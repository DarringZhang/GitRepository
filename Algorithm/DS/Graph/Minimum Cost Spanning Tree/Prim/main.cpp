#include"Prim.h"

int main() {
    int n,m;
    while(scanf("%d%d", &n,&m) != EOF && n){
        MinimumSpanningTree graph(n,m);
        graph.prim(1);
    }
    return 0;
}