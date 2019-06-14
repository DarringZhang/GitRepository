
//���뷽ʽ��GBK

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


//��ȡ·��
vector<State> v;

int cnt =0;
int flag = 0;
void dfs(){
    if(flag == 0){
        //cnt++;
        //if (cnt%5==0) cout<<"curcnt: "<<cnt<<endl;


        while(!sstack.empty()) {

         //   cout<<"sstack.size(): "<<sstack.size()<<endl;
            //ȡ����һ���ڵ�
            State s = sstack.top();
            sstack.pop();


            if (memcmp(goal.a, s.a, sizeof(s.a))== 0) {
                cout<<"�ҵ�Ŀ��״̬����������������"<<endl;

                for(int i=(int)v.size()-1; i>=0;i--){
                    Print(v[i]);
                }

                flag = 1;
                return; //�ҵ�Ŀ��״̬������
            }


          if(s.deep > 4){
                return;
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
        scanf("%d",&st.a[i]); //��ʼ״̬

    }

    //Print(st);

    for(int i = 0; i < 9; ++i){
        scanf("%d",&goal.a[i]); //��ʼ״̬
    }

    //Print(goal);

    //��ʼ�����ұ�
    init_lookup_table();

    v.push_back(st);
    vis.insert(get_val(st) );
    sstack.push(st);

    dfs();

    if(flag ==0){
        cout<<endl;
        cout<<"�����������Ϊ4������£�δ�ҵ�Ŀ��״̬"<<endl;
    }

    return 0;
}