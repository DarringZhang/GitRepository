//
// Created by Darring on 2018/12/19.
//
//Qt
#ifndef ALLSORT_ALLSORT_H
#define ALLSORT_ALLSORT_H
#define LEN 1000000
#include <iostream>
#include <vector>
#include <climits>
//#include <algorithm>
using namespace std;


void Print(vector<int>& Print){//���ô��ݣ��ܸı䱻���õ�ʵ��
    for(int i = 0; i < LEN; ++i ){
            cout<<Print[i]<<" ";
    }
            cout<<endl;
}

//Time(worst and average):O(n^2)��Time(best):O��n��,Space:O(1),  stable
void Bubble_Sort(vector<int> &A,int begin,int end){//���ô��ݣ��ܸı䱻���õ�ʵ��
    for(int i = LEN; i > 0; --i) {// ���������ˣ�ÿ�˽���ǰ��Χ��0 ~ �Ѿ��źõ����Ԫ��ǰ��һλ�������Ԫ�ع�λ
        for(int j = 0;j < i-1; ++j){
            if(A.at(j) > A.at(j+1)){
                int temp = A.at(j);
                A.at(j) = A.at(j+1);
                A.at(j+1) = temp;
            }
        }
    }
    //Print(A);
}


//��i��ѭ��, ��A[i, �� , n - 1]���ҳ���С��, ������A[i]����.i= 0, ��, n - 2
// Time(best and worst and average):O(n^2), Space:O(1),  Instable
void Selection_Sort(vector<int> &A,int begin,int end){
        int min;
        for(int i = 0; i < LEN; ++i){
            min = A[i];
            for(int j = i+1; j < LEN; ++j){//��ѭ�������ã�����ǰ��Χ���Ѿ��źõ���СԪ�صĺ���һλ ~ ��β�����Ԫ������
                if(min>A[i]){
                    int t = min;
                    min = A[j];
                    A[j] = t;
                }
            }
            A[i] = min;
        }
        //Print(A);
}

//Time(worst and average):O(n^2)��Time(best):O��n��,Space:O(1),  stable
//�ٹ�ģ��̫���ʱ������һ������ķ�ʽ����������O��n^2���ķ�ʽ����ã���������С��������⺯��sort�����ǵ��ÿ�����nС�����ߵݹ鵽n�Ƚ�Сʱ���ò���
void Insert_Sort(vector<int> &A,int begin,int end){
    for(int j = 1; j < LEN; ++j){
        int key = A[j];//�� A [j] = key���뵽�źõ�����A[0,j-1]��

        int i = j-1;//�ҵ��źõ������е����һ��������ǰ��֪���

        while(i >= 0 && A [i] > key){ //key ̫С�ˣ�keyҪ��ǰ�ƶ��ˣ���ʱ A [i] Ϊ��ǰ�ź�Ԫ�� ����������һλ
            A[i + 1] = A[i];//key �Ѿ�����¼�����ˣ���һ��ѭ��ǰһ���� A [i] ����key ����key ��λ�� ��A[i+1]��λ�ã��������Ϳճ�һ��λ�á��ٷ�������һ��һ������
            i--;
        }
        A[i+1] = key;//�ҵ����ʵ�key��λ����
    }
    //Print(A);
}


//��������ĸĽ���ϣ�����򣨿粽����˼�룩��������������ԭ�����������������ܿ죬so����������������,�ϴ�Ĳ����ƶ����ݣ�С����ֻ����������ȽϺͽ������ɵ���ȷλ�á�
//���һ�������Բ���5����������Ȼ�����Բ���3����������ô�����в������Բ���3���򣬶������Բ���5���򣬱��Խ��Խ�������1�����������򣨴�ʱ���Ǽ򵥵Ĳ��������ˣ�
//Time Best:O(nlogn),worst and average: nlog^2 n(),�����õıȽ��㷨��O(n log n)Ҫ��һЩ����Լ��n��1.5 ��1.6�η�, Space O(1)
//Instable
// ��Ȼ���ȶ��Ĳ�������ĸĽ������ǲ��ȶ�����Ϊ����Ĺ�������ͬ������������һ�飬û����ϵ�����Խ�����ʱ����ܽ������λ��
void Shell_Sort(vector<int> &A,int begin,int end){
    int h = 1;
    while(h < LEN/3){//�Ƚ���������Ϊ���ı�������󲽳�
        h = 3 * h + 1;
    }
    while(h >= 1){
        for(int i = h; i < LEN; ++i){//i������󣬴���ÿ���б������
            for(int j = i; j >= h && A[j] < A[j-h]; j-=h){//ÿ�������Լ���бȽϣ�ÿ��ѭ���������е�һ����������λ��ǰ��
                swap(A[j],A[j-h]);
            }
        }
        h /= 3;//�����еĸ���
    }
    //Print(A);
}


//����˼�룬�����ģС��ֻ��һ��Ԫ�أ������ţ������Ѿ��źõģ��ϲ���
/*������������һ��������ƽ�ֳ�����С���飬�ֱ������С����ݹ飬�ٺϲ��������ź����С����
 * �ؼ���������ô�ϲ���
 *
 * Time(bset average medium):O(nlogn), Space :O(n) stable
 * */
void Merge_Sort(vector<int> &A,int begin,int end){
    if(begin < end){
        int q = (begin + end)/2;
        Merge_Sort(A,begin,q);
        Merge_Sort(A,q+1,end);
        Merge(A,begin,q,end);        //�ϲ�
    }
    else{
        return;;
    }
}

//�ö���Ŀռ䣬������С���� ����С���� �ŵ� �������У���С�����һ��ֱ��С����ȡ��Ϊֹ
void Merge(vector<int> &A,int begin,int medium, int end){
    int n1 = medium - begin +1;//�������ĳ��ȣ�0 ~ medium,��Ҫȡ�õ�medium, ʵ�ʳ���medium+1
    int n2 = end - medium; //o-base
    vector<int> L(n1+1);
    vector<int> R(n2+1);
    for(int i = 0; i < n1; ++i ){//���λ�ò����
        L[i] = A[begin + i];
    }
    for(int j = 0; j < n2; ++j){
        R[j] = A[medium+j+1];
    }
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    int i = 0;
    int j = 0;
    for(int k = begin; begin < end; k++){
        if(L[i] <= R[j]){
            A[k] = L[i];
            i++;
        }
        else{
            A[k] = R[j];
            j++;
        }
    }
}

//����˼�룺����n��Ԫ�ص�����A, ÿ�ΰ�����ֳ�������: ����С�ڵ���A[n-1], ���ִ���A[n-1], ��ôA[n-1]
//�Ϳ��Է���������������м�. Ȼ��ݹ�ؿ���������������С��ģ������.
void Quick_Sort(vector<int> &A,int begin,int end){
    if(begin < end){
        int q = Partition_end(A,begin,end);//�ؼ������������
        Quick_Sort(A,begin,q-1);
        Quick_Sort(A,q+1,end);
    }
}
//����Partition
//�̲��ϣ�����һ������Ϊpivot
int Partition_begin(vector<int> &A,int begin,int end){//end ���������±�
    int pivot = A[begin];//������ĵ�һ��Ԫ����Ϊ ��Ŧ
    while(begin < end){// ��һ�ν���ʱ ��һ��Ԫ��λ�þͱ����ǣ��Ӵ����������пճ�һ��λ����pivot ��¼���Ǹ�ֵ��λ�ã���Ŧpivotһֱ���ε�����û�й̶���λ�� ��
        while(begin < end && A[end] >= pivot){//��ͼ���Ұ���ҵ�һ������ŦС��Ԫ�أ�����ѭ��
            -- end;
        }
        A[begin] = A[end];//�Ͷ����begin����λ��,���������ŦС��Ԫ�ذ��õ����

        while(begin < end && A[begin] <= pivot){//��ͼ�������ҵ�һ������Ŧ���Ԫ�أ�����ѭ��
            ++ begin;
        }
        A[end] = A[begin];//�Ͷ����begin����λ��,���������Ŧ���Ԫ�ذ��õ��ұ�

    }
    A[end] = pivot;//��ʱend = begin�� ���м��λ�� �� pivot
    return end;
}

//��2�� ��i j Ϊ�ֽ��߷ָ�������
int Partition_end(vector<int> &A,int begin,int end){
    int pivot = A[end];//������ĵ�һ��Ԫ����Ϊ ��Ŧ
    int i = begin-1;//��pivotС�������е����һ����
    int j = i+1;//��pivot��������е����һ�����ĺ���һ�����������ŵĵ�һ����
    //��ʼi ָ�� ��һ�� ���� Ԫ�ص�ǰһ��λ�ã� j ָ���һ������Ԫ��
    //i + 1 = ��pivot��������е� ��һ����
    while(j <= end - 1){//��begin <= end ��j �ܵ����ȥ��
        if(A[j] <= pivot){//j ��ǰԪ�ر�pivot С��Ҫ����ǰԪ��j��Ϊ��ߣ���ʱiָ���pivotС�������е����һ����
            i++;//������i �ĺ����һ���� �� ��pivot��������еĵ�һ����
            swap(A[i],A[j]);
        }
        j++;//��һ��Ԫ��
    }

    //��pivot�ŵ����ʵ�λ��
    A[end] = A[i+1];//�������һ��λ�÷ŵ���pivot�����ڻ���A[i+1] (��pivot��������еĵ�һ����)
    A[i+1] = pivot;
    return  i+1;//pivot��λ��
}


void Heap_Sort(vector<int> &A,int begin,int end);
/********************************************����Ϊ���ڱȽϵ�����*************************************************/
 /**************************************֤�����ڱȽϵ�����ĸ��Ӷ�����O��nlogn��*************************************/
/************************************����Ϊ���� ���Ӷȵ������㷨********************************/

void Counting_Sort(vector<int> &A,int begin,int end){

}

void Radin_Sort(vector<int> &A,int begin,int end){

}

#endif //ALLSORT_ALLSORT_H
