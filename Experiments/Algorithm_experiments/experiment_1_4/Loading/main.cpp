#include <bits/stdc++.h>
using namespace std;

struct box {
    int value;
    int idx;

    bool operator<(const box &s1) const {
        return value < s1.value;
    };
};
    void Loading(int x[], box w[], int c, int n, int *t)
//x[ ]存储集装箱的选中情况， w[ ]存储集装箱的编号
// c 为轮船的剩余载重量， n 为集装箱的个数， t 为排序后每个集装箱原来的序号。
    {
        sort(w, w + n);  //将n个集装箱按照重量w非减序排序
        for (int i = 0; i < n; i++) {
            t[i] = w[i].idx;
        }

        cout<<"集装箱按重量排序的编号：";
        for (int i = 0; i < n; i++) {
            cout<< t[i]<<" ";
        }
        cout<<endl;

        for (int i = 1; i <= n; i++)
            x[i] = 0;
        for (int i = 1; i <= n && w[t[i]].value <= c; i++) {
            x[t[i]] = 1;
            c = c - w[t[i]].value;
        }
    }


    int main() {
        int x[100] = {0};
        int c = 19;
        int n = 5;
        box w[5];
        int t[100] = {0};

        for (int i = 0; i < 5; ++i) {
            w[i].idx = i;
        }

        w[0].value = 5;
        w[1].value = 3;
        w[2].value = 8;
        w[3].value = 6;
        w[4].value = 9;


        Loading(x, w, c, n, t);

        for (int i = 0; i < 5; ++i) {
            cout << x[i] << " ";
        }

        return 0;
    }
