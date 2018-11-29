//
// Created by Darring on 2018/11/26.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
//������ͼG�У������������vi,vj�䣨vi>vj����һ����vi��vj������·����ͬʱ����һ����vj��vi������·���������������ǿ��ͨ(strongly connected)���������ͼG��ÿ�������㶼ǿ��ͨ��
// ��G��һ��ǿ��ͨͼ������ͼ�ļ���ǿ��ͨ��ͼ����Ϊǿ��ͨ����(strongly connected components)��

/*
 * ��?(ǿ)��ͨ?ͼ:?��ͼ��(ǿ)��ͨ?ͼ�����Ҽ�?�κ�?���������ĵ㼯�еĵ㶼�ᵼ��������(ǿ)��ͨ
 * ��С��ͨ��������С��������
 * ��ͨ?��ͼ�ļ�?��ͨ?ͼ��������?��
 * */
/*
 * �洢��ʽ��
 * �ڽӾ����ʾ�������飩���ڽ�����ʮ����������������ʾ����ͼ��
 * ��Ȼ,?��ͼ�����Ӿ����ǶԳƵ�
 * */
/*
 * ͼ�ı�����������ȣ�BFS��:Ϊ�˱���ͬһ���㱻���ʶ�Σ����������б�����±����ʹ��Ķ��㣬�ø�������visited[0~n-1]
 * BFS��һ�ֲ�α��������Ը��㷨��Ҫ����������ʵ�֡�����һ�����У�����push �����ڽӵ� ���д�δ���ʹ��Ľ��
 *
 * */
#include <iostream>
#include <climits>
#include <queue>
#include <vector>
using namespace std;
enum color{WHITE,GRAY,BLACK};
#define N 5

//�������ٽṹ���ڳ�ʼ������Ϊ����ṹ��ʱ����δ��������ڴ棬���Գ�ֵ���޷��洢�ġ�Ӧ�������ṹ��������ֹ���ֵ��
struct Node{
    int idx;
    int color;//��㱻��ǵ���ɫ
    int find;//BFS���ֵ�ʱ��
    int start_discover;//��ʼ���ʵ�ʱ��DFS
    int end_discover;//�������ʵ�ʱ��DFS
    int pai;//ǰ�����±�
    Node(){
        color = WHITE;  //δ����ǰ���ǰ�ɫ��
        start_discover = INT_MAX;//��ʼ�������ֵ�ʱ��
        end_discover = INT_MAX;
        find = INT_MAX;
        pai = -1;
    }
};


class VisitedGraph{
private:
    Node *NodeList;//��Ž��
    int clock;//��ʱ

    int bfs[N][N] = {    //����һ��5��5��ͼ
        { 0, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 0 },
        { 0, 1, 1, 1, 0 },
        { 1, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0 }
    };

    int dfs[5][5] = {
            { 0, 1, 1, 0, 0 },
            { 0, 0, 1, 0, 1 },
            { 0, 0, 1, 0, 0 },
            { 1, 1, 0, 0, 1 },
            { 0, 0, 1, 0, 0 }
    };

public:
    VisitedGraph(){
        NodeList = new Node[N];  //0-base
        for(int i = 0; i < N; ++i){
            NodeList[i].idx = i;//Ϊ�˷��㣬�ͽ�����±���Ϊ�����Ϣ
        }
    }

    ~VisitedGraph(){
        delete [] NodeList;
    }

    int *FindAdj(int u){
        int *Adj;
        Adj = new int(N);
        for(int i = 0; i < N; ++ i){
            Adj[i] = 0;
        }

       //why int Adj[N] = [0,]������ȡ��ַ�õ�������������ָԪ�صĵ�ַ��
        //��ָ��ȡ��ַ�õ�����ָ���������ĵ�ַ
        for(int i = 0; i < N; ++ i){
//            if(bfs[u][i] == 1){
//                Adj[i] = 1;
//            }

            if(dfs[u][i] == 1){
                Adj[i] = 1;
           }

        }
        return Adj;
    }

    void BFS(int start){
        queue <int> Q;
        Q.push(start);
        NodeList[start].color = GRAY;//start��λ�õĽ���Ѿ�������
        NodeList[start].find = 0;

        while(!Q.empty()){
            int front = Q.front();
            Q.pop();
            int *Adj = FindAdj(front);
            for(int i = 0; i < N; ++ i){
                if(Adj[i] == 1){//for each node in Adj[front]
                    if(NodeList[i].color == WHITE){
                        NodeList[i].color = GRAY;
                        NodeList[i].find = NodeList[front].find +1;
                        NodeList[i].pai = front;
                        Q.push(NodeList[i].idx);
                    }
                }
            }
            NodeList[front].color = BLACK;
            print_BFS(NodeList[front]);
        }

        Check_Cannot_reach(start);

    }


    void print_BFS(Node u){
        if(u.pai==-1){
            cout<< u.idx <<"�Ž��û��ǰ��";
        }
        else{
            cout<< u.idx <<"�Ž���ǰ����"<< u.pai <<"�Ž��";
        }
        cout<<", ����ʱ��Ϊ��"<<u.find<<"s"<<endl;
    }


    void DFS(){
        clock = 0;
        for(int i = 0; i < N; ++ i ){
            if(NodeList[i].color == WHITE){
                DFS_VISIT(NodeList[i].idx);
            }
        }

    }

    void DFS_VISIT(int start){
        clock ++;
        NodeList[start].start_discover = clock;
        NodeList[start].color = GRAY;
        int *Adj = FindAdj(start);
        for(int i = 0; i < N; ++ i){
            if(Adj[i] == 1){//for e-ach node in Adj[front]
                if(NodeList[i].color == WHITE){
                    NodeList[i].pai = start;
                    DFS_VISIT(NodeList[i].idx);
                }
            }
        }

        NodeList[start].color = BLACK;
        clock++;
        NodeList[start].end_discover = clock;
        print_DFS(NodeList[start]);

    }


    void print_DFS(Node u){

        if(u.pai == -1){
            cout<< u.idx <<"�Ž��û��ǰ��";
        }
        else{
            cout<< u.idx <<"�Ž���ǰ����"<< u.pai <<"�Ž��";
        }
        cout<<", discover/finish��"<<u.start_discover<<"/"<<u.end_discover<<endl;



    }

    void Check_Cannot_reach(int start){
        for(int i = 0 ;i < N; ++i){
            if(NodeList[i].color == WHITE){
                cout<<NodeList[start].idx<<"�Ž�㲻�ɵ���"<<NodeList[i].idx<<"�Ž�㣡"<<endl;
            }
        }
    }
};




#endif //GRAPH_GRAPH_H
