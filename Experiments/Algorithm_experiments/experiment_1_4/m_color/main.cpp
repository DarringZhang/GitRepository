#include <bits/stdc++.h>
#include "Color.h"
using namespace std;

int main() {
    int n = 4;
    int m = 3;
    int a[4][4]={{1,1,0,1},
                 {1,1,1,0},
                 {0,1,1,1},
                 {1,0,1,1}};
    mColoring(n,m,a);
    return 0;

}