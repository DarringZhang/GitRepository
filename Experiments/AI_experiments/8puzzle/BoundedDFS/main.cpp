
//???????GBK

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
    for(int i = 0; i < 9; ++i) {   //?????????9��???????
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
    cout<<"????"<<t.deep<<endl;
    for(int i = 0; i < 9; ++i){
        printf("%d ",t.a[i]);  //?????
        if((i+1)%3 == 0){
            cout<<endl;
        }
    }

    cout<<endl;
}


// ???????????dx??dy,?????????????????????dx??dy???????????
//const int dx[] = {-1,1,0,0};
//const int dy[] = {0,0,-1,1};  //??��
const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};



int cnt =0;
int nt = 0;//?????????????
int flag = 0;
void dfs(){

        while(!sstack.empty()) {

         //   cout<<"sstack.size(): "<<sstack.size()<<endl;
            //???????????
            State s = sstack.top();
            sstack.pop();

            path[++cnt] = s;


            //?????????????
            cout<<"??"<<++nt<<"??"<<endl;
            Print(s);



            if (memcmp(goal.a, s.a, sizeof(s.a))== 0) {
                cout<<"????????????????????????"<<endl;

                int count = 0;

                State Temp = path[s.father];
                while(Temp.father != -1){
                    cout<<"??"<<++count<<"??"<<endl;
                    Print(Temp);
                    Temp = path[Temp.father];
                }

                flag = 1;
                return; //??????????????
            }


          if(s.deep > 6){
                continue;
            }


            int z;
            for (z = 0; z < 9; z++) {
                if (!s.a[z]) { //???0��??
                    break;
                }
            }

            int x = z/3, y = z%3;




            for (int d = 0; d < 4; d++) { //????????????????  ????????????
                int newx = x + dx[d];
                int newy = y + dy[d];

                int newz = newx * 3 + newy;
                if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {  //??????
                    State t = s;
                    memcpy(&t, &s, sizeof(s));   //s??????t,???????


                    t.a[newz] = s.a[z]; //???0
                    t.a[z] = s.a[newz];


                    if (try_to_insert(t)) {      //??????????

//                    for(set<int>:: iterator it = vis.begin(); it!=vis.end(); it++){
//                        cout<<*it<<"\t";
//                    }

                        t.deep = s.deep+1;
                        t.father = cnt;  //t???? father ??path ?????cnt ?????
                        sstack.push(t);

                         //v.push_back(t); //????????????????????????????????????????????????????????��???????��??????????��??
                        // dfs(); ??????????????dfs??

                    }

                }


            }
        }



}

int main() {
    freopen("local.txt","r",stdin);

    for(int i = 0; i < 9; ++i){
        scanf("%d",&st.a[i]); //?????

    }

    Print(st);


    for(int i = 0; i < 9; ++i){
        scanf("%d",&goal.a[i]); //?????
    }

    Print(goal);



    //??????????
    init_lookup_table();

    st.deep = 1;
    st.father = -1;
    vis.insert(get_val(st));
    sstack.push(st);


    dfs();

    if(flag == 0){
        cout<<endl;
        cout<<"????????????5????????��????????"<<endl;
    }

    return 0;
}