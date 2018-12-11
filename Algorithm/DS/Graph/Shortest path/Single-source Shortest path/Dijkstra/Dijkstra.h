//
// Created by Darring on 2018/12/10.
//
//ʵ��4.2����ͨʵ�֣�ʱ�临�Ӷ�O(n^2)�����������С�ѵ�ʵ�֣����Ӷ�ElgV��
//ע�͵������distance���洢���������С�ľ���ֵ�����������ȶ���

/*�����ʵ�ָ�Prim����
 * ��ʼʱ��Դ����ӵ�SPT�У�Ȼ��ÿ������һ����������SPT��
 * ��ȡ�ı����ǿ��Ը�����Դ�㵽��δ��SPT��ĳ����������·�������������㰴�յ�Դ��ľ�����С���������ӵ�SPT��
 *��SPT֮��Ķ�����ѡ��һ������v����Ӧ�ߵ�Ȩֵ��С��Ȼ��������߽����ɳڲ������㷨����ֱ��ͼ�����ж��㶼��SPT��Ϊֹ��
 * */
#ifndef DIJKSTRA_DIJKSTRA_H
#define DIJKSTRA_DIJKSTRA_H


#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>
#include <climits>
using namespace std;
#define SIZE 100000
//�Ӷ��г�һ������Դ��·����̵Ķ��㡣�պ÷��϶ѵĻ���������ɾ���Ѷ�Ԫ�أ�������Ҳ������Dijkstra�Ǹ�̰���㷨��
//���ǿ���֤��dijkstra��̰������ȷ�ģ����ʼǱ�

struct Node{
    int idx;
    int pai;
    int d;//�����ʼ��ľ���
    bool visited ;
    Node(){
        pai = -1;
        visited = false;
        d = INT_MAX;
    }

};


bool operator < (const Node &a,const Node &b)
{
    return a.d > b.d;
}

class Dijkstra {
private:
    int AdjMatrix[101][101];
    Node NodeList[101];
    // int distance[10001];//�洢���е㵽begin �����̾����ʼֵ
    int N, M;


public:
    Dijkstra() {

    }

    void CreateGraph(int n, int m) {
        N = n;//n������
        M = m;//m��·��

        for (int i = 1; i <= n; ++i) {//��ʼ������б�
            NodeList[i].idx = i;
        }

        for (int j = 1; j <= n; ++j) {//��ʼ���ڽӾ���
            for (int i = 1; i <= n; ++i) {
                AdjMatrix[j][i] = INT_MAX;
            }
        }
        cout << "������ͻ���" << endl;
        int a, b, cost;//���� a b �Ļ���
        for (int i = 1; i <= m; ++i) {
            cin >> a >> b >> cost;
            AdjMatrix[a][b] = cost;
        }
        cout << "finish" << endl;
    }

    void RELAX(Node u,Node v,int w){ //distance����ÿ��ֵ����start��v��·��������Ȩֵ���ۼ�
        if(NodeList[v.idx].d > NodeList[u.idx].d + w){//��u�������Ѵ���С,w = ����Զ��u v���ɴ������
            NodeList[v.idx].d = NodeList[u.idx].d + w;//����u.d
            NodeList[v.idx].pai = u.idx;
        }
    }

//�޸�Ȩ������ͼ����Դ���·��

    void Calculate_Dijkstra(int start){//��ʼ
        Node t;
        int count = N-1;
        priority_queue<Node> Q;//������нڵ㣬����dֵ����


        //��ʼ�����е㵽start �����̾����ʼֵ
        for(int i = 1; i <= N; ++i){
            NodeList[i].d = AdjMatrix[start][i];
            if(NodeList[i].d != INT_MAX){
                NodeList[i].pai = start;
                Q.push(NodeList[i]);

            }
        }
        NodeList[start].d = 0;
        NodeList[start].visited = true;


        while(count>0){

            do{
                t = Q.top(); //����start�������һ��δ�����t
                Q.pop();
            }while(NodeList[t.idx].visited == true);

            if(NodeList[t.idx].pai!=-1 && NodeList[NodeList[t.idx].pai].visited == true){//����ǰ��������δ���ɳڵ��ĵ���ǰ��һ���Ѿ������·������
                NodeList[t.idx].visited = true;//����֤�� ������˵���ɳڵĴ�����
                count--;
            }
            else if(NodeList[t.idx].pai ==-1 ){
                continue;
            }



            //Ȼ���ɳ�startͨ����ǰ�ڵ�t����� �� ������i��·��
            for(int i = 1; i <= N; ++ i){
                if(t.idx!=i && AdjMatrix[t.idx][i]!=INT_MAX){//t���Լ��Ͳ����ɳ��ˣ���t��i����Զ������̫��Ҳ�����ɳ�
                    RELAX(NodeList[t.idx],NodeList[i],AdjMatrix[t.idx][i]);//start�����ͨ��t��������������㣬���Ƿ�����ɳ�
                }//һ���ǰ������·����˳�����ɳڣ��м���������ɳ�Ҳû��ϵ�������ɳ���Ҳ���簴�����·���ɳڵĳ̶ȴ󣬻�Ҫ���ɳ�һ��
            }

            for(int i = 1; i <= N; ++i){//��t���ڵģ� ��δ�������·���ĵ� �������
                if(i!= t.idx&&AdjMatrix[t.idx][i] != INT_MAX && NodeList[i].visited == false ){
                    Q.push(NodeList[i]);
                }
            }

        }

    }

    void PrintShortestPath(){//�����ӡ���κ������ɴ������·��
        int sum,j;
        for(int i = 2; i <= N; ++i){
            sum = NodeList[i].d;
            j = i;
            while(NodeList[j].pai != -1){
                cout<<NodeList[j].idx<<"<-"<<NodeList[j].pai<< " ";
                j = NodeList[j].pai;
            }
            cout<<"  sum = "<< NodeList[i].d <<endl;
        }
    }


};
#endif //DIJKSTRA_DIJKSTRA_H
