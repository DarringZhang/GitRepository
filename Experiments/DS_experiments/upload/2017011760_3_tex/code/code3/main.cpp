#include "BST.h"
#include "AVL.h"
#include <ctime>
#include <vector>
#include <cstdio>
#include <cstdlib>
//#include <windows.h>
#include <algorithm>

struct data{
    int  key;
    int  idx;
};

bool operator < (const data& first, const data& other){//q去掉&引用也可以，只是传参比传地址慢
    return first.key < other.key;//小于号重载为比较key值
}

//此产生随机数的方法太均匀，拉不开BST的树高
//void GenerateData(int *&box,int size){//传参 必须*&box 而不是 *box
//    srand((unsigned)time(NULL));
//    box = new int[size];
//    //生成size 个不重复的随机数，存放到数组中
//    for(int j = 0; j < size; j++){
//        box[j] = j;
//    }
//
//    for(int j = size-1; j >=1 ; j-- ){
//        swap(box[j],box[rand()%j]);
//    }
//
////    for(int j = 0; j < size; j++){
////        cout << box[j] << " ";
////    }
////  cout<<"finish"<<endl;
//}

void GenerateData(vector<int> &d,int size){
    srand((unsigned)time(NULL));//随机产生种子
    d.resize(size);
    vector<data> change;
    change.resize(size);
    for(int i = 0; i < size; i++){
        change[i].key = rand()%100;//rand()函数随机产生o~32768之间的数，对100取余产生一个0~99的随机数
        change[i].idx = i;
    }//虽然产生的随机数key有重复的，但是使用的是下标idx;

    sort(change.begin(),change.end());//根据change的key值排序,idx跟着一起动，sort 默认小于号比较，所以重载小于号生效
    //这里sort相当于打乱顺序，随机化

    for(int i = 0; i < change.size(); i++){
        d[i] = change[i].idx;
    }
}

void testSearchTime(int size){
    vector <int> NodeArray;//使用vector 数组大小可变
    BST aBST;
    AVL bAVL;
    GenerateData(NodeArray,size);
//   int *NodeArray = new int[5];
//
//    NodeArray[0] = 3;
//    NodeArray[1] = 2;
//    NodeArray[2] = 1;
//    NodeArray[3] = 4;
//    NodeArray[4] = 0;

//    for(int j = 0; j < size; j++){
//        cout << NodeArray[j] << " ";
//    }


    //测试建树需要的时间
    clock_t start = clock();
    for(int j = 0 ; j < size; j++){
        // aBST.BST_Insert_NonRecur(aBST.GetRoot(),NodeArray[j]);
        aBST.BST_Insert(aBST.GetRoot(),NodeArray[j]);
    }
    // aBST.inOrder_No_Stack();
    //printf("Build BST tree needs %ld miu seconds\n",(clock() - start));
    printf("Build %d height Tree time(BST): %ld miu seconds \n",aBST.GetRoot()->height,(clock() - start) );


    start = clock();
    for(int j = 0 ;j < size ; j++){
        //  bAVL.AVL_Insert_Nonrecur(bAVL.GetRoot(),NodeArray[j]);
        bAVL.AVL_Insert(bAVL.GetRoot(),NodeArray[j]);
    }
    //  bAVL.inOrder_No_Stack();
    //printf("Build AVL tree needs %ld miu seconds\n",(clock() - start));
    printf("Build %d height Tree time(AVL): %ld miu seconds \n",bAVL.GetRoot()->height,(clock() - start) );

    //测试搜索值需要的时间
    vector<int>SearchArray;
    GenerateData(SearchArray, size/10);

    start = clock();
    for(int i = 0;i < size/10;i++){
        aBST.BST_Search_NonRecur(aBST.GetRoot(),SearchArray[i]);
    }
    printf("Search Time(BST): %ld miu seconds\n", clock() -  start);

    start = clock();
    for(int i = 0;i < size/10;i++){
        bAVL.BST_Search_NonRecur(bAVL.GetRoot(),SearchArray[i]);
    }
    printf("Search Time(AVL): %ld miu seconds\n", clock() -  start);

    aBST.destroy(aBST.GetRoot());//结束后析构
    bAVL.destroy(bAVL.GetRoot());
}

/*********************************************这是一条分界线**********************************/

int main(void)
{
    printf(" *说明：本程序分为三块：程序1，程序2，程序3;分别实现BST,AVL基本操作以及两者对比*\n\n");

/*********************************************这是一条分界线**********************************/

    BST a;
    int flag=1,k;
    printf("       程序1实现二叉搜索树的基本操作。（输入13退出，进入程序2开始测试AVL的基本操作）\n");
    printf("建立BST,递归插入，非递归插入，递归查找某个特定的值，非递归查找某个特定的值，找最大，找最小，找后继，前驱，删除，,替换，前/中序遍历打印，退出等操作。\n");

    while(flag)
    {
        printf("\n");
        printf("|--------------------------------------------------------------|\n");
        printf("|                      BST的基本操作如下:                        |\n");
        printf("|                        0.创建BST                             |\n");
        printf("|                        1.递归插入                             |\n");
        printf("|                        2.非递归插入 (未更新树高)                |\n");
        printf("|                        3.递归查找                             |\n");
        printf("|                        4.非递归查找                           |\n");
        printf("|                        5.最大                                |\n");
        printf("|                        6.最小                                |\n");
        printf("|                        7.前驱(中序)                          |\n");
        printf("|                        8.后继（中序）                         |\n");
        printf("|                        9.删除                                |\n");
        printf("|                        10.替换                               |\n");
        printf("|                        11.前序遍历打印                        |\n");
        printf("|                        12.中序遍历打印（按数字从小到大）         |\n");
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
                printf("退出本BST测试程序\n\n");
                break;
            }

            default:{
                cout<<"input error,please input again"<<endl;
                break;
            }

        }
    }
    a.destroy(a.GetRoot());


/*********************************************这是一条分界线**********************************/

    AVL b;
    flag=1;
    printf("      程序2实现AVL的基本操作。（输入13退出，进入程序3开始测试BST 和AVL 的查找和树高的关系）\n");
    printf("建立AVL，旋转插入，递归查找，非递归查找，找最大，找最小，找前驱，找后继，删除，替换，中序打印操作。\n");

    while(flag)
    {
        printf("\n");
        printf("|--------------------------------------------------------------|\n");
        printf("|                      AVL的基本操作如下:                      |\n");
        printf("|                        0.创建AVL                             |\n");
        printf("|                        1.递归插入                            |\n");
        printf("|                        2.非递归插入                          |\n");
        printf("|                        3.递归查找                            |\n");
        printf("|                        4.非递归查找                          |\n");
        printf("|                        5.最大                                |\n");
        printf("|                        6.最小                                |\n");
        printf("|                        7.前驱                                |\n");
        printf("|                        8.后继                                |\n");
        printf("|                        9.删除                                |\n");
        printf("|                        10.替换                               |\n");
        printf("|                        11.中序遍历打印                       |\n");
        printf("|                        12.前序遍历打印                       |\n");
        printf("|                        13.退出                               |\n");
        printf("|--------------------------------------------------------------|\n");
        printf("                        请选择功能：");
        scanf("%d",&k);
        switch(k)
        {
            case 0:{
                printf("请建立AVL，输入你想要创建的结点个数：");
                int s;
                cin>>s;
                b.Create_AVL(s);
                b.inOrder_No_Stack();
                break;
            }
            case 1 :{
                if(b.GetRoot())
                {
                    printf("input the key you wanna insert:");
                    int k;
                    cin>>k;
                    b.AVL_Insert(b.GetRoot(),k) ;
                    b.inOrder_No_Stack();
                }
                else
                    printf("          AVL为空！\n");
                break;

            }

            case 2:{
                if(b.GetRoot())
                {
                    printf("input the key you wanna Nonrecursive insert:");
                    int k;
                    cin>>k;
                    b.AVL_Insert_Nonrecur(b.GetRoot(),k);
                    b.inOrder_No_Stack();
                }
                else
                    printf("          AVL为空！\n");
                break;
            }
            case 3: {
                if(b.GetRoot())
                {
                    printf("input the key you wannna recursive find:");
                    int k;
                    cin>>k;
                    Node * t = b.BST_Search(b.GetRoot(),k);
                    if(t==NULL){
                        cout<<"cant't find!";
                    }
                    else{
                        cout<<"find it !";
                    }
                    printf("\n");
                }
                else
                    printf("          AVL为空！\n");
                break;
            }

            case 4:  {
                if(b.GetRoot())
                {
                    printf("input the key you wannna Non_recursive find:");
                    int k;
                    cin>>k;
                    Node * t = b.BST_Search_NonRecur(b.GetRoot(),k);
                    if(t==NULL){
                        cout<<"cant't find!";
                    }
                    else{
                        cout<<"find it !";
                    }
                    printf("\n");
                }
                else
                    printf("          AVL为空！\n");
                break;
            }

            case 5:  {

                if(b.GetRoot())
                {
                    printf("Maxinum is ：");
                    cout<<b.BST_Maximum(b.GetRoot())->key;
                    printf("\n");
                }
                else
                    printf("          AVL为空！\n");
                break;
            }
            case 6: {
                if(b.GetRoot())
                {
                    printf("Mininum is ：");
                    cout<<b.BST_Minimum(b.GetRoot())->key;
                    printf("\n");
                }
                else
                    printf("          AVL为空！\n");
                break;
            }

            case 7:{
                if(b.GetRoot())
                {
                    printf("input the key you wanna find predecessor for:");
                    int k;
                    cin>>k;
                    if(b.BST_Search_NonRecur(b.GetRoot(),k)==b.BST_Minimum(b.GetRoot())){
                        cout<<"the predecessor is NULL"<<endl;
                        break;
                    }
                    cout<<"the predecessor is:";
                    cout<<b.BST_Predecessor(k)->key<<endl;
                    printf("\n");
                }
                else
                    printf("          AVL为空！\n");
                break;
            }

            case 8:{
                printf("input the key you wanna find successor for:");
                int k;
                cin>>k;
                if(b.BST_Search_NonRecur(b.GetRoot(),k)==b.BST_Maximum(b.GetRoot())){
                    cout<<"the successor is NULL"<<endl;
                    break;
                }
                cout<<"the successor is:";
                cout<<b.BST_Successor(k)->key<<endl;
                printf("\n");
                break;
            }
            case 9:{
                printf("input the key you wanna delete:");
                int k;
                cin>>k;
                b.AVL_Delete(b.GetRoot(),k);
                b.inOrder_No_Stack();
                break;
            }
            case 10:{
                printf("input the key you wanna modify and modify as:");
                int m,n;
                cin>>m>>n;
                b.Modyfiy(m,n);
                b.inOrder_No_Stack();
                break;
            }
            case 11:{
                b.inOrder_No_Stack();
                break;
            }

            case 12:{
                cout<<"前序打印结果为：";
                b.preOrder_No_Stack();
                break;
            }
            case 13:{
                flag=0;
                printf("结束程序2运行\n\n");
                break;
            }
            default:{
                cout<<"input error,please input again"<<endl;
                break;
            }

        }
    }
    b.destroy(b.GetRoot());
    system("pause");

    /*********************************************这是一条分界线**********************************/

    cout<<"************************程序3进行验证BST，AVL的查找和树高的关系*************************"<<endl;

    int TestGroups = 10;//测试组别数10
    //srand(clock());testSearchTime函数内已经包含
    for(int i=1; i<=TestGroups; i++){
        cout<<"Group "<<i<<":"<<endl;
        testSearchTime(1000000);//构建含有1000000个结点的树
        cout<<endl;
    }

    return 0;
}



