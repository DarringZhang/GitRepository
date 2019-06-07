//递归方法

#include <iostream>
using namespace std;

void Swap(int &a, int &b){
    int t = a;
    a = b;
    b = t;
}

void Perm(int list[],int k, int m){ //排列list[k:m]的所有数
    if(k == m){ //左边界=右边界，边界条件，前面都排列好了
        for(int i = 0; i <= m; ++i){  //直接打印
            cout << list[i]<<" ";
        }
        cout<<endl;
    }
    else{
        for(int i = k; i <= m; i ++){
            Swap(list[k],list[i]); //将后面的元素和第一个元素进行交换（一趟换一个）
            Perm(list,k+1,m);
            Swap(list[k],list[i]);
        }
    }
}


int main() {
    int list[] = {1,2,3,4};
    Perm(list,0,3);
    return 0;
}