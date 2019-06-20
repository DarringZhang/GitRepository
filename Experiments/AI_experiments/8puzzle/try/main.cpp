
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
    for(int i = 0; i < 9; ++i) {   //��״̬ת����9λʮ������
        v = v * 10 + s.a[i];
    }
    return v;
}


int try_to_insert(State s){
    int v = 0;
    for(int i = 0; i < 9; ++i) {   //��״̬ת����9λʮ������
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
        printf("%d ",t.a[i]);  //Ŀ��״̬
        if((i+1)%3 == 0){
            cout<<endl;
        }
    }

    cout<<endl;
}


// ����һ���ڵ��dx��dy,Ҫô�ϣ�Ҫô�£�Ҫô��Ҫô�ң���dx��dy�����������
const int dx[] = {-1,1,0,0};
const int dy[] = {0,0,-1,1};
int cost_tree_bfs(){
    while(!Q.empty()) {
        State s = Q.front();
        Q.pop();


        if (memcmp(goal.a, s.a, sizeof(s.a))== 0) {
            cout<<"�ҵ�Ŀ��״̬����������������"<<endl;

            State *kk = s.father;
            int cnt = 0;
            if(kk==NULL){
                cout<<"sfasuihciausdv "<<endl;
            }
            //����father ��ӡ·��
            while(kk!= NULL){

                cout<<"��"<<++cnt<<"��:"<<endl;
                Print(*kk);
                kk = kk->father;
            }

            return 1; //�ҵ�Ŀ��״̬������
        }


        int z;
        for (z = 0; z < 9; z++) {
            if (!s.a[z]) { //�ҵ�0λ��
                break;
            }
        }

        int x = z/3, y = z%3;

        for (int d = 0; d < 4; d++) { //Ѱ����һ���ƶ��ķ���  �������ҵ�˳��
            int newx = x + dx[d];
            int newy = y + dy[d];

            int newz = newx * 3 + newy;
            if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {  //�ƶ��Ϸ�
                State t = s;
                memcpy(&t, &s, sizeof(s));   //s������t,��չ�½ڵ�


                t.a[newz] = s.a[z]; //�ƶ�0
                t.a[z] = s.a[newz];


                if (try_to_insert(t)) {      //�ɹ���չ�½ڵ�

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
        scanf("%d",&st.a[i]); //��ʼ״̬

    }

    Print(st);

    for(int i = 0; i < 9; ++i){
        scanf("%d",&goal.a[i]); //��ʼ״̬
    }

    Print(goal);

    //��ʼ�����ұ�
    init_lookup_table();

    Q.push(st);
    box.push_back(st);
    st.father = NULL;

    int ans = cost_tree_bfs();

    if(ans == 0){
        cout<<"�޽�"<<endl;
    }

    return 0;
}