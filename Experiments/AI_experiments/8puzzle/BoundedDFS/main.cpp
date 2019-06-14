
//编码方式：GBK

#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

typedef struct Station{
    int a[9];
    int deep;
}State;


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


//存取路径
vector<State> v;

int cnt =0;
int flag = 0;
void dfs(){
    if(flag == 0){
        //cnt++;
        //if (cnt%5==0) cout<<"curcnt: "<<cnt<<endl;


        while(!sstack.empty()) {

         //   cout<<"sstack.size(): "<<sstack.size()<<endl;
            //取出第一个节点
            State s = sstack.top();
            sstack.pop();


            if (memcmp(goal.a, s.a, sizeof(s.a))== 0) {
                cout<<"找到目标状态，以下是输出结果："<<endl;

                for(int i=(int)v.size()-1; i>=0;i--){
                    Print(v[i]);
                }

                flag = 1;
                return; //找到目标状态，结束
            }


          if(s.deep > 4){
                return;
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

//                    for(set<int>:: iterator it = vis.begin(); it!=vis.end(); it++){
//                        cout<<*it<<"\t";
//                    }

                        t.deep = s.deep+1;
                        sstack.push(t);
                        v.push_back(t);
                        dfs();

                    }

                }


            }
            return;

        }

    }

    else{

        return;
    }

}

int main() {
   // freopen("local.txt","r",stdin);

    for(int i = 0; i < 9; ++i){
        scanf("%d",&st.a[i]); //起始状态

    }

    //Print(st);

    for(int i = 0; i < 9; ++i){
        scanf("%d",&goal.a[i]); //起始状态
    }

    //Print(goal);

    //初始化查找表
    init_lookup_table();

    v.push_back(st);
    vis.insert(get_val(st) );
    sstack.push(st);

    dfs();

    if(flag ==0){
        cout<<endl;
        cout<<"限制搜索深度为4的情况下，未找到目标状态"<<endl;
    }

    return 0;
}