//
// Created by Darring on 2018/12/9.
//

#ifndef PRIM_PRIM_H
#define PRIM_PRIM_H
/*稠密图O（n^2），Q如果使⽤⼆叉堆,时间复杂度可以控制在O(E lgV)⾥.
 * 首先从集合V中任选取一点(如V0)放入集合U中，这是U={V0}, TE{Ф},然后选择这样的
一条边：一个顶点在集合U中，另一个顶点在集合V-U中,且权值最小的边(u,v)（u∈U, v∈V-U）
将该边放入TE中，并将顶点v加入到U中。重复上述过程，知道U=V位置，此时TE中有n-1条边，那
么T=(U,TE)就是G的一颗最小生成树。
 * */


/*
 * 如果用传统的做法每次都要将集合内的元素遍历一遍，再与集合外的元素判断是否相连，再找出最小权值，
 * 然后把带有最小权值的那个终点记录下来，插入到集合内。
下次循环再从集合的第一个元素开始遍历，这样会浪费很多时间，
 于是乎，我想能不能把之前已经遍历过的顶点而且不是最小权的那些顶点存入列表中，下次再遍历的时候可以接着用，
 只需要把新的顶点插入进去就行了，那么怎么输出最小的权呢，大家都知道有个优先队列，
 就是把队列中的权值按由小到大排列，每次只需要把top()的权值pop掉就行了。


我在把3插入队列之后，怎么不用遍历找出和3相连的边，解决办法就是用代码中的link数组来保存与3对应的边的终点，
那么和以3为起点的边有很多，那有几个呢，link[p][link[p][0]++] = q;这个就是解决办法每有重复的顶点插入进去，
    link[p][0]就会++，最后link[p][0]就是与p顶点相连的边数，

    link[3][1] = 2  (表示以3作为  顶点的第一条边  即    与顶点3相连的第一条边  的终点为2 即 3-2这个边)

   link[3][2] = 4  同理表示 3-4为以3作为顶点的第二条边
 * */

#include <iostream>
#include <queue>
#define SIZE 100
using namespace std;
struct Node{
    int start;
    int end;
    int weight;
};

bool operator < (const Node &a,const Node &b)
{
    return a.weight > b.weight;
}


class MinimumSpanningTree {
private:
    int N,M;
    int AdjMatrix[SIZE+1][SIZE+1];
    int link[SIZE+1][SIZE+1];
public:
    MinimumSpanningTree(int n,int m) {
        this->N = n;
        this->M = m;
        for(int i = 1; i <= n; ++ i){
            link[i][0] = 1;//初始化link。。。= “1”, 输入第“1”条边的信息时，与顶点i 相连的第 “1” 条边 为。。。
        }//留出 link[p][0] 的始终 代表p顶点相连的边数
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= n; ++j){
                AdjMatrix[i][j] = 0;
            }
        }
    }
    ~MinimumSpanningTree(){
    }



    void prim(int s) {//从s点开始
        int sum = 0;//计算最小生成树的花费
        int point1, point2, cost;
        int visited[SIZE + 1] = {0};//初始化 为未访问

        priority_queue<Node> Q;//此处使用优先队列（二叉堆实现），使算法复杂度控制在O（elogv）



        cout << "输入边信息" << endl;

        while (M--) {
            cin >> point1 >> point2 >> cost;
            AdjMatrix[point1][point2] = cost;
            AdjMatrix[point2][point1] = cost;
            link[point1][link[point1][0]++] = point2;//不用遍历，用link存放 起源点发出的多条边 而不引起矛盾
            link[point2][link[point2][0]++] = point1;//
        }


        Node nn;
        int count = 1;//已经访问过的顶点个数，默认从s开始，s已经访问
        visited[s] = 1;
        while (count < N) {
            for (int i = 1; i < link[s][0]; i++) {//遍历所有和s相邻的边  link[s][0] - 1个相邻的
                if (!visited[link[s][i]])// 若这个边没被访问，就将其加入优先队列
                {
                    nn.start = s;
                    nn.end = link[s][i];
                    nn.weight = AdjMatrix[s][nn.end];
                    Q.push(nn);

                }

            }



            while(!Q.empty() && visited[Q.top().end]) {//到达一个绝境顶点，与之相邻的顶点在原图中都访问过，将要构成环了
                Q.pop();
           }//跳过这个点，找下一个权值小的点

            nn = Q.top();
            Q.pop();
            s = nn.end;//更新下一个要访问的结点
            sum += nn.weight;
            //cout << nn.start << "--" << nn.end << " " << nn.weight << endl;
            visited[s] = 1;
            count++;
        }

        cout<<"cost:"<<sum<<endl;
    }

};
#endif //PRIM_PRIM_H
