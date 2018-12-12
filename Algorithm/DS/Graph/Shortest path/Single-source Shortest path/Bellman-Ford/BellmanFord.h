//
// Created by Darring on 2018/12/11.
//

#ifndef BELLMAN_FORD_BELLMANFORD_H
#define BELLMAN_FORD_BELLMANFORD_H
/*���㷨�ͱȽϱ���
 * �㷨��ÿ�������ɳڲ����������ظ�|V|-1�Σ������㷨��������|V|��|E|�����ȵ�ʱ���ڽ����Դ���·������
 * �Աߵ����û��Ҫ�󣬲������Դ���Ȩ�ߣ����ܴ�����
 * ����һ��ͼG(v,e)(v����㼯��e����߼�)��ִ��|v|-1�α߼����ɳڲ�������ν�ɳڲ��������Ƕ���ÿ����e1(v,w)��
 * ��Դ�㵽w�ľ������Ϊ��ԭ��Դ�㵽w�ľ��� �� Դ�㵽v�ľ������v��w�ľ��� �н�С���Ǹ���v-1���ɳڲ���֮��
 * �ж��Ƿ���Դ���ܵ���ĸ������жϵķ������ǣ���ִ��һ�α߼����ɳڲ����������һ���ɳڲ��������ɳڳɹ��ıߣ���ô��˵��ͼ���и������㷨���Ӷ�ΪO(ne)
 * */
#include <iostream>
#include <queue>
#include <climits>
#include <cmath>
using namespace std;
#define SIZE 101
//ע������Ҫ�˼���AdjMatrix��ά�����С������Ԫ��̫������ջ�ռ������������ʱ��û���⣬��ջ�ռ�ķ����������е�ʱ�����ġ�����������ð취�ǽ��ж��ڴ���䣬���ڴ�ͺܴ�ջ�ռ�Ĵ�Сֻ��K��������
// ���ѿռ�Ĵ�С���ԴﵽG������������Ȼ���������ڴ��ˣ��ѿռ���������new������֮��Ҫע��delete���ͷ�

struct Node{
    int idx;
    int pai;
    bool visited;//��SPFA�ж��Ƿ��ڶ�����
    Node(){
        pai = -1;
        visited = false;
    }
};


class BellmanFord {
protected:
    int AdjMatrix[SIZE][SIZE];
    Node NodeList[SIZE];
    int distance[SIZE];//�洢���е㵽begin �����̾����ʼֵ
    int N, M;


public:
    BellmanFord() {

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



    //����һ��boolֵ��boolֵΪtrue��ͼ��û��Դ��ɴ�ĸ�����false��Ϊͼ����Դ��ɴ�ĸ�����
    bool Violence_Calculate_BellmanFord(int s){

        for(int i = 1; i <= N; ++i){
            distance[i] = AdjMatrix[s][i];
            if( AdjMatrix[s][i]!=INT_MAX){
                NodeList[i].pai = s;
            }
        }
        distance[s] = 0;


        for(int i = 1; i <= N-1; ++i){//�����·���ϵ�ÿһ���߶���һ���ɳڣ��� N-1 ��

            for(int j = 1; j <= N; ++j){//�����������ڽӾ����ж��Ƿ��������ڱߣ�������ڣ�������ɳڲ���
                for(int k = 1; k <= N; ++k){
                    if(AdjMatrix[j][k]!=INT_MAX){//��ʵ����ط����Դ�һ�ݱ߼�,�洢start��end������ĳ���ߵ������˵㣬��ʼ��ͼ��ʱ�򣬹���������еıߣ��洢��һ�������С��ڽ���Bellman-Ford��ʱ��ֱ�ӱ�������߼����ɣ���ȥ�˶�����жϡ�

                        if(distance[j]+AdjMatrix[j][k] < distance[k]){
                            NodeList[k].pai = j;
                        }

                        distance[k] = min(distance[k],distance[j]+AdjMatrix[j][k]);//ͨ�� j -> k ������ ����k���Ƿ�ȽϽ�

                    }

                }

            }
        }

        //�ж��Ƿ��и������ٱȽ�һ�� �Ѿ��ɳںõıߣ� ��ͨ�� j -> k ������ ����k���Ƿ�ȽϽ����������и�Ȩ�ػ�
        for(int j=1 ;j <= N ; j++) {
            for (int k = 1; k <= N; k++) {
                if (AdjMatrix[j][k] != INT_MAX) {
                    if(distance[k] > distance[j]+AdjMatrix[j][k]){
                        return false;
                    }
                }
            }
        }

        return true;
    }


    void PrintShortestPath(){//�����ӡ����ʼ�㵽�κ�һ���ɴ������·��
        int sum,j;
        for(int i = 2; i <= N; ++i){
            sum = distance[i];
            j = i;
            //�л����������·��û����
            /*while(NodeList[j].pai != -1){
                cout<<NodeList[j].idx<<"<-"<<NodeList[j].pai<< " ";
                j = NodeList[j].pai;
            }*/
            cout<<"  sum = "<< sum <<endl;
        }
    }


};

#endif //BELLMAN_FORD_BELLMANFORD_H
