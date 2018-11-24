#include<iostream>
#include<string>
#include<queue>
#include<stack>
using namespace std;

struct Node {
    char data;
    Node* l_child ,*r_child, *parent = NULL;
};
class Binary{
private :
    Node * root  = NULL;
public:
    Binary(){
        root  = new Node;
        root->l_child = NULL;
        root->r_child = NULL;
        root->data = ' ';
    };

    ~Binary(){ //using  BFS to release  all nodes
        queue<Node*> L;
        Node * t = root;
        L.push(t); //L is a queue.
        while(!L.empty()){
            t = L.front();  //检查队首元素
            L.pop();
            if(t == NULL){
                continue;
            }
            L.push(t->l_child);  //将队首元素的两个儿子踢进队列
            L.push(t->r_child);
            delete t;
        }

    }



//利用一个辅助队列，存放已经创建出来的但是没有确定左右儿子的结点
//每次从输入序列读两个元素,这两个元素就应该是队首结点的左右儿子
    //层序遍历创建
    void CreateTree(string s){
        queue<Node*> L ;
        int idx = 0;

        root->data = s[idx++] ;
        L.push(root);   //L is a queue.
        while( idx <s.length()){
            Node* node = L.front();  //取出当前队首元素
            L.pop();
            if (node == NULL) {    //若队首元素是空的
                idx += 2;           //代表它后面紧接着的两个儿子是空的
                continue;           //跳过此次循环
            }

            //node紧接着 是node 的左儿子

            char a = s[idx++];
            if ( a != '#'){//node 的左儿子不为空
                node->l_child = new Node;
                node->l_child->data = a;
                node ->l_child-> l_child = NULL;
                node->l_child->r_child = NULL;
            }
            L.push(node->l_child);//空的也要push进去，利于上面idx+=2跳过空结点的两个空儿子 ；

            if ( idx >=s.length()) break;//读取完毕

            //读取未完毕，紧接着右儿子

            a = s[idx++];
            if ( a != '#'){//node 的右儿子不为空
                node->r_child = new Node;
                node->r_child->data = a;
                node ->r_child-> l_child = NULL;
                node->r_child ->r_child = NULL;
            }
            L.push(node->r_child);
        }
       // cout<<"create finished!"<<endl;
    }


    void visit(Node *node){

    }

    Node *GetRoot(){
        return root;
    }





/*遍历：
	BFS层序遍历
	DFS深度遍历
		1.递归（效率低）
		2.非递归
*/


//BFS （队列实现）
    void LevelOrderTraverse(){
        queue<Node*> L ;
        if (root ==NULL){
            return;
        }
        L.push(root); // L is a queue
        while(!L.empty()){
            Node * node = L.front(); //取出队首
            L.pop();
            if(node == NULL) continue;
            L.push(node->l_child);
            L.push(node->r_child);
            visit(node); //访问node结点的数据
        }
    }

    //DFS
    //1递归 （思想：只是换visit位置，系统栈调用）
    void  PreOrderTraverse( Node *p){
        if (p ==NULL) {
            return;
        }
        visit(p);
        PreOrderTraverse(p->l_child);
        PreOrderTraverse(p->r_child);
    }
    void  InOrderTraverse( Node *p){
        if (p ==NULL) return;
        InOrderTraverse(p->l_child);
        visit(p);
        InOrderTraverse(p->r_child);
    }
    void  PostOrderTraverse( Node *p){
        if (p ==NULL) return;
        PostOrderTraverse(p->l_child);
        PostOrderTraverse(p->r_child);
        visit(p);
    }


    //2.非递归
    /*前序 思想：中左右遍历，visit当前结点，有儿子的话紧接着一定visit 儿子，同时将儿子踢入栈（注意踢入顺序）
        利用栈的后进先出的特点,后踢入先visit。
    */
    void PreOrder_Stack( Node *p){
        if (p ==NULL){
            return;
        }

        stack<Node*> s;
        s.push(p);
        while(!s.empty()){
            Node *t = s.top();
            s.pop();
            if(t ==NULL) {continue;}
            visit(t);
            s.push(t->r_child);
            s.push(t->l_child);//注意后踢入左儿子作为栈顶
        }
    }

/*
	//中序思想 ：利用辅助栈 左中右遍历.先一路找到最左下的结点
*/
    void InOrder_Stack( Node *p){
        if (p ==NULL){
            return;
        }

        stack<Node*> s;
        s.push(p);
        while(!s.empty()){
            Node *t = s.top();
            while(t){//左边一路进栈直到最左下的空结点，因为始终是先访问左儿子
                s.push(t->l_child);
                t = s.top();
            }
            //最后一个一定是空结点，退栈
            s.pop(); //上面一个循环结束后，一定左儿子是空的，空结点退栈

            if(s.empty()) {break;}//仅在中序最后一步，遍历完，栈空的时候用到，否则，紧接着的pop错误

            t = s.top();
            s.pop();
            visit(t);//访问自己
            s.push(t->r_child); //当前访问完下一个一定是 右儿子 ，把右儿子踢进去
        }
    }

/*
	***hard!!因为要利用根节点先访问左儿子和右儿子,所以必须记
录上次访问的结点和栈顶结点的关系:如果上次访问左儿子,
那么根节点还不能出栈,要等其右儿子访问后才出栈; 如果上次
访问的是右儿子,则说明左右子树都已经访问完毕,根节点出栈)

       判断根节点出不出栈！！
*/

    void  PostOrder_Stack(Node *p){
        if(p ==NULL){
            return;
        }

        stack<Node*> s;
        Node * cur = p;//当前要检查的结点
        Node *LastVisited = NULL; //前一个被访问的结点

        while(cur) {            //栈空时结束
            s.push(cur);      //最先遍历 左边， 全部 l_child 先入栈
            cur = cur->l_child;
        }

        while(!s.empty()){
            cur = s.top();
            s.pop();

            //如果当前结点的右孩子为空或者 已经被访问,接下来访问自己 ！！！！！重要！！！！
            if(cur->r_child == NULL||cur->r_child==LastVisited){
                visit(cur);
                LastVisited = cur;
            }

            else{//当前结点右儿子不空且未访问， 说明这时候自己还不能访问
                s.push(cur);//刚才 pop掉 了cur自己，因为还没轮到访问自己，要先访问右儿子的，还不能pop自己，现在加回来。//上面if 里面才是要pop 自己
                cur = cur->r_child;
                while(cur){//右儿子的全部左子树入栈
                    s.push(cur);
                    cur = cur->l_child;
                }

            }
        }
    }
};
