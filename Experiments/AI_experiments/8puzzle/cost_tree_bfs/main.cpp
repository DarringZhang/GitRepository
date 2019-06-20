
#include <bits/stdc++.h>
#include <cstdio>
using namespace std;


//多叉树的存取
typedef struct Station {
    int a[9];
    int deep;
    struct Station *father;
    vector<Station*> vson;
    bool operator < (const Station &other) const{      //注意，优先队列调用返回大根堆，而这里要取代价最小的
        return deep > other.deep;
    }
}State;


State *goal = new State;
State *st = new State;
State *root = new State;    //root 节点。  必须是存完  拓展完其的三个子节点之后，  才能完整赋值给root ，这时拥有三个子节点的root 才完整
priority_queue<State> Q ;



set<int> vis;
void init_lookup_table(){
    vis.clear();
}


//此处用优先队列重载小于号，代替，每次取top
//State find_min_cost(){
//    State mi = v[0];
//    for(int i = 1; i < v.size(); i++){
//        if(mi.deep > v[i].deep){
//            mi = v[i];
//        }
//    }
//    return mi;
//}


//把状态转换成9位十进制数
int get_val(State *s){
    int v = 0;
    for(int i = 0; i < 9; ++i) {
        v = v * 10 + s->a[i];
    }
    return v;
}


//判断该节点可不可以拓展
int try_to_insert(State *s){
    int v = get_val(s);

    if(vis.count(v)){
        return 0;
    }

    vis.insert(v);
    return 1;
}


void Print(State *t){
    cout<<"深度为" << t->deep<<endl;
    for(int i = 0; i < 9; ++i){
        printf("%d ",t->a[i]);  //目标状态
        if((i+1)%3 == 0){
            cout<<endl;
        }
    }

    cout<<endl;
}


void delete_tree(State *t){
    while(t!=NULL){
        for(int i = 0; i < t->vson.size(); i++){
            delete_tree(t->vson[i]);
        }
        delete t;
    }


}

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};


int nt = 0;//测试中途输出结果
bool is_root = false;
stack<State> path;

int cost_tree_bfs(){
    while(!Q.empty()) {
        State *s = new State;   //注意即使是临时变量也要new出空间，因为下面pop 掉后若用指针会丢
        *s = Q.top();

        //cout<< s->deep;   不确定是大根堆还是小根堆，测试一下。！！！！！！！！


        Q.pop();   //待会儿会在test代码中测试一下,这里pop 含有delete,!!  但是后来的delete 全部树节点时没关系，因为是复制品

        //测试中途输出结果
        cout<<"第"<<++nt<<"组"<<endl;
        Print(s);

        if (memcmp(goal->a, s->a, sizeof(s->a))== 0) {
            int cnt = 0;
            State *kk = s->father;
            while(kk != NULL){
                path.push(*kk);
                kk = kk->father;
            }

            cout<<"找到目标状态，以下是输出结果："<<endl;

            while(!path.empty()){
                cout<<"第"<<++cnt<<"组:"<<endl;
                Print(&path.top());
                path.pop();
            }


            return 1;    //找到目标状态，结束
        }


        int z;
        for (z = 0; z < 9; z++) {
            if (!s->a[z]) { //找到0位置
                break;
            }
        }

        int x = z/3, y = z%3;

        for (int d = 0; d < 4; d++) { //寻找下一步移动的方案  上下左右的顺序
            int newx = x + dx[d];
            int newy = y + dy[d];

            int newz = newx * 3 + newy;
            if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {  //移动合法

                State *t = new State;

         //      memcpy(t, s, sizeof(s));   //s拷贝到t,拓展新节点，不会用就不要用

                for(int i = 0; i < 9 ;i++){
                    t->a[i] = s->a[i];
                }
                t->deep = s->deep;


                t->a[newz] = s->a[z];  //移动0
                t->a[z] = s->a[newz];


                if (try_to_insert(t)) {      //成功拓展新节点

                    t->deep = s->deep +1;
                    t->father = s;
                    s->vson.push_back(t);
                    Q.push(*t);
                }
                else{
                    delete t;
                }

            }
        }

        if(!is_root){   //将完整的root 存起来，便于从根节点出发打印路径
            root = s;
            is_root = true;
        }

    }


    return 0;

}




int main(int argc,char** argv){

    freopen("local.txt","r",stdin);

    for(int i = 0; i < 9; ++i){
        scanf("%d",&st->a[i]); //起始状态

    }

    st->father = NULL;
    st->deep = 1;
    Print(st);

    for(int i = 0; i < 9; ++i){
        scanf("%d",&goal->a[i]); //起始状态
    }
    goal->deep = 1;
    Print(goal);

    //初始化查找表
    init_lookup_table();
    //给查找表赋初值
    vis.insert(get_val(st));





    Q.push(*st);

    int ans = cost_tree_bfs();


    if(ans == 0){
        cout<<"无解"<<endl;
    }


    delete_tree(root);
    return 0;
}