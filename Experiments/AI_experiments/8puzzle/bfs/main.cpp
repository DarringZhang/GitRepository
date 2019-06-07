#include <bits/stdc++.h>
using namespace std;
#define N 2000

struct Map{
    int cell[N][N];          //数码数组
    Direction BelockDirec; //操作符方向
    struct Map * Parent;   //父节点
};


//打印数组
void PrintMap(struct Map *map){
    cout<<"*************************************************"<<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout<<map->cell[i][j]<<"   ";
        }
        cout<<endl;
    }
    cout<<"*************************************************"<<endl;
}


//随机生成一个八数码数组
struct Map *RandomMap(){
    int a[9];
    struct Map *NewMap = new Map();
    srand((unsigned)time(0));

    for(int k = 0; k < 9; k++)
    {
        bool Isre = false;
        a[k] = rand()%9;
        for (int l = 0; l < k; l++) //每次遍历已放入八数码的节点
        {
            if (a[k] == a[l])
            {
                Isre = true;
                break;
            }
        }

        if(Isre)
        {
            k = k - 1;
            continue;
        }
    }


    for(int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            NewMap->cell[i][j] = a[i*3+j]; //一维数组变成二维
        }
    }
    NewMap->Parent = NULL;
    NewMap->BelockDirec = None;
    return NewMap;
}


//函数用来扩展一个结点的后继结点（上、下、左、右）
struct Map * MoveMap(struct Map * map,Direction Direct,bool CreateNewMap)
{
    struct Map * NewMap;

    //获取空闲格坐标位置i,j
    int i,j;
    for(i = 0; i < N; i++)
    {
        bool HasGetBlankCell = false;
        for(j = 0; j < N; j++)
        {
            if(map->cell[i][j] == 0)
            {
                HasGetBlankCell = true;
                break;
            }
        }
        if(HasGetBlankCell)
            break;
    }


    //移动数字,t_i,t_j为移动后0的坐标
    int t_i = i,t_j = j;
    bool AbleMove = true; //四周是墙，不能移动

    switch(Direct)//移动方向
    {
        case Down:
            t_i++;
            if(t_i >= N)
                AbleMove=false;
            break;
        case Up:
            t_i--;
            if(t_i < 0)
                AbleMove=false;
            break;
        case Left:
            t_j--;
            if(t_j < 0)
                AbleMove=false;
            break;
        case Right:
            t_j++;
            if(t_j >= N)
                AbleMove=false;
            break;
    };


    if(!AbleMove)//不可以移动则返回原节点
    {
        return map;
    }


    if(CreateNewMap)
    {
        NewMap = new Map();
        for(int x = 0; x < N; x++)
            for(int y = 0; y < N; y++)
                NewMap->cell[x][y] = map->cell[x][y];
    }
    else
        NewMap = map;


/*移动即交换0与相应数字的位置*/

    NewMap->cell[i][j] = NewMap->cell[t_i][t_j]; //原来的位置被替换
    NewMap->cell[t_i][t_j] = 0;//设置现在的位置 = 0


    return NewMap;
}



//判断某节点是否为目标结点
bool IsSuccess(struct Map * map,struct Map * Target)
{
    bool IsSuc = true;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(map->cell[i][j] != Target->cell[i][j])
            {
                IsSuc = false;
                break;
            }
        }
        if(!IsSuc)
            break;
    }
    return IsSuc;
}



//Open表队列结构，先进先出，链表作为数据结构，便于指针回溯
struct Map * BNF_Search(struct Map * begin,struct Map * Target){
    struct Map *p1,*p2,*p; //p1待进入close, p2待进入open, p是结果
    bool IsSucc = false;
    queue<struct Map *> Queue;

    if(IsSuccess(begin,Target)){
        return begin;
    }

    //当前表不为空表 或 还没找到结果
    while(!Queue.empty() || p == NULL){
        p1 = Queue.front(); //待拓展
        Queue.pop();
        Direction Direct = (Direction)i;

        //拓展当前节点
        for(int i = 0; i <= 4; ++i){
            if(Direct == p1->BelockDirec){//跳过父节点的方向
                continue;
            }

            p2 = MoveMap(p1,Direct,true);  //p2为拓展的结点

            //数码可以移动
            if(p2 != p1){
                p2->Parent = p1;

                switch (Direct){
                    case Up:
                        p2->BelockDirec = Down;
                        break;
                    case Down:
                        p2->BelockDirec = Up;
                        break;
                    case Left:
                        p2->BelockDirec = Right;
                        break;
                    case Right:
                        p2->BelockDirec = Left;
                        break;
                }

                if(IsSuccess(p2,Target)){
                    p = p2;
                    return p;
                }

                Queue.push(p2);


            }


        }

    }

}


//判断八数码可不可解
//结论：结点逆序数的奇偶性，奇偶相同 说明有解
int HasResult(struct Map *map)
{
    int a=0;
    char b[9];
    //把二维表变为一维数组，和随机生成八数码中 类似的操作
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            b[i*3+j]=map->cell[i][j];
    }

    for(i=0;i<9;i++)
    {
        for(int j=0;j<i;j++)
        {
            if((b[j]<b[i])&&b[j]!=0)
                a++;
        }
    }
    return a%2;
}


int main() {
    int a1,a2;
    Map Target;
    Map *begin,*T;
    begin=new Map;
    //设定目标图 [1 2 3],[8 0 4],[7 6 5]

    Target.cell[0][0] = 1;
    Target.cell[0][1] = 2;
    Target.cell[0][2] = 3;
    Target.cell[1][0] = 8;
    Target.cell[1][1] = 0;
    Target.cell[1][2] = 4;
    Target.cell[2][0] = 7;
    Target.cell[2][1] = 6;
    Target.cell[2][2] = 5;



    begin = RandomMap();
    cout<<"目标图:"<<endl;
    PrintMap(&Target);
    cout<<"起始图:"<<endl;
    PrintMap(begin);



    a1=HasResult(&Target);
    a2=HasResult(begin);

    if(a1 != a2){//奇偶不同
        cout<<"无解"<<endl;
    }
    else{
        cout<<"有解"<<endl;
        double start = clock();
        //图搜索
    }



}




    //如果有解则进行BNF搜索并打印结果：


    else
    {
        double start=clock();
        cout<<"有解"<<endl;

//图搜索
        T=BNF_Search(begin,&Target);
//打印
        if(T != NULL)
        {
//把路径倒序
            Map *p=T;
            stack<Map *> result_Stack1;  //栈，先进后出
            while(p->Parent != NULL)
            {
                result_Stack1.push(p);
                p = p->Parent;
            }
            cout<<"搜索结果:"<<endl;
            while(!result_Stack1.empty())
            {
                PrintMap(result_Stack1.top());
                c++;
                result_Stack1.pop();//删除
            }
            cout<<"\n完成!"<<endl;
            cout<<"路径长度为:"<<c<<endl;
            double end=clock();
            cout<<"程序运行的时间为:"<<end-start<<endl;
        }

    return 0;
}