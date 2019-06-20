
#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

typedef struct Station {
    int a[9];
    int deep;
    struct Station *father;
}State;


State goal,st;

queue<State> Q;
vector <State>  box;


set<int> vis;
void init_lookup_table(){
    vis.clear();
}


int get_val(State s){
    int v = 0;
    for(int i = 0; i < 9; ++i) {   //把状态转换成9位十进制数
        v = v * 10 + s.a[i];
    }
    return v;
}


int try_to_insert(State s){
    int v = 0;
    for(int i = 0; i < 9; ++i) {   //把状态转换成9位十进制数
        v = v * 10 + s.a[i];
    }

    if(vis.count(v)){
        return 0;
    }

    vis.insert(v);
    return 1;
}


void Print(State t){

    for(int i = 0; i < 9; ++i){
        printf("%d ",t.a[i]);  //目标状态
        if((i+1)%3 == 0){
            cout<<endl;
        }
    }

    cout<<endl;
}


// 对于一个节点的dx和dy,要么上，要么下，要么左，要么右（将dx，dy结合起来看）
const int dx[] = {-1,1,0,0};
const int dy[] = {0,0,-1,1};
int cost_tree_bfs(){
    while(!Q.empty()) {
        State s = Q.front();
        Q.pop();


        if (memcmp(goal.a, s.a, sizeof(s.a))== 0) {
            cout<<"找到目标状态，以下是输出结果："<<endl;

            State *kk = s.father;
            int cnt = 0;
            if(kk==NULL){
                cout<<"sfasuihciausdv "<<endl;
            }
            //根据father 打印路径
            while(kk!= NULL){

                cout<<"第"<<++cnt<<"组:"<<endl;
                Print(*kk);
                kk = kk->father;
            }

            return 1; //找到目标状态，结束
        }


        int z;
        for (z = 0; z < 9; z++) {
            if (!s.a[z]) { //找到0位置
                break;
            }
        }

        int x = z/3, y = z%3;

        for (int d = 0; d < 4; d++) { //寻找下一步移动的方案  上下左右的顺序
            int newx = x + dx[d];
            int newy = y + dy[d];

            int newz = newx * 3 + newy;
            if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {  //移动合法
                State t = s;
                memcpy(&t, &s, sizeof(s));   //s拷贝到t,拓展新节点


                t.a[newz] = s.a[z]; //移动0
                t.a[z] = s.a[newz];


                if (try_to_insert(t)) {      //成功拓展新节点

                    t.deep = s.deep+1;
                    t.father = &s;

                    Q.push(t);
                    box.push_back(t);

                }

            }
        }

    }
    return 0;

}





int main(int argc,char** argv){

    freopen("local.txt","r",stdin);

    for(int i = 0; i < 9; ++i){
        scanf("%d",&st.a[i]); //起始状态

    }

    Print(st);

    for(int i = 0; i < 9; ++i){
        scanf("%d",&goal.a[i]); //起始状态
    }

    Print(goal);

    //初始化查找表
    init_lookup_table();

    Q.push(st);
    box.push_back(st);
    st.father = NULL;

    int ans = cost_tree_bfs();

    if(ans == 0){
        cout<<"无解"<<endl;
    }

    return 0;
}