//
// Created by Darring on 2018/11/26.
//

#ifndef FOREST_UNION_FIND_H
#define FOREST_UNION_FIND_H
//ɭ�ֵĴ洢��ʽ��1.˫�׷�
// 2.�������ַ���������һ���������ת��Ϊ����������ȥ�����

/*ɭ�ֵ�Ӧ?, ���鼯(?˫�ױ�?��ʵ��)
       ���飺һЩ�� N ��Ԫ�صļ���Ӧ�������У�����ͨ�����ڿ�ʼʱ��ÿ��Ԫ�ع���һ����Ԫ�صļ��ϣ�
       Ȼ��һ��˳������ͬһ���Ԫ�����ڵļ��Ϻϲ������Ҫ��������һ��Ԫ�����ĸ������С�
       ������̾��漰�������ϲ����͡����ҡ����������������Һͺϲ�������ʵ���ǽ����ڴ�Ҷ�ڵ����ϵݹ���Ҹ��ڵ�Ĳ����ϡ�
       ���ò��鼯������ʵ��������洢���ݣ����Ҳ��Ҳ����ͺϲ�������ʱ�临�ӶȽ���$O(1)$��
 */
/*ʵ�� ����˼·�����鼯��һ���������ݽṹ������Щ�����У�ÿ��������һ���������еļ�����һ����γ��ˡ�ɭ�֡���
��ʡ�ռ䣬��������Ϳ���ʵ�֡�Ϊ�˷���˵�����������������ֵ�������ݱ��������� i ��Ӧ�������ֵarr[i]����i�ĸ��ڵ㡣

 �ϲ��Ż����ڡ��ϲ��������ĸ��ĸ��ڵ�ָ����ⲽ�У�����������ĸ߶ȣ����߶Ƚϵ͵��ǿ���ָ��߶Ƚϸߵ����ĸ��ڵ㡣
 ���ԣ��ڳ�ʼ����ʱ����Ҫ��һ������rank[]��������¼�� i Ϊ���ڵ�����ĸ߶ȡ�
 */
#include <iostream>

class UnionFind{
private:
     int count;
     int * parent;//parent[i] Ԫ�� i ���ڵ������
     int * rank;// rank[i] ��iΪ�� �ļ�������ʾ�����Ĳ���
public:
    UnionFind(int count){
        this->count = count;
        parent = new int[count];
        rank = new int[count];

        //��ʼÿ���ڵ������ ÿ���ڵ�ĸ������Լ���
        //��ʼ ���� ����1
        for(int i = 0; i<count; i++){
            parent[i] = i;
            rank[i] = 1;
        }
    }

    ~UnionFind(){
        delete[] parent;
        delete [] rank;
    }

    int normal_find(int i){//��ͨ�������Ҹ�����ѹ��·��
        int j = i;
        while(parent[j]>0){
            j = parent[j];//�������������ϲ���
        }
        return j;
    }

//����������·��ѹ���������ڡ����ҡ��Ĺ����У������ĸ߶�ѹ���� 2 ��

//·��ѹ����ʽ���ң��ݹ�
    int fix_find_recursion(int i){
        if( i != parent[i]){//i ���� i���ڼ��ϵĸ�
            parent[i] = fix_find_recursion(parent[i]);//����һ���Ҹ���һֱ���ϣ�ֱ������ֵ����Ϊֹ
        }
        return parent[i];
    }
//�ǵݹ�
    int fix_find_non_recursion(int x){
        int k,j,r;
        r = x;
        while(r != parent[r]){//���Ҹ��ڵ�
            r = parent[r];
        }

        k = x;
        while(k != r){//x!= x�ĸ��ڵ�r
            j = parent[k]; //j ��ʱ�洢k �ĸ��ڵ�
            parent[k] = r; //k�ĸ��ڵ� ָ����ڵ�
            k = j;    //k �Ƶ����ڵ��λ�ã���һ�� ѹ�����ڵ��·�����Դ�����
        }//����˼�룺�ײ�������ѹ��·��
        return r;//���ظ��ڵ������ĸ�
    }

    bool is_connected(int p,int q){
        return fix_find_recursion (p) == fix_find_recursion(q);
    }


//�ϲ������ֱ�Ϊp��q��Ԫ�ص�ͬһ������
    void Merge(int p,int q){
        int p_root = fix_find_recursion(p);
        int q_root = fix_find_recursion(q);
        if(p_root ==q_root){return;}

        //Ϊ�˲��������ĸ߶ȣ��ϲ�ʱ�����ĸ߶ȵ͵� ָ�� ���� �ߵ�
        if(rank[p_root] < rank[q_root]){//q  ������ ��
            parent[p_root] = q_root;
        }
        else if(rank[p_root] < rank[q_root]){
            parent[q_root] = p_root;
        }
        else{
            parent[p_root] = q_root;//p����ָ��q����
            rank[q_root]  +=1;
        }

    }
};



#endif //FOREST_UNION_FIND_H
