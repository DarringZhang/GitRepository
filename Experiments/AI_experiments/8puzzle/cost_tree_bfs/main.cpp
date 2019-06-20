
#include <bits/stdc++.h>
#include <cstdio>
using namespace std;


//������Ĵ�ȡ
typedef struct Station {
    int a[9];
    int deep;
    struct Station *father;
    vector<Station*> vson;
    bool operator < (const Station &other) const{      //ע�⣬���ȶ��е��÷��ش���ѣ�������Ҫȡ������С��
        return deep > other.deep;
    }
}State;


State *goal = new State;
State *st = new State;
State *root = new State;    //root �ڵ㡣  �����Ǵ���  ��չ����������ӽڵ�֮��  ����������ֵ��root ����ʱӵ�������ӽڵ��root ������
priority_queue<State> Q ;



set<int> vis;
void init_lookup_table(){
    vis.clear();
}


//�˴������ȶ�������С�ںţ����棬ÿ��ȡtop
//State find_min_cost(){
//    State mi = v[0];
//    for(int i = 1; i < v.size(); i++){
//        if(mi.deep > v[i].deep){
//            mi = v[i];
//        }
//    }
//    return mi;
//}


//��״̬ת����9λʮ������
int get_val(State *s){
    int v = 0;
    for(int i = 0; i < 9; ++i) {
        v = v * 10 + s->a[i];
    }
    return v;
}


//�жϸýڵ�ɲ�������չ
int try_to_insert(State *s){
    int v = get_val(s);

    if(vis.count(v)){
        return 0;
    }

    vis.insert(v);
    return 1;
}


void Print(State *t){
    cout<<"���Ϊ" << t->deep<<endl;
    for(int i = 0; i < 9; ++i){
        printf("%d ",t->a[i]);  //Ŀ��״̬
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


int nt = 0;//������;������
bool is_root = false;
stack<State> path;

int cost_tree_bfs(){
    while(!Q.empty()) {
        State *s = new State;   //ע�⼴ʹ����ʱ����ҲҪnew���ռ䣬��Ϊ����pop ��������ָ��ᶪ
        *s = Q.top();

        //cout<< s->deep;   ��ȷ���Ǵ���ѻ���С���ѣ�����һ�¡�����������������


        Q.pop();   //���������test�����в���һ��,����pop ����delete,!!  ���Ǻ�����delete ȫ�����ڵ�ʱû��ϵ����Ϊ�Ǹ���Ʒ

        //������;������
        cout<<"��"<<++nt<<"��"<<endl;
        Print(s);

        if (memcmp(goal->a, s->a, sizeof(s->a))== 0) {
            int cnt = 0;
            State *kk = s->father;
            while(kk != NULL){
                path.push(*kk);
                kk = kk->father;
            }

            cout<<"�ҵ�Ŀ��״̬����������������"<<endl;

            while(!path.empty()){
                cout<<"��"<<++cnt<<"��:"<<endl;
                Print(&path.top());
                path.pop();
            }


            return 1;    //�ҵ�Ŀ��״̬������
        }


        int z;
        for (z = 0; z < 9; z++) {
            if (!s->a[z]) { //�ҵ�0λ��
                break;
            }
        }

        int x = z/3, y = z%3;

        for (int d = 0; d < 4; d++) { //Ѱ����һ���ƶ��ķ���  �������ҵ�˳��
            int newx = x + dx[d];
            int newy = y + dy[d];

            int newz = newx * 3 + newy;
            if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {  //�ƶ��Ϸ�

                State *t = new State;

         //      memcpy(t, s, sizeof(s));   //s������t,��չ�½ڵ㣬�����þͲ�Ҫ��

                for(int i = 0; i < 9 ;i++){
                    t->a[i] = s->a[i];
                }
                t->deep = s->deep;


                t->a[newz] = s->a[z];  //�ƶ�0
                t->a[z] = s->a[newz];


                if (try_to_insert(t)) {      //�ɹ���չ�½ڵ�

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

        if(!is_root){   //��������root �����������ڴӸ��ڵ������ӡ·��
            root = s;
            is_root = true;
        }

    }


    return 0;

}




int main(int argc,char** argv){

    freopen("local.txt","r",stdin);

    for(int i = 0; i < 9; ++i){
        scanf("%d",&st->a[i]); //��ʼ״̬

    }

    st->father = NULL;
    st->deep = 1;
    Print(st);

    for(int i = 0; i < 9; ++i){
        scanf("%d",&goal->a[i]); //��ʼ״̬
    }
    goal->deep = 1;
    Print(goal);

    //��ʼ�����ұ�
    init_lookup_table();
    //�����ұ���ֵ
    vis.insert(get_val(st));





    Q.push(*st);

    int ans = cost_tree_bfs();


    if(ans == 0){
        cout<<"�޽�"<<endl;
    }


    delete_tree(root);
    return 0;
}