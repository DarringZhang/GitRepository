#include <iostream>
#include "Huffman.h"
#include "MinHeap.h"



int main() {

    Huffman huff;
    huff.create_huffman_tree();
    //cout<<"ǰ���ӡ��������:";
    //huff.preOrder(huff.GetRoot());
    // cout<<"�����ӡ����������:"<<endl;
    huff.Huffman_code();
    for(int i = 1; i <= huff.Heap.number_of_leaves; i++){
        cout<<huff.Heap.Print[i]->c<<":"<<huff.Heap.Print[i]->code<<endl;
    }
    cout<<endl;



    cout<<"������һ���ɸ����ַ���ɵ����ģ��������Ӧ�ı��룺";
    string word;
    cin>>word;
    huff.Huffman_Encoding(word);




    cout<<"������һ�����룬������룺";
//    string coding;
//    cin>>coding;
      huff.Huffman_Decoding(huff.AllTheCodes);


    return 0;
}
