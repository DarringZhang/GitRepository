#include"BST.h"
#include<time.h>
#include"Avltmp.h"
#include<vector>
#include<algorithm>
using namespace std;
struct dat {
    int _key;
    int _idx;
};
//????sort?§Ö?§³???
bool operator < (const dat& first, const dat& other) {
    return first._key < other._key;
}
//??????????ï…??????????????
//???????????????????????
void randArrray1(int *a,int size) {
    srand((unsigned)time(NULL));//?????¦Ä???????????
    vector<dat> tmp;
    tmp.resize(size);
    for (int i = 0; i < size; ++i) {
        tmp[i]._key = rand() % 100;
        tmp[i]._idx = i;
    }
    sort(tmp.begin(), tmp.end());
    for (int i = 0; i <tmp.size();i++) a[i] = tmp[i]._idx;
}
void delay(int sec)
{
    time_t start_time, cur_time; // ????????
    time(&start_time);
    do {
        time(&cur_time);
    } while ((cur_time - start_time) < sec);
}


int main() {
    BST<int> *h = new BST<int>[1000000];
    AVL<int> *ah = new AVL<int>[100000];
    int a[100000];
    int b[100000];
    //????????????10000?????§Ó???
    randArrray1(b,100000);
    Node<int> *p;
    AVLTreeNode<int> *q;
    clock_t s;
    clock_t f;
    srand((int)time(0));
    cout << "*****************************"<<"???BST??AVL?????????????"<<"************************************" << endl;
    cout << "??????????????????" << endl;
    cout << "--------------------------------" << endl;
    for(int i=0;i<10;i++){
        randArrray1(a, 1000000);
        s = clock();
        h->IntBST(a, 1000000);
        f = clock();
        cout <<"test"<<i+1<<"??"<<endl<< "Build BST: " << f - s <<"ms ";
        cout << "BST?????" << h->getHeight(h->getRoot()) <<endl;
        s = clock();
        ah->AVL_creat(a, 1000000, ah->getroot());
        f = clock();
        cout << "Build AVL: " << f - s << "ms ";
        cout << "AVL?????" << ah->tree_height(ah->getroot()) << endl;
        //h->PreTralve_stack(h->getRoot());
        s = clock();
        //???BST????100000??
        for (int j = 0; j < 100000; j++) {
            p = h->Find(h->getRoot(),b[j] );
            //cout << p->data << " ";
        }
        f = clock();//???????10?¦Â?????????
        cout << "......";
        cout <<"BST????100000?¦Å??????"<< f - s << "ms" << endl;
        s = clock();
        //???AVL????100000??
        for (int j = 0; j < 100000; j++) {
            q = ah->Find(ah->getroot(), b[j]);
            //cout << q->key << " ";
        }
        f = clock();
        cout << "......";
        cout << "AVL????100000?¦Å??????" << f - s << "ms" << endl;
        h->Destroy_stack();
        ah->Destroy_stack();
        delay(2);
    }
}

