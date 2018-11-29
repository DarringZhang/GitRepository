//
// Created by Darring on 2018/11/28.
//

#ifndef INC_1_UNDIRECTIEDGRAPH_H
#define INC_1_UNDIRECTIEDGRAPH_H

#include <iostream>
#include <vector>
#include <string>
#define SIZE 100
using namespace std;
struct Node{
    int InDegree;//���
    int OutDegree;//����
    string data;//�����Ϣ
    struct Node *OutAdjList;//����ڽӵ�Node *AdjList = new Node [SIZE]Ҳ����
    //AdjList = new Node[MAX];//Ϊʲô���ܷ�����
    Node(){
        InDegree = 0;
        OutDegree = 0;
    }

};


class DirectedGraph{
private:
    //vector<Node> NodeList[SIZE];����ã���
    Node *NodeList;
    int n;//�������
    int e;//�ߵ�����
public:
    DirectedGraph(){
        NodeList = new Node[SIZE];
    }
    ~DirectedGraph(){
        delete [] NodeList;
        for(int i = 1; i <= n; ++i ){
            delete [] NodeList[i].OutAdjList;
        }
    }

    void createAdjGraph(){
        int _n,_e;
        cout<<"����ͼ�Ķ������ͱ���:";
        cin>>_n>>_e;
        this->e = _e;
        this->n = _n;
        cout<<"����ÿ��������Ϣ���ַ�����:";
        string ch;
        for(int i = 1; i <= n; ++i ){
            cin>>ch;
            NodeList[i].OutAdjList = new Node[SIZE];
            NodeList[i].data = ch;
        }

        cout<<"����ÿ���ߵ���Ϣ����Ӧÿ���������ڽӵ���������±� 1-base ע���±���������:";
        int index1;
        int index2;
        int outde1;//��һ��ĳ���
        for(int j = 0; j < e; ++j){
            cin>>index1>>index2;
            NodeList[index1].OutDegree++;
            outde1 = NodeList[index1].OutDegree;
            NodeList[index1].OutAdjList[outde1] = NodeList[index2];

            NodeList[index2].InDegree++;
        }
    }


    void display(){
        //��ӡ���ж���������ڽӱߺͶ���
        for(int i = 1; i <= n; ++ i){
            if(NodeList[i].OutDegree == 0){
                cout<<NodeList[i].data<<"û���ڽӱ�!"<<endl;
            }
            else{
                cout<<NodeList[i].data<<"���ڽӱ��У�";
                for(int j = 1; j <= NodeList[i].OutDegree ; ++ j){
                    cout<< NodeList[i].data<<" -> "<< NodeList[i].OutAdjList[j].data<<", ";
                }
                cout<<endl;
            }

            cout<<NodeList[i].data<<"�����Ϊ��"<<NodeList[i].InDegree<<"�� ,����Ϊ"<<NodeList[i].OutDegree<<"'"<<endl;

        }
    }



};
#endif //INC_1_UNDIRECTIEDGRAPH_H
