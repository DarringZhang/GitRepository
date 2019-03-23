#include<bits/stdc++.h>
using namespace std;
struct loop{
    int data;
    loop *next;
};

int main() {
    int n;
    int cnt = 0;
    int in;
    loop *t = new loop();
    loop *head = t;
    cin >> n;
    for(int i = 0; i < n-1; i++ ){
        cin >> in;
       t->data = in;
       t->next = new loop;
        t = t->next;
    }
    cin>>in;
    t->data = in;
    t->next  = head;


    loop *flag = head;
    int ma = 0;
    for(int i = 0; i < 2*n; ++i){
        if(flag->data==0){
            cnt = 0;
        }
        else{
            cnt++;
            ma = max(cnt,ma);
        }
        flag = flag ->next;
    }

    cout<<ma;

    t = head;
    for(int i = 0; i < n; i++ ){
        free(t);
        t = t->next;
    }
    return 0;
}
//优化：
/*
 int n;
 cin >> n;
 vector<int> a(n);
 for(int i =0 ; i < n; i++){
     cin >> a[i];
 }
 int result = 0;
 int len = 0;
 for(int i = 0; i < 2*n; i++ ){
     if(a[i%n]==1){   //利用取余 构成环，实现循环
         len ++;
         result = max(result, len);
     }
     else{
         len = 0;
     }
 }

 *
*/



