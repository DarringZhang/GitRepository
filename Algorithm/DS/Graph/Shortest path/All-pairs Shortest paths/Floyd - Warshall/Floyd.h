//
// Created by Darring on 2018/12/13.
//

#ifndef FLOYD_WARSHALL_FLOYD_H
#define FLOYD_WARSHALL_FLOYD_H
/*
 * Floyd�㷨ֻ���ڲ����ڸ�Ȩ���������ʹ�ã���Ϊ�䲢�����жϸ�Ȩ��������Ҳ˵��������и�Ȩ������ô���·�������壬
 * ��Ϊ���ǿ��Բ����߸�Ȩ�����������·��ֵ���Ϊ�˸������������Դ������Ȩ�ߵ����޸�Ȩ���������
 * ���Ͼ������Դ���·��Floyd�㷨�����ڶ�̬�滮��ʮ�����š�
 * �����临�Ӷ�ȷʵ�ǲ��ҹ�ά����ΪҪά��һ��·��������˿ռ临�Ӷȴﵽ��O(n^2)��ʱ�临�Ӷȴﵽ��O(n^3)��ֻ�������ݹ�ģ��С��ʱ�򣬲��ʺ�ʹ������㷨��
 * ������ʵ�ʵ�Ӧ���У���Դ���·������ģ���ˣ��Ǹ�Ȩ�ص�Dijkstra����
 * */
#include <iostream>
#include <climits>
#include <cmath>
#include <string>
using namespace std;

class Floyd {
protected:
    int AdjMatrix[201][201];
    int N, M;
    int Path[201][201];

public:
    Floyd() {

    }

    void CreateGraph(int n, int m) {
        N = n;//n������
        M = m;//m��·��

        for (int j = 0; j < n; ++j) {//��ʼ���ڽӾ��� 0-base
            for (int i = 0; i < n; ++i) {
                if(i==j){
                    AdjMatrix[j][i] = 0;
                }
                else{
                    AdjMatrix[j][i] = INT_MAX;
                }
            }
        }

        //��ʼ��·��
        for (int j = 0; j < n; ++j) {//��ʼ���ڽӾ��� 0-base
            for (int i = 0; i < n; ++i) {
                Path[j][i] = -1;
            }
        }



        cout << "�������Ȩֵ" << endl;
        int a, b, cost;
        for (int i = 1; i <= m; ++i) {
            cin >> a >> b >> cost;
            AdjMatrix[a][b] = cost;
        }
        cout << "finish" << endl;
        Print();
    }

    /*���ǴӶ�̬�滮�ĽǶȿ��ǣ��⶯̬�滮��Ŀ���ص���Ǻ���Ķ���״̬�����ֽ׶Σ����Ƕ��� f[k][i][j]Ϊ����ǰk�Ľڵ㣬
     * ��i��j���ܵõ������·����f[k][i][j]���Դ�f[k-1][i][j]ת�ƹ���������������k���ڵ㣬Ҳ���Դ�f[k-1][i][k]+f[k-1][k][j]ת�ƹ�����
     * ��������k���ڵ㡣�۲�һ�����״̬�Ķ��壬���㲻���������ӽṹ���޺�Ч��ԭ��

     1.�����ӽṹ��ͼ�ṹ��һ���Զ��׼��Ķ������·������·����Ȼ�����·��
    2.�޺�Ч�ԣ�״̬f[k][i][j]��f[k-1][i][j]��f[k-1][i,k] �Լ�f[k-1][k][j]ת�ƹ����������׿��Կ�����
        f[k] ��״̬��ȫ��f[k-1]ת�ƹ�����ֻҪ���ǰ�k�ŵ������ѭ���У����ܱ�֤�޺�Ч�ԡ�
        //����״̬���Ż����ˣ���֤��ǰ״̬��������
     * */
    void Calculate_floyd(){
        int flag = 0;
        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if(i!=j&&AdjMatrix[i][k]!=INT_MAX&&AdjMatrix[k][j]!=INT_MAX&&AdjMatrix[i][j] > AdjMatrix[i][k] + AdjMatrix[k][j]){
                    //ע�������if�ж�AdjMatrix[i][k]!=INT_MAX&&AdjMatrix[k][j]!=INT_MA//
                    //��Ϊ����INT_MAX ��ӿ��ܵ���һ����С�ĵĸ������Ǹ������������������һ������INT_MAX�������ɳ�ifҲ������
                        AdjMatrix[i][j] =  AdjMatrix[i][k] + AdjMatrix[k][j];
                        cout<<"=="<<++flag<<"=="<<endl;
                        Print();
                        Path[i][j] = k;

                    }
                    //AdjMatrix[i][j] = min(AdjMatrix[i][j], AdjMatrix[i][k] + AdjMatrix[k][j]);

                }
            }
        }
        Print();
    }

    // ��ӡ�м���
    void Print(){
        for(int i = 0; i < N; ++ i){
            for(int j = 0; j < N; ++ j){
                if(AdjMatrix[i][j]!=INT_MAX){
                    printf("%d\t",AdjMatrix[i][j]);
                }
                else{
                    printf("��\t");
                }
            }
            cout<<endl;
        }
        printf("\n--------------------------------\n");
    }


    /*
     * ���������֪�������·���ĳ��ȣ�ʵ��Ӧ�������ǳ�������Ҫ֪�������·������Floyd�㷨����ô�����·���أ�
     *ֻ��Ҫ��¼�����ڸ���f[i][j]��ʱ���õ����м�ڵ����ĸ��Ϳ����ˡ�����������path[i][j]��¼��i��j�ɳڵĽڵ�k��
     * ��ô��i��j,�϶����ȴ�i��k��Ȼ���ٴ�k��j�� ��ô�������ҳ�path[i][k] , path[k][j]���ɣ�\
     * �� i��k�����·�� i -> path[i][k] -> k -> path[k][j] -> k Ȼ����path[i][k]��path[k][j] ��һֱ��ĳ�����ڵ�û���м�ڵ�Ϊֹ
     *
     * /

 //�����·��:��ô���صݹ��ַ���
    string getPath(int[][] Path, int i, int j) {
        if (Path[i][j] == -1) {
            return " "+i+" "+j;
        } else {
            int k = Path[i][j];
            return getPath(Path, i, k)+" "+getPath(Path, k, j)+" ";
        }
    }
*/
};
#endif //FLOYD_WARSHALL_FLOYD_H
