#include <iostream>
#include"RB.h"
using namespace std;
int main() {
    RBTree *tree = RB_INIT();
    cout << "input the size of your tree:" <<endl;
    int size;
    cin>>size;
    cout << "input these keys" <<endl;
    int key;
    for(int i = 0; i<size; ++i){
        cin>>key;
        RB_INSERT(tree, key);
    }
    cout<<" pre"<<endl;
    rbtree_preorder(tree->root);
    cout<<" in"<<endl;
    rbtree_inorder(tree->root);
    cout<<" post"<<endl;
    rbtree_postorder(tree->root);
    return 0;
}