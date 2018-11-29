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
    int degree;
    string data;//�����Ϣ
   // vector<Node> AdjList;
    struct Node *AdjList;

    //AdjList = new Node[MAX];//Ϊʲô������new���ṹ������ֻ��һ����������������ṹ�壬ʲôҲû����
    Node(){
        degree = 0;
    }

};


class UnDirectedGraph{
private:
//    vector<Node> NodeList;//����new,��װ���˵ģ��ɱ䳤������
  Node *NodeList;
    int n;//�������
    int e;//�ߵ�����
public:
    UnDirectedGraph(){
        NodeList = new Node[SIZE];
    }
    ~UnDirectedGraph(){
        delete [] NodeList;
        for(int i = 1; i <= n; ++i ){
            delete [] NodeList[i].AdjList;
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
           // Node t;
           // t.data = ch;
           // NodeList.push_back(t);//����Vector������pushback���٣�vector�ĳ��Ⱦ��Ƕ���
           NodeList[i].AdjList = new Node[n+1];
          NodeList[i].data = ch;
        }

        cout<<"����ÿ���ߵ���Ϣ����Ӧÿ���������ڽӵ���������±� 1-base���±���������:";
        int index1;
        int index2;
        int de1;//�õ�Ķ���
        int de2;
        for(int j = 0; j < e; ++j){
            cin>>index1>>index2;
            NodeList[index1].degree++;//���Ǽ������м����ڽӵ�
            de1 = NodeList[index1].degree;
            NodeList[index1].AdjList[de1] = NodeList[index2];

            NodeList[index2].degree++;//���Ӷ�����ʱ���ڽӵ��Ҫ��������
            de2 = NodeList[index2].degree;
            NodeList[index2].AdjList[de2] = NodeList[index1];
        }
    }


    void display(){
        //��ӡ���ж���������ڽӱߺͶ���
        for(int i = 1; i <= n; ++ i){
            cout<<NodeList[i].data<<"���ڽӱ��У�";
            for(int j = 1; j <= NodeList[i].degree ; ++ j){
                cout<< NodeList[i].data<<" <-> "<<NodeList[i].AdjList[j].data<<", ";
            }
            cout<<endl;
            cout<<NodeList[i].data<<"�Ķ����ǣ�"<<NodeList[i].degree<<"��"<<endl;
        }
    }



};
#endif //INC_1_UNDIRECTIEDGRAPH_H
