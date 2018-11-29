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
    string data;//结点信息
    struct Node *AdjList;//存放邻接点Node *AdjList = new Node [SIZE]也不行
    //AdjList = new Node[MAX];//为什么不能放这里
    Node(){
        degree = 0;
    }

};


class UnDirectedGraph{
private:
    vector<Node> NodeList;
//    Node *NodeList;
    int n;//顶点个数
    int e;//边的条数
public:
    UnDirectedGraph(){
     //   NodeList = new Node[SIZE];
    }
    ~UnDirectedGraph(){
        delete [] NodeList;
        for(int i = 1; i <= n; ++i ){
            delete [] NodeList[i].AdjList;
        }
    }

    void createAdjGraph(){
        int _n,_e;
        cout<<"输入图的顶点数和边数:";
        cin>>_n>>_e;
        this->e = _e;
        this->n = _n;
        cout<<"输入每个结点的信息（字符串）:";
        string ch;
        for(int i = 1; i <= n; ++i ){
            cin>>ch;
            Node t;
            t.data = ch;
            NodeList.push_back(t);
        //    NodeList[i].data = ch;
        }

        cout<<"输入每条边的信息（对应每条边输入邻接的两个点的下标 1-base，下标输入无序）:";
        int index1;
        int index2;
        int de1;//该点的度数
        int de2;
        for(int j = 0; j < e; ++j){
            cin>>index1>>index2;
            NodeList[index1].degree++;//度是几，就有几个邻接点
            de1 = NodeList[index1].degree;
            NodeList[index1].AdjList[de1] = NodeList[index2];

            NodeList[index2].degree++;
            de2 = NodeList[index2].degree;
            NodeList[index2].AdjList[de2] = NodeList[index1];
        }
    }


    void display(){
        //打印所有顶点的所有邻接边和度数
        for(int i = 1; i <= n; ++ i){
            cout<<NodeList[i].data<<"的邻接边有：";
            for(int j = 1; j <= NodeList[i].degree ; ++ j){
                cout<< NodeList[i].data<<" <-> "<<NodeList[i].AdjList[j].data<<", ";
            }
            cout<<endl;
            cout<<NodeList[i].data<<"的度数是："<<NodeList[i].degree<<"‘"<<endl;
        }
    }



};
#endif //INC_1_UNDIRECTIEDGRAPH_H
