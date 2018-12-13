#include "Articulation.h"
int main() {
    UnDirectedGraph articul;
    int flag = 0;
    articul.createAdjGraph();
    articul.FindArticulation();
    for(int i = 1; i <= articul.GetN(); ++i){
        if(articul.GetNodeList()[i].key == true){
            flag ++;
        }
    }
    cout<<flag;
    return 0;
}