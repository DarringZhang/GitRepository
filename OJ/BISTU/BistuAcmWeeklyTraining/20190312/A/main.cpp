#include <bits/stdc++.h>
using namespace std;

int main() {
    int h1,m1,h2,m2;
    char ch;
    cin>>h1>>ch>>m1;
    cin>>h2>>ch>>m2;
    int min1 = m1 + 60*h1;
    int min2 = m2 + 60*h2;
    int sub;

    if(h1==h2&&m2==m1){
        if(m1<10){
            cout<<h1+12<<":0"<<m1;
        }
        else{
            cout<<h1+12<<m1;
        }

    }
    else if(min1< min2){
        sub = (min2-min1)/2;
        int h,min;
        h = sub/60;

        min = sub%60;
        if(h+h1 < 10){
            cout<<0<<h+h1<<":";
        }
        else{
            cout<<h+h1<<":";
        }
        if(min+m1<10){
            cout<<0<<m1+min;
        }
        else{
            cout<<m1+min;
        }

    }
    else if(min1> min2){
        sub = (((min2- (min1 - 24*60)))%720)/2;
        int h,min;
        h = sub/60;
        min = sub%60;

        if(m2-min < 0){
            if(h2-h -1< 10){
                cout<<0<<h2-h-1<<":";
            }
            else{
                cout<<h2-h-1<<":";
            }

            if(m2+60-min<10){
                cout<<0<<m2+60-min;
            }
            else{
                cout<<m2+60-min;
            }

        }
        else{
            if(h2-h < 10){
                cout<<0<<h2-h<<":";
            }
            else{
                cout<<h2-h<<":";
            }

            if(m2-min<10){
                cout<<0<<m2-min;
            }
            else{
                cout<<m2-min;
            }
        }

    }


    return 0;
}