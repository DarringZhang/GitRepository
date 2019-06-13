
//编码方式：GBK

#include <bits/stdc++.h>
using namespace std;

typedef int State[9];  //定义9个元素的"状态",代表一种节点
const int  maxstate = 1000000;
State st[maxstate],goal;  //st 为状态数组，所有的状态都保存在这里，最多能保存1000000个状态
int dist[maxstate];      //距离数组；
int fa[maxstate];       //打印方案所需的父亲编号节点。

set<int> vis;

void init_lookup_table(){
    vis.clear();
}

int try_to_insert(int s){
    int v = 0;
    for(int i = 0; i < 9; ++i) {   //把状态转换成9位十进制数
        v = v * 10 + st[s][i];
    }

    if(vis.count(v)){
        return 0;
    }

    vis.insert(v);
    return 1;
}

// 对于一个节点的dx和dy,要么上，要么下，要么左，要么右（将dx，dy结合起来看）
const int dx[] = {-1,1,0,0};
const int dy[] = {0,0,-1,1};

int dfs(){
    init_lookup_table();            //初始化查找表
    int front = 1,rear = 2;         //数组的头和尾。不定义0,0视作空

    //int flag=0 ;

    while(front < rear) {

        //cout<<"我是flag" << flag++ <<endl;

        State &s = st[front];      //"引用"简化代码,s为保存front号位置状态的临时数组。
        if (memcmp(goal, s, sizeof(s))== 0) {
            return front; //找到目标状态，返回这个状态在数组st的下标。
        }

        int z;
        for (z = 0; z < 9; z++) {
            if (!s[z]) { //找到0位置
                break;
            }
        }

        int x = z/3, y = z%3; //获取行列的编号（0~2），（技巧）将一维转化成二维坐标。

        for (int d = 0; d < 4; d++) { //寻找下一步移动的方案  上下左右的顺序
            int newx = x + dx[d];
            int newy = y + dy[d];

            int newz = newx * 3 + newy;  //呼应前面的  x = z/3,y = z%3
            if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {  //移动合法
                State &t = st[rear];
                memcpy(&t, &s, sizeof(s));   //s拷贝到t,拓展新节点

                t[newz] = s[z]; //交换0和第一个数字的位置
                t[z] = s[newz];

                dist[rear] = dist[front] + 1;  //更新节点的距离值

                if (try_to_insert(rear)) {      //成功拓展新节点，修改队尾指针
                    fa[rear] =front;
                    rear++;
                }
            }

        }

        front++;           //修改队首指针

    }
    return 0;
}

int main() {

    for(int i = 0; i < 9; ++i){
        scanf("%d",&st[1][i]); //起始状态
    }

    for(int i = 0; i < 9; ++i){
        scanf("%d",&goal[i]);  //目标状态
    }


    int ans = bfs();


    cout<<"搜索到第几个节点 : " <<ans <<endl;



    if(ans > 0){
        cout<<"最少需要移动的步数: " ;
        printf("%d\n",dist[ans]);

        cout<<"从叶子一直到根节点的移动路径为: " << endl;
        int print = dist[ans];
        int flag = ans;
        int cnt = 0;

        while(print--){
            cout<<"第"<<++cnt<<"组:"<<endl;
            State &t = st[flag];
            for(int i = 0; i < 9; ++i){
                printf("%d ",t[i]);  //目标状态
                if((i+1)%3 == 0){
                    cout<<endl;
                }
            }

            cout<<endl;
            flag = fa[flag];

        }

    }
    else{
        printf("无解\n");
    }

    return 0;
}