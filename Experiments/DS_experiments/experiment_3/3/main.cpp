#include "BST.h"
#include "AVL.h"
#include <ctime>
#include <cstdio>
#include <cstdlib>

int main(void)
{
    BST a;
    AVL b;
    int flag=1,k;
    printf("                     本程序实现二叉搜索树的基本操作。\n");
    printf("可以进行建立BST,递归插入，非递归插入，递归查找某个特定的值，非递归查找某个特定的值，找最大，找最小，找后继，前驱，删除，,替换，前/中序遍历打印，退出等操作。\n");

    while(flag)
    {
        printf("\n");
        printf("|--------------------------------------------------------------|\n");
        printf("|                      BST的基本操作如下:                        |\n");
        printf("|                        0.创建BST                             |\n");
        printf("|                        1.递归插入                             |\n");
        printf("|                        2.非递归插入                           |\n");
        printf("|                        3.递归查找                             |\n");
        printf("|                        4.非递归查找                           |\n");
        printf("|                        5.最大                                |\n");
        printf("|                        6.最小                                |\n");
        printf("|                        7.前驱(中序)                          |\n");
        printf("|                        8.后继（中序）                         |\n");
        printf("|                        9.删除(不涉及调整树高)                  |\n");
        printf("|                        10.替换                               |\n");
        printf("|                        11.前序遍历打印                        |\n");
        printf("|                        12.中序遍历打印（按数字从小到大）       |\n");
        printf("|                        13.退出                               |\n");
        printf("|--------------------------------------------------------------|\n");
        printf("                        请选择功能：");
        scanf("%d",&k);
        switch(k)
        {
            case 0:{
                printf("请建立BST，输入你想要创建的结点个数：");
                int s;
                cin>>s;
                a.Create_BST(s);
                cout<<"中序打印结果为：";
                a.inOrder_No_Stack();
                break;
            }
            case 1 :{
                if(a.GetRoot())
                {
                    printf("input the key you wanna recursive_insert:");
                    int k;
                    cin>>k;
                    a.BST_Insert(a.GetRoot(),k);
                    cout<<"中序打印结果为：";
                    a.inOrder_No_Stack();
                }
                else
                    printf("          BST为空！\n");
                break;

            }
            case 2: {
                if(a.GetRoot())
                {
                    printf("input the key you wanna non_recursive_insert:");
                    int k;
                    cin>>k;
                    a.BST_Insert_NonRecur(a.GetRoot(),k) ;
                    cout<<"中序打印结果为：";
                    a.inOrder_No_Stack();
                }
                else
                    printf("          BST为空！\n");
                break;
            }

            case 3: {
                if(a.GetRoot())
                {
                    printf("input the key you wannna recursive find:");
                    int k;
                    cin>>k;
                    Node * t = a.BST_Search(a.GetRoot(),k);
                    if(t==NULL){
                        cout<<"cant't find!";
                    }
                    else{
                        cout<<"find it !";
                    }
                    printf("\n");
                }
                else
                    printf("          BST为空！\n");
                break;
            }

            case 4:  {
                if(a.GetRoot())
                {
                    printf("input the key you wannna Non_recursive find:");
                    int k;
                    cin>>k;
                    Node * t = a.BST_Search_NonRecur(a.GetRoot(),k);
                    if(t==NULL){
                        cout<<"cant't find!";
                    }
                    else{
                        cout<<"find it !";
                    }
                    printf("\n");
                }
                else
                    printf("          BST为空！\n");
                break;
            }

            case 5:  {

                if(a.GetRoot())
                {
                    printf("Maxinum is ：");
                    cout<<a.BST_Maximum(a.GetRoot())->key;
                    printf("\n");
                }
                else
                    printf("          BST为空！\n");
                break;
            }
            case 6: {
                if(a.GetRoot())
                {
                    printf("Mininum is ：");
                    cout<<a.BST_Minimum(a.GetRoot())->key;
                    printf("\n");
                }
                else
                    printf("          BST为空！\n");
                break;
            }

            case 7:{
                if(a.GetRoot())
                {
                    printf("input the key you wanna find predecessor for:");
                    int k;
                    cin>>k;
                    if(a.BST_Search_NonRecur(a.GetRoot(),k)==a.BST_Minimum(a.GetRoot())){
                        cout<<"the predecessor is NULL"<<endl;
                        break;
                    }
                    cout<<"the predecessor is:";
                    cout<<a.BST_Predecessor(k)->key<<endl;
                    printf("\n");
                }
                else
                    printf("          BST为空！\n");
                break;
            }

            case 8:{
                printf("input the key you wanna find successor for:");
                int k;
                cin>>k;
                if(a.BST_Search_NonRecur(a.GetRoot(),k)==a.BST_Maximum(a.GetRoot())){
                    cout<<"the successor is NULL"<<endl;
                    break;
                }
                cout<<"the successor is:";
                cout<<a.BST_Successor(k)->key<<endl;
                printf("\n");
                break;
            }
            case 9:{
                printf("input the key you wanna delete:");
                int k;
                cin>>k;
                a.Delete(k);
                cout<<"中序打印结果为：";
                a.inOrder_No_Stack();
                break;
            }
            case 10:{
                printf("input the key you wanna modify and modify as:");
                int m,n;
                cin>>m>>n;
                a.Modyfiy(m,n);
                cout<<"中序打印结果为：";
                a.inOrder_No_Stack();
                break;
            }
            case 11:{
                cout<<"前序打印结果为：";
                a.preOrder_No_Stack();
                break;
            }
            case 12:{
                cout<<"中序打印结果为：";
                a.inOrder_No_Stack();
                break;
            }
            case 13:{
                flag=0;
                printf("结束程序运行，退出本程序\n");
                break;
            }

            default:{
                cout<<"input error,please input again"<<endl;
                break;
            }

        }
    }

    a.destroy(a.GetRoot());

    cout<<"************************下面进行验证BST树的查找和树高的关系*************************"<<endl;

    clock_t start,finish;
    double total_time;
    int value;

    cout<<"按从小到大的顺序插入100000个数，BST其成为一条链,AVL高度平衡，再查找"<<endl;
    for(int i = 1 ;i <= 50000;i++){
        a.BST_Insert_NonRecur(a.GetRoot(),i);
    }




    for(int i = 1 ;i <= 50000;i++){
        b.AVL_Insert(b.GetRoot(),i);
    }


    cout<<"请输入你要查找的值:";
    cin>>value;

    start=clock();
    a.BST_Search_NonRecur(a.GetRoot(),value);
    finish=clock();
    total_time=(double)(finish-start);
    cout<<"the "<<a.GetRoot()->height<<" hight BST tree finds "<<value<<" needs "<<total_time<<" ms"<<endl;


    start=clock();
    b.BST_Search_NonRecur(b.GetRoot(),value);
    finish=clock();
    total_time=(double)(finish-start);
    cout<<"the "<<b.GetRoot()->height<<" hight AVL tree finds "<<value<<" needs "<<total_time<<" ms"<<endl;


    return 0;
}



