
//���뷽ʽ��GBK

#include <bits/stdc++.h>
using namespace std;

typedef int State[9];  //����9��Ԫ�ص�"״̬",����һ�ֽڵ�
const int  maxstate = 1000000;
State st[maxstate],goal;  //st Ϊ״̬���飬���е�״̬���������������ܱ���1000000��״̬
int dist[maxstate];      //�������飻
int fa[maxstate];       //��ӡ��������ĸ��ױ�Žڵ㡣

set<int> vis;

void init_lookup_table(){
    vis.clear();
}

int try_to_insert(int s){
    int v = 0;
    for(int i = 0; i < 9; ++i) {   //��״̬ת����9λʮ������
        v = v * 10 + st[s][i];
    }

    if(vis.count(v)){
        return 0;
    }

    vis.insert(v);
    return 1;
}

// ����һ���ڵ��dx��dy,Ҫô�ϣ�Ҫô�£�Ҫô��Ҫô�ң���dx��dy�����������
const int dx[] = {-1,1,0,0};
const int dy[] = {0,0,-1,1};

int bfs(){
    init_lookup_table();            //��ʼ�����ұ�
    int front = 1,rear = 2;         //�����ͷ��β��������0,0������

    //int flag=0 ;

    while(front < rear) {

        //cout<<"����flag" << flag++ <<endl;

        State &s = st[front];      //"����"�򻯴���,sΪ����front��λ��״̬����ʱ���顣
        if (memcmp(goal, s, sizeof(s))== 0) {
            return front; //�ҵ�Ŀ��״̬���������״̬������st���±ꡣ
        }

        int z;
        for (z = 0; z < 9; z++) {
            if (!s[z]) { //�ҵ�0λ��
                break;
            }
        }

        int x = z/3, y = z%3; //��ȡ���еı�ţ�0~2���������ɣ���һάת���ɶ�ά���ꡣ

        for (int d = 0; d < 4; d++) { //Ѱ����һ���ƶ��ķ���  �������ҵ�˳��
            int newx = x + dx[d];
            int newy = y + dy[d];

            int newz = newx * 3 + newy;  //��Ӧǰ���  x = z/3,y = z%3
            if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {  //�ƶ��Ϸ�
                State &t = st[rear];
                memcpy(&t, &s, sizeof(s));   //s������t,��չ�½ڵ�

                t[newz] = s[z]; //����0�͵�һ�����ֵ�λ��
                t[z] = s[newz];

                dist[rear] = dist[front] + 1;  //���½ڵ�ľ���ֵ

                if (try_to_insert(rear)) {      //�ɹ���չ�½ڵ㣬�޸Ķ�βָ��
                    fa[rear] =front;
                    rear++;
                }
            }

        }

        front++;           //�޸Ķ���ָ��

    }
    return 0;
}

int main() {

    for(int i = 0; i < 9; ++i){
        scanf("%d",&st[1][i]); //��ʼ״̬
    }

    for(int i = 0; i < 9; ++i){
        scanf("%d",&goal[i]);  //Ŀ��״̬
    }


    int ans = bfs();


    cout<<"�������ڼ����ڵ� : " <<ans <<endl;



    if(ans > 0){
        cout<<"������Ҫ�ƶ��Ĳ���: " ;
        printf("%d\n",dist[ans]);

        cout<<"��Ҷ��һֱ�����ڵ���ƶ�·��Ϊ: " << endl;
        int print = dist[ans];
        int flag = ans;
        int cnt = 0;

        while(print--){
            cout<<"��"<<++cnt<<"��:"<<endl;
            State &t = st[flag];
            for(int i = 0; i < 9; ++i){
                printf("%d ",t[i]);  //Ŀ��״̬
                if((i+1)%3 == 0){
                    cout<<endl;
                }
            }

            cout<<endl;
            flag = fa[flag];

        }

    }
    else{
        printf("�޽�\n");
    }

    return 0;
}