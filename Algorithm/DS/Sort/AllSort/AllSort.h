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


void Print(vector<int>& Print){//引用传递，能改变被调用的实参
    for(int i = 0; i < LEN; ++i ){
            cout<<Print[i]<<" ";
    }
            cout<<endl;
}

//Time(worst and average):O(n^2)，Time(best):O（n）,Space:O(1),  stable
void Bubble_Sort(vector<int> &A,int begin,int end){//引用传递，能改变被调用的实参
    for(int i = LEN; i > 0; --i) {// 计数多少趟，每趟将当前范围（0 ~ 已经排好的最大元素前面一位）的最大元素归位
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


//第i次循环, 从A[i, … , n - 1]中找出最小的, 将它和A[i]互换.i= 0, …, n - 2
// Time(best and worst and average):O(n^2), Space:O(1),  Instable
void Selection_Sort(vector<int> &A,int begin,int end){
        int min;
        for(int i = 0; i < LEN; ++i){
            min = A[i];
            for(int j = i+1; j < LEN; ++j){//此循环的作用：将当前范围（已经排好的最小元素的后面一位 ~ 队尾）最大元素挑出
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

//Time(worst and average):O(n^2)，Time(best):O（n）,Space:O(1),  stable
//再规模不太大的时候这是一种优秀的方式（在这三个O（n^2）的方式中最好，常数项最小），比如库函数sort不总是调用快排序，n小，或者递归到n比较小时，用插入
void Insert_Sort(vector<int> &A,int begin,int end){
    for(int j = 1; j < LEN; ++j){
        int key = A[j];//将 A [j] = key插入到排好的序列A[0,j-1]中

        int i = j-1;//找到排好的序列中的最后一个数（当前已知最大）

        while(i >= 0 && A [i] > key){ //key 太小了，key要往前移动了，此时 A [i] 为当前排好元素 序列中最大的一位
            A[i + 1] = A[i];//key 已经被记录下来了，第一次循环前一个数 A [i] 覆盖key ，（key 的位置 即A[i+1]的位置）。这样就空出一个位置。再符合条件一步一步往后
            i--;
        }
        A[i+1] = key;//找到合适的key的位置了
    }
    //Print(A);
}


//插入排序的改进：希尔排序（跨步插入思想），若插入排序中原来的序列有序，则插入很快，so尽量快让序列有序,较大的步长移动数据，小数据只需进行少数比较和交换即可到正确位置。
//如果一个数列以步长5进行了排序然后再以步长3进行排序，那么该数列不仅是以步长3有序，而且是以步长5有序，变得越来越有序，最后1步长进行排序（此时就是简单的插入排序了）
//Time Best:O(nlogn),worst and average: nlog^2 n(),这比最好的比较算法的O(n log n)要差一些。大约是n的1.5 到1.6次方, Space O(1)
//Instable
// 虽然是稳定的插入排序的改进，但是不稳定，因为分组的过程中相同的两个数不在一组，没有联系，各自交换的时候可能交换相对位置
void Shell_Sort(vector<int> &A,int begin,int end){
    int h = 1;
    while(h < LEN/3){//先将步长扩大为三的倍数的最大步长
        h = 3 * h + 1;
    }
    while(h >= 1){
        for(int i = h; i < LEN; ++i){//i都跑完后，代表每个列变得有序
            for(int j = i; j >= h && A[j] < A[j-h]; j-=h){//每列数各自间进行比较，每次循环都将列中的一个数往合适位置前进
                swap(A[j],A[j-h]);
            }
        }
        h /= 3;//缩短列的个数
    }
    //Print(A);
}


//分治思想，数组规模小到只有一个元素，不用排，对于已经排好的，合并。
/*基本操作：将一个大叔组平分成两个小数组，分别对两个小数组递归，再合并这两个排好序的小数组
 * 关键操作：怎么合并？
 *
 * Time(bset average medium):O(nlogn), Space :O(n) stable
 * */
void Merge_Sort(vector<int> &A,int begin,int end){
    if(begin < end){
        int q = (begin + end)/2;
        Merge_Sort(A,begin,q);
        Merge_Sort(A,q+1,end);
        Merge(A,begin,q,end);        //合并
    }
    else{
        return;;
    }
}

//用额外的空间，将两个小数组 中最小的数 放到 大数组中，该小数组减一，直到小数组取完为止
void Merge(vector<int> &A,int begin,int medium, int end){
    int n1 = medium - begin +1;//左边数组的长度，0 ~ medium,还要取得到medium, 实际长度medium+1
    int n2 = end - medium; //o-base
    vector<int> L(n1+1);
    vector<int> R(n2+1);
    for(int i = 0; i < n1; ++i ){//相对位置不会变
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

//分治思想：对于n个元素的数组A, 每次把数组分成两部分: 部分小于等于A[n-1], 另部分大于A[n-1], 那么A[n-1]
//就可以放在这两个数组的中间. 然后递归地快速排序这两个较小规模的数组.
void Quick_Sort(vector<int> &A,int begin,int end){
    if(begin < end){
        int q = Partition_end(A,begin,end);//关键在于这个划分
        Quick_Sort(A,begin,q-1);
        Quick_Sort(A,q+1,end);
    }
}
//两种Partition
//教材上：将第一个数作为pivot
int Partition_begin(vector<int> &A,int begin,int end){//end 就是数组下标
    int pivot = A[begin];//以数组的第一个元素做为 枢纽
    while(begin < end){// 第一次交换时 第一个元素位置就被覆盖，从此整个数组中空出一个位置是pivot 记录的那个值的位置（枢纽pivot一直在游荡，并没有固定的位置 ）
        while(begin < end && A[end] >= pivot){//试图在右半边找到一个比枢纽小的元素，跳出循环
            -- end;
        }
        A[begin] = A[end];//和对面的begin交换位置,将这个比枢纽小的元素安置到左边

        while(begin < end && A[begin] <= pivot){//试图在左半边找到一个比枢纽大的元素，跳出循环
            ++ begin;
        }
        A[end] = A[begin];//和对面的begin交换位置,将这个比枢纽大的元素安置到右边

    }
    A[end] = pivot;//此时end = begin， 将中间的位置 给 pivot
    return end;
}

//法2： 以i j 为分界线分割两部分
int Partition_end(vector<int> &A,int begin,int end){
    int pivot = A[end];//以数组的第一个元素做为 枢纽
    int i = begin-1;//比pivot小的数组中的最后一个数
    int j = i+1;//比pivot大的数组中的最后一个数的后面一个数：即待排的第一个数
    //开始i 指向 第一个 数组 元素的前一个位置， j 指向第一个数组元素
    //i + 1 = 比pivot大的数组中的 第一个数
    while(j <= end - 1){//即begin <= end 即j 跑到最后去了
        if(A[j] <= pivot){//j 当前元素比pivot 小，要将当前元素j归为左边，此时i指向比pivot小的数组中的最后一个数
            i++;//紧接着i 的后面的一个数 是 比pivot大的数组中的第一个数
            swap(A[i],A[j]);
        }
        j++;//下一个元素
    }

    //将pivot放到合适的位置
    A[end] = A[i+1];//本来最后一个位置放的是pivot，现在换成A[i+1] (比pivot大的数组中的第一个数)
    A[i+1] = pivot;
    return  i+1;//pivot的位置
}


void Heap_Sort(vector<int> &A,int begin,int end);
/********************************************以上为基于比较的排序*************************************************/
 /**************************************证明基于比较的排序的复杂度下限O（nlogn）*************************************/
/************************************以下为线性 复杂度的排序算法********************************/

void Counting_Sort(vector<int> &A,int begin,int end){

}

void Radin_Sort(vector<int> &A,int begin,int end){

}

#endif //ALLSORT_ALLSORT_H
