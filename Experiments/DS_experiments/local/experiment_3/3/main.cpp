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

bool operator < (const data& first, const data& other){//qȥ��&����Ҳ���ԣ�ֻ�Ǵ��αȴ���ַ��
    return first.key < other.key;//С�ں�����Ϊ�Ƚ�keyֵ
}

//�˲���������ķ���̫���ȣ�������BST������
//void GenerateData(int *&box,int size){//���� ����*&box ������ *box
//    srand((unsigned)time(NULL));
//    box = new int[size];
//    //����size �����ظ������������ŵ�������
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
    srand((unsigned)time(NULL));//�����������
    d.resize(size);
    vector<data> change;
    change.resize(size);
    for(int i = 0; i < size; i++){
        change[i].key = rand()%100;//rand()�����������o~32768֮���������100ȡ�����һ��0~99�������
        change[i].idx = i;
    }//��Ȼ�����������key���ظ��ģ�����ʹ�õ����±�idx;

    sort(change.begin(),change.end());//����change��keyֵ����,idx����һ�𶯣�sort Ĭ��С�ںűȽϣ���������С�ں���Ч
    //����sort�൱�ڴ���˳�������

    for(int i = 0; i < change.size(); i++){
        d[i] = change[i].idx;
    }
}

void testSearchTime(int size){
    vector <int> NodeArray;//ʹ��vector �����С�ɱ�
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


    //���Խ�����Ҫ��ʱ��
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

    //��������ֵ��Ҫ��ʱ��
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

    aBST.destroy(aBST.GetRoot());//����������
    bAVL.destroy(bAVL.GetRoot());
}

/*********************************************����һ���ֽ���**********************************/

int main(void)
{
    printf(" *˵�����������Ϊ���飺����1������2������3;�ֱ�ʵ��BST,AVL���������Լ����߶Ա�*\n\n");

/*********************************************����һ���ֽ���**********************************/

    BST a;
    int flag=1,k;
    printf("       ����1ʵ�ֶ����������Ļ���������������13�˳����������2��ʼ����AVL�Ļ���������\n");
    printf("����BST,�ݹ���룬�ǵݹ���룬�ݹ����ĳ���ض���ֵ���ǵݹ����ĳ���ض���ֵ�����������С���Һ�̣�ǰ����ɾ����,�滻��ǰ/���������ӡ���˳��Ȳ�����\n");

    while(flag)
    {
        printf("\n");
        printf("|--------------------------------------------------------------|\n");
        printf("|                      BST�Ļ�����������:                        |\n");
        printf("|                        0.����BST                             |\n");
        printf("|                        1.�ݹ����                             |\n");
        printf("|                        2.�ǵݹ����                           |\n");
        printf("|                        3.�ݹ����                             |\n");
        printf("|                        4.�ǵݹ����                           |\n");
        printf("|                        5.���                                |\n");
        printf("|                        6.��С                                |\n");
        printf("|                        7.ǰ��(����)                          |\n");
        printf("|                        8.��̣�����                         |\n");
        printf("|                        9.ɾ��(���漰��������)                  |\n");
        printf("|                        10.�滻                               |\n");
        printf("|                        11.ǰ�������ӡ                        |\n");
        printf("|                        12.���������ӡ�������ִ�С����         |\n");
        printf("|                        13.�˳�                               |\n");
        printf("|--------------------------------------------------------------|\n");
        printf("                        ��ѡ���ܣ�");
        scanf("%d",&k);
        switch(k)
        {
            case 0:{
                printf("�뽨��BST����������Ҫ�����Ľ�������");
                int s;
                cin>>s;
                a.Create_BST(s);
                cout<<"�����ӡ���Ϊ��";
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
                    cout<<"�����ӡ���Ϊ��";
                    a.inOrder_No_Stack();
                }
                else
                    printf("          BSTΪ�գ�\n");
                break;

            }
            case 2: {
                if(a.GetRoot())
                {
                    printf("input the key you wanna non_recursive_insert:");
                    int k;
                    cin>>k;
                    a.BST_Insert_NonRecur(a.GetRoot(),k) ;
                    cout<<"�����ӡ���Ϊ��";
                    a.inOrder_No_Stack();
                }
                else
                    printf("          BSTΪ�գ�\n");
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
                    printf("          BSTΪ�գ�\n");
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
                    printf("          BSTΪ�գ�\n");
                break;
            }

            case 5:  {

                if(a.GetRoot())
                {
                    printf("Maxinum is ��");
                    cout<<a.BST_Maximum(a.GetRoot())->key;
                    printf("\n");
                }
                else
                    printf("          BSTΪ�գ�\n");
                break;
            }
            case 6: {
                if(a.GetRoot())
                {
                    printf("Mininum is ��");
                    cout<<a.BST_Minimum(a.GetRoot())->key;
                    printf("\n");
                }
                else
                    printf("          BSTΪ�գ�\n");
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
                    printf("          BSTΪ�գ�\n");
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
                cout<<"�����ӡ���Ϊ��";
                a.inOrder_No_Stack();
                break;
            }
            case 10:{
                printf("input the key you wanna modify and modify as:");
                int m,n;
                cin>>m>>n;
                a.Modyfiy(m,n);
                cout<<"�����ӡ���Ϊ��";
                a.inOrder_No_Stack();
                break;
            }
            case 11:{
                cout<<"ǰ���ӡ���Ϊ��";
                a.preOrder_No_Stack();
                break;
            }
            case 12:{
                cout<<"�����ӡ���Ϊ��";
                a.inOrder_No_Stack();
                break;
            }
            case 13:{
                flag=0;
                printf("�˳���BST���Գ���\n\n");
                break;
            }

            default:{
                cout<<"input error,please input again"<<endl;
                break;
            }

        }
    }
    a.destroy(a.GetRoot());


/*********************************************����һ���ֽ���**********************************/

    AVL b;
    flag=1;
    printf("      ����2ʵ��AVL�Ļ���������������13�˳����������3��ʼ����BST ��AVL �Ĳ��Һ����ߵĹ�ϵ��\n");
    printf("����AVL����ת���룬�ݹ���ң��ǵݹ���ң����������С����ǰ�����Һ�̣�ɾ�����滻�������ӡ������\n");

    while(flag)
    {
        printf("\n");
        printf("|--------------------------------------------------------------|\n");
        printf("|                      AVL�Ļ�����������:                      |\n");
        printf("|                        0.����AVL                             |\n");
        printf("|                        1.�ݹ����                            |\n");
        printf("|                        2.�ǵݹ����                          |\n");
        printf("|                        3.�ݹ����                            |\n");
        printf("|                        4.�ǵݹ����                          |\n");
        printf("|                        5.���                                |\n");
        printf("|                        6.��С                                |\n");
        printf("|                        7.ǰ��                                |\n");
        printf("|                        8.���                                |\n");
        printf("|                        9.ɾ��                                |\n");
        printf("|                        10.�滻                               |\n");
        printf("|                        11.���������ӡ                       |\n");
        printf("|                        12.ǰ�������ӡ                       |\n");
        printf("|                        13.�˳�                               |\n");
        printf("|--------------------------------------------------------------|\n");
        printf("                        ��ѡ���ܣ�");
        scanf("%d",&k);
        switch(k)
        {
            case 0:{
                printf("�뽨��AVL����������Ҫ�����Ľ�������");
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
                    printf("          AVLΪ�գ�\n");
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
                    printf("          AVLΪ�գ�\n");
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
                    printf("          AVLΪ�գ�\n");
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
                    printf("          AVLΪ�գ�\n");
                break;
            }

            case 5:  {

                if(b.GetRoot())
                {
                    printf("Maxinum is ��");
                    cout<<b.BST_Maximum(b.GetRoot())->key;
                    printf("\n");
                }
                else
                    printf("          AVLΪ�գ�\n");
                break;
            }
            case 6: {
                if(b.GetRoot())
                {
                    printf("Mininum is ��");
                    cout<<b.BST_Minimum(b.GetRoot())->key;
                    printf("\n");
                }
                else
                    printf("          AVLΪ�գ�\n");
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
                    printf("          AVLΪ�գ�\n");
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
                cout<<"ǰ���ӡ���Ϊ��";
                b.preOrder_No_Stack();
                break;
            }
            case 13:{
                flag=0;
                printf("��������2����\n\n");
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

    /*********************************************����һ���ֽ���**********************************/

    cout<<"************************����3������֤BST��AVL�Ĳ��Һ����ߵĹ�ϵ*************************"<<endl;

    int TestGroups = 10;//���������10
    //srand(clock());testSearchTime�������Ѿ�����
    for(int i=1; i<=TestGroups; i++){
        cout<<"Group "<<i<<":"<<endl;
        testSearchTime(1000000);//��������1000000��������
        cout<<endl;
   }

    return 0;
}



