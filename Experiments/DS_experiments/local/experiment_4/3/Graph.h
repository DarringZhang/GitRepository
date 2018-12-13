//
// Created by Darring on 2018/11/26.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

/*
 * //DFS  BFS  �ڽӾ���洢��ʽ�����Ӷ�O(n^2)����ռ�O(V)
 *
 * */
/*DFS���������Ҫ���ʣ�DFS��?��?ͼ�γ�?���ж�������ɵ�ɭ��,���v�������
��ɭ��?���u�ĺ�� ���ҽ��� ���v�ڽ��u�Ļ�?�׶α����֣����ķ���ʱ������ʱ��������Ż��ṹ
����ͼ����ͨ����������DFS����
 ����ͼ��ǿ��ͨ������G ��G^T�ж��ܵ���ĵ�
 ����ͼ���ս���ʱ��Ӵ�С��˳�����DFS.  DFS��?��?ͼ�γ��ж�������ɵ�ɭ�֡� ɭ���е�ÿ�������һ��ǿ��ͨ����
 ����DFS���Ǹ��жϽ�ȥ�Ĵ�����

 */
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

       //why int Adj[N] = [0,]//���û��new,��������������й�����Adj��ָ��ͻᶪʧ����new�����Ŀռ䣬ר����һ���ڴ�洢��������ʾdelete,�Ͳ��ᱻ�ͷ�
       // ������ȡ��ַ�õ�������������ָԪ�صĵ�ַ��//��ָ��ȡ��ַ�õ�����ָ���������ĵ�ַ���������GitRepository/other/pointer
        for(int i = 0; i < N; ++ i){

            if(bfs[u][i] == 1){
                Adj[i] = 1;
            }

//
//            if(dfs[u][i] == 1){
//                Adj[i] = 1;
//           }


        }
        return Adj;
    }

    void BFS(int start){
        queue <int> Q;//���ø������У��ȷ��ʳ�ʼ��㣬�ٳ�ʼ�ڵ���ھӣ����ھӵ��ھ�
        Q.push(start);
        NodeList[start].color = GRAY;//start��λ�õĽ���Ѿ�������
        NodeList[start].find = 0; //��Ƿ���ʱ��

        int *Adj;
        while(!Q.empty()){
            int front = Q.front();
            Q.pop();
             Adj = FindAdj(front);  //Ѱ�ҵ�ǰ�ڵ��  �ڽӽ��
            for(int i = 0; i < N; ++ i){//����ǰ���  ����δ���ʹ����ڽӽ�� push
                if(Adj[i] == 1){//for each node in Adj[front]
                    if(NodeList[i].color == WHITE){
                        NodeList[i].color = GRAY;
                        NodeList[i].find = NodeList[front].find +1;//���׽��ķ���++
                        NodeList[i].pai = front;
                        Q.push(NodeList[i].idx);
                    }
                }
            }
            NodeList[front].color = BLACK;
            print_BFS(NodeList[front]);//BFS�ص�Ĵ�ӡ��ֻ��һ��ʱ��
            delete [] Adj;
            Adj = NULL;
        }

        //����Ƿ���BFS���ܱ�������
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
            if(NodeList[i].color == WHITE){//����ͼ����ͨ����������жϽ�ȥ���ٴΣ����м�����ͨ����
                DFS_VISIT(NodeList[i].idx);
            }
        }

    }

    /*���ȷ��ʳ�����start, �ӳ��������������������ÿ���ڽӵ�w,
    ��wΪ���ʣ����� w δ�µĳ����㣬ֱ�������εĵ������ڽӵ㶼��������Ϊֹ���ٻ��ݵ���һ���--------�ݹ�*/
    void DFS_VISIT(int start){
        clock ++;
        NodeList[start].start_discover = clock;
        NodeList[start].color = GRAY;
        int *Adj = FindAdj(start);
        for(int i = 0; i < N; ++ i){
            if(Adj[i] == 1){            //for each node in Adj[front]
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
        delete [] Adj;
        Adj = NULL;
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
