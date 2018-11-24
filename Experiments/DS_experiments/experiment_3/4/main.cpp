#include <iostream>
#include "Huffman.h"
#include "MinHeap.h"



int main() {

    Huffman huff;
    huff.create_huffman_tree();
    //cout<<"前序打印哈夫曼树:";
    //huff.preOrder(huff.GetRoot());
    // cout<<"层序打印哈夫曼编码:"<<endl;
    huff.Huffman_code();
    for(int i = 1; i <= huff.Heap.number_of_leaves; i++){
        cout<<huff.Heap.Print[i]->c<<":"<<huff.Heap.Print[i]->code<<endl;
    }
    cout<<endl;



    cout<<"请输入一串由给定字符组成的明文，计算出对应的编码：";
    string word;
    cin>>word;
    huff.Huffman_Encoding(word);




    cout<<"请输入一串编码，计算解码：";
//    string coding;
//    cin>>coding;
      huff.Huffman_Decoding(huff.AllTheCodes);


    return 0;
}
