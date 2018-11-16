#include <iostream>
using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

//森林的存储方式：1.双亲法

#include <vector>
struct Node{
    char data;
    int parent;//树根的parent = -1;
};

struct Tree{
    vector <Node> nodes;
    int root,size;//根的位置和结点数
};

//左子右兄法：假想有一个虚拟根，转化为二叉树，再去虚拟根
/*森林的应⽤, 并查集(⽤双亲表⽰法实现)
       并查：查找元素a b是否在同一个集合中，如果不在，合并
 */

int find(Tree S,int i){//查找S集合中i所在子集的根

}

void Merge(Tree &S,int i,int j){

}