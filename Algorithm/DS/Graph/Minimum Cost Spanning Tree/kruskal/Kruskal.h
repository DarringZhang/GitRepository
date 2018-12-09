
#ifndef KRUSKAL_KRUSKAL_H
#define KRUSKAL_KRUSKAL_H



//
// Created by Darring on 2018/12/4.
//

/*
ͼ����??����(Minimum Cost Spanning Tree)
 ����?����Ȩ����ͨ?��ͼG(V,E), w:(u,v)��>R, ����ϣ���ҵ�E��?��?����?��T,ʹ��ÿ?��v���ܱ�������\
 ����Ȩֵ��?.

*/

/*����С��������kruskal�㷨��
Kruskal�㷨�ǻ���̰�ĵ�˼��õ��ġ��������ǰ����еı߰���Ȩֵ�ȴ�С�������У�
 ���Ű���˳��ѡȡÿ���ߣ���������ߵ������˵㲻����ͬһ���ϣ���ô�ͽ����Ǻϲ���
 ֱ�����еĵ㶼����ͬһ������Ϊֹ��������ô�ϲ���һ�����ϣ�
 ��ô�������ǾͿ����õ�һ�����ߡ���-���鼯
 ������֮��Kruskal�㷨���ǻ��ڲ��鼯��̰���㷨��

 (1)��ͼG����һ��ɭ�֣�ÿ������Ϊһ�ö�������
(2)�����еı߼��뼯��S����һ��ʼS = E
(3)��S���ó�һ����̵ı�(u,v)�˴�ʹ�����ȶ��У����(u,v)����ͬһ�����ڣ�������u,v�ϲ�����������ͬʱ��(u,v)�����������ı߼�E'
(4)�ظ�(3)ֱ�����е�����ͬһ�������߼�E'����һ����С������


*/
#include <iostream>
#include <queue>
using namespace std;

struct edge{
    int point1,point2,cost;
    bool operator < (const edge& n) const {
        return cost > n.cost;//�������ȶ��е�С�ںţ���ΪĬ�����ȶ��������ѣ��Ƚϱߵ�cost
    }
};

class MinimumSpanningTree{
private:
    int *parent;
    int N;
public:
    MinimumSpanningTree(int n){
        this->N = n;
        parent = new int[n+1];
        for(int i = 1; i <= n; ++i ){
            parent[i] = i;
        }
    }

    void Destroy(){
        delete [] parent;
    }

    //���鼯
    /*
     * ����rank��·��ѹ���㷨ʵ�ֵĲ��鼯�ʱ�临�Ӷ���O(m ��(n) )�����Ц���Ackerman������ĳ����������
     * ���������ֵ���Կ����ǲ�����4�����ԣ����鼯�����ֵ��Ͳ�����makeset,merge,findset����ʱ�临�Ӷ������Եġ�
     * n>2048��  ����n�����Ǹ�<=4�ĳ���
     * */
    int fix_find_recursion(int i){
        if( i != parent[i]){//i ���� i���ڼ��ϵĸ�
            parent[i] = fix_find_recursion(parent[i]);//����һ���Ҹ���һֱ���ϣ�ֱ������ֵ����Ϊֹ
        }
        return parent[i];
    }

    bool Merge(int a,int b){
        a = fix_find_recursion(a);
        b = fix_find_recursion(b);//�ҵ����Ը����ȣ�˳��ѹ��һ��·��
        if(a == b){
            return false;
        }
        else{//����һ�����ģ��ϲ�
            parent[a] = b;
            return true;
        }
    }

    void kruskal(){
        edge e;
        int ans = 0;
        int flag = 0;
        priority_queue<edge> Q;//�˴�ʹ�����ȶ��У������ʵ�֣���ʹ�㷨���Ӷȿ�����O��elogv��
        //������������ͨ���飬��Ҫʹ��sort�������ֶβ��ò�ͬ�����򷽷��������źã�����һ���������棬O��eloge��
        int m = N*(N-1)/2;//m���ߣ�������������֮�䶼�бߣ�
        cout<<"�������Ϣ"<<endl;
        while(m--){//�������ȶ��н� �� ��Ȩ�� ��������
            cin>>e.point1>>e.point2>>e.cost;
            Q.push(e);
        }

        while(!Q.empty()){//e
            e = Q.top();//logv
            Q.pop();
            if(Merge(e.point1,e.point2)){//��������㲻��ͬһ������,����Ҫ����һ��·��
                flag ++;
                ans += e.cost;
            }

            if(flag == N-1){//�Ѿ���һ����С���������ٶ�һ���߾ͳɻ���
                break;
            }
        }

        cout<<ans;
    }
};


#endif //KRUSKAL_KRUSKAL_H
