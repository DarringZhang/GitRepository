#include "BellmanFord.h"
#include "SPFA.h"


int main() {
    int n,m;
    cout<<"������ڵ�ĸ����ͱ�����";
    cin>>n>>m;


    cout<<"�Ż�ǰ��"<<endl;
    BellmanFord bell;
    bell.CreateGraph(n,m);
    if(bell.Violence_Calculate_BellmanFord(1)){
        bell.PrintShortestPath();
    }
    else{
        cout<<"��ͼ�и�Ȩ�ػ�"<<endl;
    }

    cout<<"SPFA�Ż���:"<<endl;
    SPFA spfa;
    spfa.CreateGraph(n,m);
    spfa.Caluculate_SPFA(1);
    spfa.PrintShortestPath();

    return 0;
}