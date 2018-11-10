#include <iostream>
#include "Huffman.h"
#include "MinHeap.h"
int main() {

    /*  流程：
     * 构建哈夫曼树（包含构建存储哈夫曼结点的小顶堆）->哈夫曼树测试->哈夫曼树实现哈夫曼编码
     * */

    Huffman huff;
    huff.create_huffman_tree();
    huff.preOrder(huff.GetRoot());
    huff.inOrder(huff.GetRoot());
    huff.postOrder(huff.GetRoot());
    huff.Huffman_code();
    return 0;
}