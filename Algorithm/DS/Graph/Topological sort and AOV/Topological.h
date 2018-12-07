//
// Created by Darring on 2018/12/5.
//

#ifndef TOPOLOGICAL_SORT_AND_AOE_TOPOLOGICAL_H
#define TOPOLOGICAL_SORT_AND_AOE_TOPOLOGICAL_H
/*
 * �������򣺻����Ⱥ����������ϵ����Ҫ��Ϊ���һ�������ܷ�˳����е�����, ÿ�����裨��㣩��������ϵ
 * ָ��һ�������޻�ͼ(Directed Acyclic Graph)��G=(V,E)�����ж���v��������,����Ľ�������G��һ����(u,v),��ô����u�����ڶ���v��ǰ��
 *Ҫ������������ǰ����ͼ�в����ڻ�,��⣺DFS̽��
 *���������裺if  DFS����л������� ����   else ����ͼ��ѡ��һ��û��ǰ���Ľڵ��������ɾ���ýڵ㼰���������ı�
 * �ظ�else ,ֱ��ȫ�������Ѿ���� ���� ��ǰͼ������û��ǰ���Ľڵ㣨���Ϊ0�Ľڵ㣩
 * ��ͼ�ж���δ��ȫ�������ʣ��Ķ������Ⱦ���Ϊ0����˵�����д�������
 *
 *
 * ����һ��ֻ��Ҫʹ?DFS�Ϳ��Ի��?��DAG������������:һ������DFS_VISIT(Node u)�������� ����Q.push_front(u);
 * ��������������ͨ������ÿ���������������������������ж��㶼����������������У��򲻴��ڻ�
 *
 *
 * ��������Ľ����Ψһ�� ���Ⱥ����˳�򶼲���
 * */
#include <iostream>
#include <string>
#include <stack>
using namespace std;
#define  N 100
struct Node{
    int idx;//�ڵ����
    int indegree;
    bool has_been_pushed;
    Node(){
        indegree = 0;
        has_been_pushed = false;
    }
};

 class AOV{ //AOV Activity On Vertex Network �����ʾ�����
 private:
     Node* NodeList;//�������
     int AdjMatrix[N+1][N+1];//�ڽӾ���
     int n;//�������
     int e;//�ߵ�����
     stack <int> s;// stack���ܱ���������û�е�������
 public:
     AOV(){
         NodeList = new Node[N+1];
     }

     ~AOV(){
         delete [] NodeList;
     }

     void createGraph(){
         //�ڽӾ���
         //���Ķ��������ÿ��������
         int _n;
         int _e;
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
             NodeList[index2].indegree ++;
         }
     }

     //�޸�ɾ����һ����֮��ĸ��������ȣ���//�����ж�Ϊ0�Ķ�����븨��ջS��
     void Fix_Node_Indegree(int dele){
         s.pop();
        for(int i = 1; i <= n; ++i){
            if(AdjMatrix[dele][i] != 0){//ɾ����������ڵ�delete �� ��ȵ� i ���
                NodeList[i].indegree--;
                if (NodeList[i].indegree == 0 ) {
                    s.push(i);
                }
            }
        }
     }

     void TopoSort(){
             int count = 0;//�����Ѿ�����˶��ٸ�

             for (int i= 1; i <= n; ++i){//�����ж�Ϊ0�Ķ����??������ջS��
                 if (NodeList[i].indegree == 0) {
                     s.push(i);
                 }
             }

             while (!s.empty()){
                 cout << s.top() << " ";
                 Fix_Node_Indegree(s.top());
                 count++;

             }

         if (count < n) {
             cout << "��ͼ�л�,��������ؼ�·��" << endl;
         } else {
             cout << "��ͼ�޻�" << endl;
         }

     }

 };
#endif //TOPOLOGICAL_SORT_AND_AOE_TOPOLOGICAL_H
