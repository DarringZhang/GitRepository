
//编码方式：GBK

#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

typedef struct Station{
    int a[9];
    int deep;
    int father;
}State;

const int  maxstate = 1000000;
State path[maxstate];

State goal,st;
stack<State> sstack;




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
    int v = get_val(s);

    if(vis.count(v)){
        return 0;
    }

    vis.insert(v);
    return 1;
}


void Print(State t){
    cout<<"深度为"<<t.deep<<endl;
    for(int i = 0; i < 9; ++i){
        printf("%d ",t.a[i]);  //目标状态
        if((i+1)%3 == 0){
            cout<<endl;
        }
    }

    cout<<endl;
}



const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};



int cnt =0;
int nt = 0;//测试中途输出结果
int flag = 0;
void dfs(){

    while(!sstack.empty()) {

        //   cout<<"sstack.size(): "<<sstack.size()<<endl;
        //取出第一个节点
        State s = sstack.top();
        sstack.pop();

        path[++cnt] = s;


        //测试中途输出结果
        cout<<"第"<<++nt<<"组"<<endl;
        Print(s);



        if (memcmp(goal.a, s.a, sizeof(s.a))== 0) {
            cout<<"找到目标状态，以下是输出结果："<<endl;

            int count = 0;

            State Temp = path[s.father];
            while(Temp.father != -1){
                cout<<"第"<<++count<<"组"<<endl;
                Print(Temp);
                Temp = path[Temp.father];
            }

            flag = 1;
            return; //找到目标状态，结束
        }


//        if(s.deep > 6){
//            continue;
//        }


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
                    t.father = cnt;  //t节点的 father 是path 里面第cnt 个节点
                    sstack.push(t);

                }

            }


        }
    }



}

int main() {
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

    st.deep = 1;
    st.father = -1;
    vis.insert(get_val(st));
    sstack.push(st);


    dfs();

//    if(flag == 0){
//        cout<<endl;
//        cout<<"限制搜索深度为5的情况下，未找到目标状态"<<endl;
//    }

    return 0;
}