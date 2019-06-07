#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int a[100000];
int n;
int main(){
    n=4;

    bool fnext= true;

    for (int i=1;i<=n;i++) a[i]=i;
    int cnt=0;

    while(fnext){
        cnt++;
        for(int i=1;i<=n;i++) cout<<a[i]<<" ";
        cout<<endl;

        //找到第一个逆序中最大数的位置
        int left_pos=0;
        fnext=false;
        for(int i=n;i>=2;i--){
            for(int j=i;j>=1;j--){
                if(a[j]<a[i]) {
                    left_pos = max(left_pos,j);
                    fnext=true;
                    break;
                }
            }

        }

        //没有找到更大的字典序了
        if(!fnext) break;

        //第一个仅挨着大于上一个数
        int val=100000+111;
        int id=-1;
        for(int i=left_pos+1;i<=n;i++){
            if(a[i]>a[left_pos]){//大于要换的数但是是左边最小的
                if(a[i]<val){
                    val = a[i];
                    id = i;
                }
            }
        }

        int temp;
        temp = a[id];
        a[id] = a[left_pos];
        a[left_pos] = temp;


        //排序，将左边换成有序状态
        sort(a+left_pos+1,a+n+1);



    }
    cout<<"all cnt:"<<cnt<<endl;

    return 0;
}