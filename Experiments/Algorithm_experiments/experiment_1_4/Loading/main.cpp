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
//x[ ]�洢��װ���ѡ������� w[ ]�洢��װ��ı��
// c Ϊ�ִ���ʣ���������� n Ϊ��װ��ĸ����� t Ϊ�����ÿ����װ��ԭ������š�
    {
        sort(w, w + n);  //��n����װ�䰴������w�Ǽ�������
        for (int i = 0; i < n; i++) {
            t[i] = w[i].idx;
        }

        cout<<"��װ�䰴��������ı�ţ�";
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
