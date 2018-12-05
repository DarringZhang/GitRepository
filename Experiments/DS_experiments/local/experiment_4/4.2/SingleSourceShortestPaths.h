//
// Created by Darring on 2018/12/2.
//

#ifndef INC_4_2_SINGLESOURCESHORTESTPATHS_H
#define INC_4_2_SINGLESOURCESHORTESTPATHS_H

#include <iostream>
#include <queue>
#include <climits>
using namespace std;


struct Node{
    int idx;
    int pai;
    bool visited ;
    Node(int _pai = -1){
        pai = _pai;
        visited = false;
    }

};

class Dijkstra{
private:
    int AdjMatrix[101][101];
    Node NodeList[101];
    int distance[10001];//�洢���е㵽begin �����̾����ʼֵ
    int N,M;


public:
    Dijkstra(){

    }

    void CreateGraph(int n,int m){
        N = n;//n������
        M = m;//m��·��

        for(int i = 1; i <= n; ++i ){//��ʼ������б�
            NodeList[i].idx = i;
        }

        for(int j = 1; j <= n; ++j ){//��ʼ���ڽӾ���
            for(int i = 1; i <= n; ++i){
                AdjMatrix[j][i] = INT_MAX;
            }
        }
        cout<<"������ͻ���"<<endl;
        int a,b,cost;//���� a b �Ļ���
        for(int i = 1; i <= m; ++i ){
            cin>>a>>b>>cost;
            AdjMatrix[a][b] = cost;
            AdjMatrix[b][a] = cost;
        }
        cout<<"finish"<<endl;
    }

    void RELAX(Node u,Node v,int w){ //distance����ÿ��ֵ����start��v��·��������Ȩֵ���ۼ�
        if(distance[v.idx] > distance[u.idx] + w){//��u�������Ѵ���С,w = ����Զ��u v���ɴ������
            distance[v.idx] = distance[u.idx] + w;//����u.d
            v.pai = u.idx;
        }
    }

//�޸�Ȩ������ͼ����Դ���·��

    void Calculate_Dijkstra(int start){//��ʼ
        int t;
        int count = N-1;
        NodeList[start].visited = true;
        //��ʼ�����е㵽start �����̾����ʼֵ
        for(int i = 1; i <= N; ++i){
            distance[i] = AdjMatrix[start][i];
        }
        distance[start] = 0;//�Լ����Լ�


        while(count-->0){
            t = FindMinDistance();//ÿ��ȡ��һ������start��Ȩֵ��С��δ���ʵĵ�
            NodeList[t].visited = true;

            //Ȼ���ɳ�startͨ��t����㵽������j��·��
            for(int i = 1; i <= N; ++ i){
                if(t!=i && AdjMatrix[t][i]!=INT_MAX){//t���Լ��Ͳ����ɳ��ˣ���t��i����Զ������̫��Ҳ�����ɳ�
                    RELAX(NodeList[t],NodeList[i],AdjMatrix[t][i]);//start�����ͨ��t��������������㣬���Ƿ�����ɳ�
                }

            }
        }

    }

    int SumDistance(){
        return distance[N];
    }

    int FindMinDistance(){//�ҵ�δ��ǵ���С����±�
        int min_idx = N;
        for( int i = 1; i <= N; ++i){
            if(distance[min_idx] > distance[i] && NodeList[i].visited == false ){
                min_idx = i;
            }
        }
        return min_idx;
    }

};
#endif //INC_4_2_SINGLESOURCESHORTESTPATHS_H
