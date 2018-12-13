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
    int InDegree;//入度
    int OutDegree;//出度
    string data;//结点信息
    struct Node *OutAdjList;//邻接数组
    Node(){
        InDegree = 0;
        OutDegree = 0;
    }

};


class DirectedGraph{
private:
    Node *NodeList;
    int n;//顶点个数
    int e;//边的条数
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
        cout<<"输入图的顶点数和边数:";
        cin>>_n>>_e;
        this->e = _e;
        this->n = _n;
        cout<<"输入每个结点的信息（字符串）:";
        string ch;
        for(int i = 1; i <= n; ++i ){
            cin>>ch;
            NodeList[i].OutAdjList = new Node[SIZE];
            NodeList[i].data = ch;
        }

        cout<<"输入每条边的信息（对应每条边输入邻接的两个点的下标 1-base 注意下标输入有序）:";
        int index1;
        int index2;
        int outde1;//第一点的出度
        for(int j = 0; j < e; ++j){
            cin>>index1>>index2;
            NodeList[index1].OutDegree++;
            outde1 = NodeList[index1].OutDegree;//记录点二在点一邻接数组的位置
            NodeList[index1].OutAdjList[outde1] = NodeList[index2];

            NodeList[index2].InDegree++;
        }
    }


    void display(){
        //打印所有顶点的所有邻接边和度数
        for(int i = 1; i <= n; ++ i){
            if(NodeList[i].OutDegree == 0){
                cout<<NodeList[i].data<<"没有邻接边!"<<endl;
            }
            else{
                cout<<NodeList[i].data<<"的邻接边有：";//根据出度打印邻接边
                for(int j = 1; j <= NodeList[i].OutDegree ; ++ j){
                    cout<< NodeList[i].data<<" -> "<< NodeList[i].OutAdjList[j].data<<", ";
                }
                cout<<endl;
            }

            cout<<NodeList[i].data<<"的入度为："<<NodeList[i].InDegree<<"‘ ,出度为"<<NodeList[i].OutDegree<<"'"<<endl;

        }
    }



};
#endif //INC_1_UNDIRECTIEDGRAPH_H
