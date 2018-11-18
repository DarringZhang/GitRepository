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
    printf("                     ������ʵ�ֶ����������Ļ���������\n");
    printf("���Խ��н���BST,�ݹ���룬�ǵݹ���룬�ݹ����ĳ���ض���ֵ���ǵݹ����ĳ���ض���ֵ�����������С���Һ�̣�ǰ����ɾ����,�滻��ǰ/���������ӡ���˳��Ȳ�����\n");

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
        printf("|                        12.���������ӡ�������ִ�С����       |\n");
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
                printf("�����������У��˳�������\n");
                break;
            }

            default:{
                cout<<"input error,please input again"<<endl;
                break;
            }

        }
    }

    a.destroy(a.GetRoot());

    cout<<"************************���������֤BST���Ĳ��Һ����ߵĹ�ϵ*************************"<<endl;

    clock_t start,finish;
    double total_time;
    int value;

    cout<<"����С�����˳�����100000������BST���Ϊһ����,AVL�߶�ƽ�⣬�ٲ���"<<endl;
    for(int i = 1 ;i <= 50000;i++){
        a.BST_Insert_NonRecur(a.GetRoot(),i);
    }




    for(int i = 1 ;i <= 50000;i++){
        b.AVL_Insert(b.GetRoot(),i);
    }


    cout<<"��������Ҫ���ҵ�ֵ:";
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



