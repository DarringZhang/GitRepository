#include <iostream>
#include "Huffman.h"
#include "MinHeap.h"
int main() {

    /*  ���̣�
     * �����������������������洢����������С���ѣ�->������������->��������ʵ�ֹ���������
     * */

    Huffman huff;
    huff.create_huffman_tree();
    cout<<"ǰ���ӡ��������:";
    huff.preOrder(huff.GetRoot());
    cout<<endl;
    cout<<"�����ӡ��������:";
    huff.inOrder(huff.GetRoot());
    cout<<endl;
    cout<<"�����ӡ��������:";
    huff.postOrder(huff.GetRoot());
    cout<<endl;
    cout<<"ǰ���ӡ����������:"<<endl;
    huff.Huffman_code();
    cout<<endl;
    return 0;
}