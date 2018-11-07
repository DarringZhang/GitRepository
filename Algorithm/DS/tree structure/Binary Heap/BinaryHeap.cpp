//
// Created by Darring Zhang on 2018/11/7.
//
#include <iostream>
#include "BinaryHeap.h"
using namespace std;
int main(){
    BinaryHeap heap;
    cout<<"the size of creating your array :"<<endl;
    int size;
    cin>>size;
    cout<<"input these values: ";
    for(int i=1;i<size+1;i++){
        cin>>heap.A[i];
        heap.effective++;
    }

    int  op;
    int flag = 1;
    while(flag){
        cout<<"0.Build_Max_Heap"<<endl;
        cout<<"1.Heap_Extract_Max()"<<endl;
        cout<<"2.Max_Heap_Insert(int key)"<<endl;
        cout<<"3.HeapSort()"<<endl;
        cout<<"4.quit"<<endl;
        cin>>op;
        switch (op){
            case 0:{
                heap.Build_Max_Heap();
                cout<<"build finished"<<endl;
                heap.print();
                break;
            }
            case 1:{
                cout<<"the max is: "<< heap.Heap_Extract_Max()<<endl;
                cout<<"the rest heap is:";
                heap.print();
                break;
            }
            case 2:{
                cout<<"insert :";
                int key;
                cin>>key;
                heap.Max_Heap_Insert(key);
                cout<<"insert finished"<<endl;
                heap.print();
                break;
            }
            case 3:{
                heap.HeapSort();
                heap.print();
                break;
            }
            case 4:{
                flag = 0;
                break;
            }
            default:{
                cout<<"error!"<<endl;
                break;
            }

        }
    }

    return 0;
}

