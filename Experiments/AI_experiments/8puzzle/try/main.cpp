
//编码方式：GBK

#include <bits/stdc++.h>
using namespace std;

typedef int State[9];  //定义9个元素的"状态",代表一种节点

State goal,st;
stack<State> sstack;

//queue<State >ssque;
//为什么 sstack 不能push操作
set<int> vis;
void init_lookup_table(){
    vis.clear();
}


int main() {
    for(int i = 0; i < 9; ++i){
        scanf("%d",&st[i]); //起始状态
    }

    for(int i = 0; i < 9; ++i){
        scanf("%d",&goal[i]);  //目标状态
    }

    sstack.push(st);

   // dfs();

    return 0;
}