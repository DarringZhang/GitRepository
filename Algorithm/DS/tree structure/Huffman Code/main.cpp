#include <iostream>
#include "Huffman.h"
#include "MinHeap.h"
int main() {

    /*  Á÷³Ì£º
     * ¹¹½¨¹ş·òÂüÊ÷£¨°üº¬¹¹½¨´æ´¢¹ş·òÂü½áµãµÄĞ¡¶¥¶Ñ£©->¹ş·òÂüÊ÷²âÊÔ->¹ş·òÂüÊ÷ÊµÏÖ¹ş·òÂü±àÂë
     * */

    Huffman huff;
    huff.create_huffman_tree();
    cout<<"Ç°Ğò´òÓ¡¹ş·òÂüÊ÷:";
    huff.preOrder(huff.GetRoot());
    cout<<endl;
    cout<<"ÖĞĞò´òÓ¡¹ş·òÂüÊ÷:";
    huff.inOrder(huff.GetRoot());
    cout<<endl;
    cout<<"ºóĞò´òÓ¡¹ş·òÂüÊ÷:";
    huff.postOrder(huff.GetRoot());
    cout<<endl;
    cout<<"Ç°Ğò´òÓ¡¹ş·òÂü±àÂë:"<<endl;
    huff.Huffman_code();
    cout<<endl;
    return 0;
}