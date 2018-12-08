//
// Created by Darring on 2018/12/7.
//
/*
(1)   AOE��
    *���
     AOE��AOV���Ǵ�Ȩ�������޻�ͼ��
    ��������ʵ���϶�Ӧ��AOV����(Activity on Vertex),����������һ��ͼ�У����֮����໥��Լ��ϵ����������Ⱥ�˳�����������ϵ.
    ����ʵ�ʴ��͹��̻���Ŀ�У�����ÿ��������������ϵ�⣬���ǻ��ȽϹ�������·���Ƿ��ܹ�˳�������Լ��������·�̵����ʱ��.
    ��Щ������ڽ���Ӱ���������̵Ľ��ȣ���������Щ��Ƿ������������̵�Ч�ʡ�

     *AOE(Activity On Edge netword)�������ר??���ҳ�����?�̵�����Щ���費�ܱ������?��?��
     *                      1.��Щ��ǹ��̽��ȵĹؼ�   2.��������������Ҫ�೤ʱ��
     *AOE�������ʣ�

                ֻ����ĳ������������¼������󣬴Ӹö�������ĸ�����ܿ�ʼ��

                ֻ���ڽ���ĳ����ĸ�����������ö�����������¼����ܷ�����

     * AOV���Ķ����ʾ��� �߱�ʾ�֮������ȹ�ϵ
       AOE���ı߱�ʾ�����Ҳ��ʾ���ȹ�ϵ�����ϵ�Ȩֵ��ʾ�������ʱ��
        AOE���ǽ����ڻ֮����Լ��ϵ(�Ⱥ��ϵ)û��ì�ܵĻ����ϣ��������������������������Ҫ����ʱ��
        ���ԣ��ؼ�·��Ҫ��������������õĻ�����

 (2)  �ؼ�·������ʼ�㵽��ɵ� ��������� ʱ��֮�� ��·�����ȣ�����·�����·�йؼ�·����һ�����̿��ܻ��ж����ؼ�·�������ؼ�·���ϵĻ�йؼ��
 �����翪ʼʱ�� = ��ٿ�ʼʱ�䣩����ǰ��ɷǹؼ�������ܼӿ칤�̽��ȡ���֮��Ҫ���̹��ڣ�ֻ�����̹ؼ�·���ϵĻ�����̺���ܳ���֮ǰ�Ĺؼ�·������˷ǹؼ�·����

    �ص㣺��ǰ�涨������ؼ�·������ͼ�д�Դ�㵽������Ȩֵ��󣩵�·����

��������������������·���;������������̵Ĺ��ڣ���˵��һ��ʲô���⣿

�����������������ؼ�·���ϵĶ����붥��֮��Ļ��Ӧ�����翪ʼ����ٿ�ʼʱ������ȵģ�

�������������������������ô˵����������ʱ�䣨�����翪ʼʱ�����ٿ�ʼʱ��֮�������ѡһ��ʱ��㿪ʼ������˵������������Ǿ����������ʱ��ģ��ǾͲ��ǹؼ�·���ˡ�


��3���ؼ�·���㷨ʵ��
  ������AOE����Ѱ�����л�����翪ʼʱ�������ʼʱ�䣬���Ƚ����ǣ������������ȣ�������û�ǹؼ������ȻҲ���ǹؼ�·���ϵ�һ����


    1.����¼������緢��ʱ��etv(earliest time of vertex)��������vk�����緢��ʱ��
        ע�⣺etv[i]��������������ǰ�������緢��ʱ�����֮�����ȷ�������������������Ļ����Ͻ��е�

    2.����¼���������ʱ��ltv�����ڲ��Ƴ��������̵�ǰ���£�����vk��������ʱ��
        ע�⣺ltv[i]�����������к�̵�������ʱ�����֮�����ȷ���������������������Ļ����Ͻ��е�
    3.�߻<Vi,Vj>�����ʱ�䣺t(i,j),��AOE���ϵıߵ�Ȩֵ
    4.�߻<Vi,Vj>���翪��ʱ��ete(earliest time of edge)������ak�����緢��ʱ��
        ete(i,j) = etv[i];
    5.�߻<Vi,Vj>������ʱ��lte�����ڲ��Ƴ��������̵�ǰ���£���ak��������ʱ��
        lte(i,j) = ltv[j] - t(i,j)

    �� etv �� ltv ���ete, lte
    �� ete[k] == lte[k] ʱ���ûΪ�ؼ��



*/

#ifndef TOPOLOGICAL_SORT_AND_AOE_CRITICAL_PATH_H
#define TOPOLOGICAL_SORT_AND_AOE_CRITICAL_PATH_H


#include <iostream>
#include <string>
#include <stack>
using namespace std;
#define  N 100

struct Node{
    int idx;      //�ڵ����
    int indegree; //�����
    int earliest_happen_v;//������緢��ʱ��
    int latest_happen_v;//���������ʱ��  ������ ���� ��ã�
    Node(){
        indegree = 0;
        earliest_happen_v = 0;//��ʼ��Ϊ�ǳ���
    }
};


struct Edge{
    int earliest_happen_e;//�����綯��ʱ��
    int latest_happen_e;
    Edge(){
    }
};

class AOE{
private:
    Node* NodeList;//�������
    int AdjMatrix[N+1][N+1];//�ڽӾ���
    int n;//�������
    int e;//�ߵ�����
    stack <int> StoreToPo;//�洢�����˵�ջ
    stack <int> s;//��������ĸ���ջ
public:
    AOE(){
        NodeList = new Node[N+1];
    }

    ~AOE(){
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
            NodeList[i].idx = i ;
        }


        cout << "����ÿ���ߵ���Ϣ����Ӧÿ���������ڽӵ���������±� 1-base���±���������:";
        int index1;
        int index2;
        int weight;
        for (int j = 1; j <= e; ++j) {
            cin >> index1 >> index2 >> weight;
            AdjMatrix[index1][index2] = weight;
            NodeList[index2].indegree ++;
        }
    }





    /**********************************************************/
   //Ѱ�ҹؼ�·���ǽ�������������Ļ����ϣ��޸�ԭ������������
    /*1. ��ʼ��ÿ���ڵ�����緢��ʱ�� =0
     * 2.�����̽ڵ����緢��ʱ��Ĳ��� if v1.earliest_time_v  + weigth(v1, v2) > v2.earliest_time_v; ����v2�����緢��ʱ��
    * 3.Ϊ�˷�����������ˣ�ջ�� ����������ڵ�

     */
    bool TopoSort(){
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
            return false;

        } else {
            return true;

        }

    }

    //�޸�ɾ����һ����֮��ĸ��������ȣ��������ж�Ϊ0�Ķ�����븨��ջS��
    void Fix_Node_Indegree(int dele){
        StoreToPo.push(s.top());  //׼�������˵�˳��
        s.pop();
        for(int i = 1; i <= n; ++i){
            if(AdjMatrix[dele][i] != 0){//��� ��  ����ڽ�
                NodeList[i].indegree--;
                if (NodeList[i].indegree == 0 ) {//��� ��� �ɲ��� 0 ���� 0 ��
                    s.push(i);
                }
                ///�������緢�ָý���ʱ�䣬����ǰ�������緢��ʱ�����֮�����ȷ��
                if(NodeList[dele].earliest_happen_v + AdjMatrix[dele][i] > NodeList[i].earliest_happen_v){
                    NodeList[i].earliest_happen_v = NodeList[dele].earliest_happen_v + AdjMatrix[dele][i];
                }
            }
        }
    }


    //��ؼ�·��
    bool CriticalPath(){
        if(!TopoSort()){
            cout << "��ͼ�л���������ؼ�·��" << endl;
            return false;
        }
        cout<<endl;
        //��ʼ��ÿ���������ٷ���ʱ�䣬
        for(int i = 1; i <= n; ++i){
            NodeList[i].latest_happen_v = NodeList[n].earliest_happen_v;//��ʼ��Ϊ �������翪ʼʱ��
        }


        //�� ������������ ����������ʱ��
        //�Ƚ��ڽӾ����������,�����һ���㣨ԭ��������������һ���㣩��ʼ��
        Inverse_Matrix();


        while(!StoreToPo.empty()){
            int t = StoreToPo.top();
            StoreToPo.pop();
            for(int i = 1; i <= n; ++i){
                if(AdjMatrix[t][i] != 0){//  t->i   ���к�̵���ٷ���ʱ�����֮�����ȷ����ٷ���ʱ��
                    if(NodeList[i].latest_happen_v - AdjMatrix[t][i] < NodeList[t].latest_happen_v ){
                        NodeList[t].latest_happen_v = NodeList[i].latest_happen_v - AdjMatrix[t][i];
                    }
                }
            }
        }

        //���������ԭͼ���ڽӾ��󣬱�����ؼ��
        Inverse_Matrix();


        cout<<"�ؼ��ڵ���:";
        for(int j = 1; j <= n; ++j ){
            if(NodeList[j].latest_happen_v == NodeList[j].earliest_happen_v){
                cout<<"V"<<j<<" ";
            }

        }
        cout<<endl;
        cout<<"�ؼ�·��:";
        //��ÿ���ߵĶ���ʱ�� �� �ؼ� ·�����ؼ�·���϶�Ӧ�ĵ�Ϊ�ؼ��ڵ�
        //��Ϊ�ؼ����ǼȲ�����ǰ�ֲ����ƺ�ĵ�
        for(int i = 1; i <= n ;++i){
            for(int j = 1; j <= n; ++j){
                if(AdjMatrix[i][j] != 0){ // i->j
                    int ee = NodeList[i].earliest_happen_v;//�߻���翪ʼʱ��
                    int el = NodeList[j].latest_happen_v - AdjMatrix[i][j];//�߻����ʼʱ��
                    if(ee == el){
                        cout<<"V"<<i<<"->V"<<j<<" ";
                    }
                }
            }
        }


    }


    void Inverse_Matrix(){
        for(int i = 1; i <= n; ++i){
            int temp;
            for(int j = 1; j <= n; ++j ){
                temp = AdjMatrix[i][j];
                AdjMatrix[i][j] = AdjMatrix[j][i];
                AdjMatrix[j][i] = temp;
            }
        }

    }


};
#endif //TOPOLOGICAL_SORT_AND_AOE_CRITICAL_PATH_H
