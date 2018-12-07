//
// Created by Darring on 2018/11/29.
//

#ifndef INC_4_1_ARTICULATION_H
#define INC_4_1_ARTICULATION_H
/*
 * �ؼ��ڵ㣺������ͨͼ�У�ȥ������v ���������ӵıߺ�G����ͨ��v is articulation points
 * ���ǹؼ���㣺��ǰ��� �����ڰ�ɫ�ڵ� �� ��ǰ����ǰ��֮һ ֮�� ��һ��·���� ��ǰ��㲻��key
 * Ѱ�ҹؽڽڵ㣺�������low ֵ
 * lowֵ���������緢��ʱ��
 * �Ƚ�������ȡmin��1.�ý��v�ķ���ʱ��d;   2.v���лر��������ڽӻ�ɫ�ڵ㣨�Ѿ����ʵ�����k����d   3.v����һ���ڽӰ�ɫ���ӽ���w��lowֵ
 * ��v���ں��ӽ��w,ʹ w.low>v.d(��w���������ʱ���ڷ��ʸ���v֮�󣩣�v���ǹؼ��ڵ�
 * */
#include <iostream>
#include <string>
#include <climits>
#define SIZE 100
using namespace std;
enum color{WHITE,GRAY,BLACK};


struct Node{
    int idx;
    int degree;
    int low;
    int color;//��㱻��ǵ���ɫ
    int d;
    bool key;//�ж��Ƿ�Ϊ�ؼ��ڵ�
    Node(){
        degree = 0;
        color = WHITE;
        d = INT_MAX;
        low = INT_MAX;
        key = false;
    }

};


class UnDirectedGraph {
private:
    Node *NodeList;//�������
    int AdjMatrix[SIZE+1][SIZE+1];//�ڽӾ���
    int n;//�������
    int e;//�ߵ�����
    int clock;//��ʱ
    int count;//��¼��ǰ�Ѿ����ʵĽ�����
public:
    UnDirectedGraph() {
        NodeList = new Node[SIZE+1];
    }

    ~UnDirectedGraph() {

        delete [] NodeList;

    }
    int GetN(){
        return n;
    }
    Node* GetNodeList(){
        Node *p ;
        p = NodeList;
        return p;
    }
    void createAdjGraph() {
        int _n, _e;
        cout << "����ͼ�Ķ������ͱ���:";
        cin >> _n >> _e;
        this->e = _e;
        this->n = _n;
        //��ʼ���ڽӾ���
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <=n; ++j ){
                AdjMatrix[i][j] = 0;
            }
        }

        //��ʼ���������
        for(int i = 1; i <=n; ++i ){
            NodeList[i].idx = i;
        }


        cout << "����ÿ���ߵ���Ϣ����Ӧÿ���������ڽӵ���������±� 1-base���±���������:";
        int index1;
        int index2;
        for (int j = 0; j < e; ++j) {
            cin >> index1 >> index2;
            AdjMatrix[index1][index2] = 1;
            AdjMatrix[index2][index1] = 1;
            NodeList[index1].degree ++;
            NodeList[index2].degree ++;
        }
    }

    /*��DFS�Լ��޸ļ��ɣ���ΪDFSArticul ���ɵĽ���������б�ҵĽڵ㹹�ɵ��������������������������
        1.�����������û����������ϵ��������˸���ΪArticulation.������� count < n
        2.��������ĳ����Ҷ�ӽڵ�v ��v �������� �Ľڵ��û��ָ�� v �� ���ȵĻرߣ�vΪArticulation
     */
    void FindArticulation(){
        int flag;
        clock = 1;
        NodeList[1].d = clock;//ѡ��1�ŵ���Ϊ��ʼ��
        count = 1;

        for(int i = 1; i <= n; ++i){//Ѱ��һ�Ž��ĵ�һ���ڽӵ�
            if(AdjMatrix[1][i] ==1){
                flag = i;
                break;
            }
        }
        NodeList[1].color = GRAY;
        DFSArticul(NodeList[flag]);//��1�Ž����Ϊ�������ĸ����������ĵ�һ���ڽӵ�
        if(count < n){//������1�Ž��ĵ�һ���ڽӽ��������ڽӽ��󣬻ص�һ�Žڵ㣬����count < n�ܣ�˵������v������һ��һ��Ҫ����v,��һ�Žڵ�һ���ǹؼ��ڵ�
            NodeList[1].key = true;//���ڵ㵥������
            for(int i = 1; i <= n; ++i){
                if(AdjMatrix[1][i] == 1){//����һ�Žڵ�������ڽӽ��
                    if(NodeList[i].color == WHITE){
                        DFSArticul(NodeList[i]);
                    }
                }
            }
        }

    }

    void DFSArticul(Node u){
        NodeList[u.idx].color = GRAY;
        clock++;
        int min = clock;
        NodeList[u.idx].d = clock;//��ʱ  min = u.d
        count++;//�ַ�����һ�����
        for(int i = 1; i <= n; ++i){
            if(AdjMatrix[u.idx][i] == 1) {// u �������ڽӽ��
                if (NodeList[i].color == WHITE) {
                    DFSArticul(NodeList[i]);//�ݹ����u���ڽӺ��ӵ�low
                    if (NodeList[i].low < min) {//��������ڽӺ��ӵ�low,�Ƚ�
                        min = NodeList[i].low;
                    }
                    if (NodeList[i].low >= NodeList[u.idx].d) {//u�İ׺���low > u.d�����Ϲؼ��ڵ������
                        NodeList[u.idx].key = true;
                    }
                }
                else if(NodeList[i].d < min){//�Ƚ�ǰ����d�͵�ǰmin�����Ƿ�����нݾ���ֱ�ӹ���
                    min = NodeList[i].d;
                }
            }

        }

        NodeList[u.idx].low = min;

    }


};
#endif //INC_4_1_ARTICULATION_H
