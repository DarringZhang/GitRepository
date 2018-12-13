#include "Kruskal.h"
int main() {
    int n;
    while(scanf("%d", &n) != EOF && n){
        MinimumSpanningTree tree(n);
        tree.kruskal();
        tree.Destroy();
    }
        return 0;
}