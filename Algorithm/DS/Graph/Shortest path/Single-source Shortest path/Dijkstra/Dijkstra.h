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


struct Edge{int to,cost;};
typedef pair<int,int>P; //first����̾��룬second�Ƕ���ı��



class Dijkstra {
private:
    int AdjMatrix[101][101];
    Node NodeList[101];
    vector<Edge>G[SIZE];
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
            AdjMatrix[b][a] = cost;
        }
        cout << "finish" << endl;
    }

    void dijkstra(int s){
        priority_queue<P> Q;
        int *d = new int[SIZE];
        memset(d,INT_MAX,SIZE* sizeof(d));// �ǵ�delete
        d[s] = 0;
        Q.push(P(0,s));
        while(!Q.empty()){
            P p = Q.top();
            Q.pop();
            int v = p.second;//��ȡ�õ�ı��
            if(d[v]<p.first){//����Ҫ�ɳ�
                continue;
            }
            for(int i = 0; i <= )
        }
    }


};
#endif //DIJKSTRA_DIJKSTRA_H
