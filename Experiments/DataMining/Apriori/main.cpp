#include <bits/stdc++.h>
using namespace std;
#define ITEMMAX 100

//����洢����Ľṹ��ÿ������������100Ԫ��
typedef struct tag_TransactionItem{
    int item[ITEMMAX];
    int itemNum;  //���ֵ100��
}STTransactionItem,*STPTransactionItem;


typedef struct tag_Transaction{
    STTransactionItem transactions[ITEMMAX];
    int Trancount;
}Transaction;


//��ѡ���ṹ�Ķ���
typedef struct tag_CandidateItem{
    int item[ITEMMAX];
    int itemcount;
}STCondidateItem,*STPCondidateItem;

typedef struct tag_candidate{
    tag_CandidateItem items[ITEMMAX];
    int setNum;         //��ѡ��Ԫ�ظ���
    int CandidateIndex; //��ѡ���±�
}STCandidate,*STPCandidate;


//Ƶ�����ṹ����
typedef struct tag_FrequencyItem{
    int item[ITEMMAX];
    int itemcount;
}STFrequencyItem,*STPFreQuencyItem;

typedef  struct  tag_Frequency{
    tag_CandidateItem items[ITEMMAX];
    int setNum;         //Ƶ����Ԫ�ظ���
    int CandidateIndex; //Ƶ�����±꣬�൱���㷨���K
}STFrequency,*STPFrequency;



Transaction curTransaction;
STCandidate curCandidates[ITEMMAX];
STFrequency curFrequencys[ITEMMAX];
int minup = 2;  //֧�ֶ�


//�������ݼ�
void InitTransaction(){
    freopen("F://input.txt","r",stdin);
    //freopen("F://output.txt","w",stdout);

    printf("���뵱ǰ����ļ�¼������");
    scanf("%d",&(curTransaction.Trancount));


    for(int i = 0; i < curTransaction.Trancount; i ++){
        printf("�����%d����¼�ļ�¼����Ŀ",i);
        scanf("%d",&(curTransaction.transactions[i].itemNum));

        printf("����%d����¼�ļ�¼�����ֵ�������Ҫ������:",i);
        for(int j = 0; j < curTransaction.transactions[i].itemNum; j++){
            scanf("%d",&(curTransaction.transactions[i].item[j]));
        }
    }

    fclose(stdin);
    //fclose(stdout);
}



//Ѱ��Ƶ��1-�
void SearchFrequent_1_itemset(){
    int tranCount = curTransaction.Trancount;
    for(int i = 0; i < tranCount; i ++){
        int itemCount = curTransaction.transactions[i].itemNum;  //ÿһ�е���Ʒ����
        for(int j = 0; j < itemCount; j ++){  //ÿһ��
            int candItemNum = curCandidates[0].setNum;
            bool isFind = false;

            //���ں�ѡ���в�����û�����Ԫ��
            for(int k = 0; k < candItemNum; k ++){
                if(curCandidates[0].items[k].item[0] == curTransaction.transactions[i].item[j]){
                    curCandidates[0].items[k].itemcount++;
                    isFind = true;
                    break;
                }
            }

            //û���ҵ����ں�ѡ�����ҵ�����Ԫ�ص�λ�ã�����
            if(!isFind){
                int k = 0;
                int index = 0;
                for(k = 0; k < candItemNum; k ++){ //�򰴴�С˳�����룬ֱ�ӱȽϴ�С�ҵ�λ��
                    if(curCandidates[0].items[k].item[0] > curTransaction.transactions[i].item[j]){
                        break;
                    }
                }

                //��ѡ�������Ųһ��λ�ã��ڳ��ղ����µ�
                index = k;
                for(int m = candItemNum; m > index; m --){
                    curCandidates[0].items[m] = curCandidates[0].items[m-1];
                }
                curCandidates[0].items[index].itemcount = 1;
                curCandidates[0].items[index].item[0] = curTransaction.transactions[i].item[j];
                curCandidates[0].setNum++;
            }
        }
    }


    //����֧�ֶȴӺ�ѡ���ɸѡ��Ƶ��
    int setItems = curCandidates[0].setNum;
    int j = 0;
    for(int i = 0; i < setItems; i ++){
        if(curCandidates[0].items[i].itemcount >= minup){
            curFrequencys[0].items[j++] = curCandidates[0].items[i];
        }
    }

    curFrequencys[0].setNum = j;
    curFrequencys[0].CandidateIndex = 1;
    curCandidates[0].CandidateIndex = 1;
}


void apriori_gen(int set_k){
    //1-�
    if(set_k < 1){
        return;
    }

    //��n-1�����n� n = 2,3,4...
    //���ԣ�Fn-1 �� Fn-1
    int setnum = curFrequencys[set_k-2].setNum;
    int candNum = 0;
    for(int i = 0; i < setnum; i++){
        for(int j = i+1; j < setnum; j++){
            bool isUnion = true;
            for(int k = 0; k < set_k-2; k++){
                if(curFrequencys[set_k-2].items[i].item[k] != curFrequencys[set_k-2].items[j].item[k]){
                    isUnion = false;
                    break;
                }
            }

            if(isUnion){
                curCandidates[set_k-1].items[candNum] = curFrequencys[set_k-2].items[i];
                curCandidates[set_k-1].items[candNum].item[set_k-1] = curFrequencys[set_k-2].items[j].item[set_k-2];
                curCandidates[set_k-1].items[candNum].itemcount = 0;
                candNum ++;
            }
        }
    }

    curCandidates[set_k-1].CandidateIndex = set_k;

    int i,m,n,l;
    int validCanNum = 0;
    for(i = 0; i < candNum; i++){
        curCandidates[set_k-1].items[validCanNum] = curCandidates[set_k-1].items[i];
        int tranCount = curTransaction.Trancount;
        for(m = 0; m < tranCount; m++){
            int itemCount = curTransaction.transactions[m].itemNum;
            for(n = 0, l = 0;n < itemCount && l < set_k; n++){
                if(curCandidates[set_k-1].items[validCanNum].item[l] == curTransaction.transactions[m].item[n]){
                    l ++;
                    continue;
                }
                else if(curCandidates[set_k-1].items[validCanNum].item[l] < curTransaction.transactions[m].item[n]){
                    break;
                }
            }

            if(l == set_k){
                curCandidates[set_k-1].items[validCanNum].itemcount++;
            }
        }

        if(curCandidates[set_k-1].items[validCanNum].itemcount > 0){
            validCanNum ++;
        }
    }
    curCandidates[set_k-1].setNum = validCanNum;

}

void GetFrequency_set_k(int set_k){
    int i,j=0;
    int setItems = curCandidates[set_k-1].setNum;
    for(i = 0; i < setItems; i++){
        if(curCandidates[set_k-1].items[i].itemcount > minup){
            curFrequencys[set_k - 1].items[j++] = curCandidates[set_k-1].items[i];
        }
    }

    curFrequencys[set_k-1].setNum = j;
    curFrequencys[set_k-1].CandidateIndex = set_k;
}


void printCandidate(int set_k){
    int setItems = curCandidates[set_k-1].setNum;
    printf("��ѡ��%d�й���%d���\n",set_k,setItems);
    for(int i = 0; i < setItems; i ++){
        for(int j = 0; j < curCandidates[set_k-1].CandidateIndex; j++){
            printf("%4d",curCandidates[set_k-1].items[i].item[j]);
        }
        printf("%8d\n",curCandidates[set_k-1].items[i].itemcount);
    }

}

void printFrequency(int set_k){
    int setItems = curFrequencys[set_k-1].setNum;
    printf("Ƶ����%d�й���%d�\n",set_k,setItems);
    for(int i = 0; i < setItems; i ++){
        for(int j = 0; j < curFrequencys[set_k-1].CandidateIndex; j++){
            printf("%4d",curFrequencys[set_k-1].items[i].item[j]);
        }
        printf("%8d\n",curFrequencys[set_k-1].items[i].itemcount);
    }
}


void printTransaction(Transaction transaction){
    int tranCount = transaction.Trancount;
    printf("������%d����¼\n",tranCount);
    for(int i = 0; i < tranCount; i++){
        printf("%d:   ",i);
        int itemCount = transaction.transactions[i].itemNum;
        for(int j = 0; j < itemCount; j++){
            printf("%4d",transaction.transactions[i].item[j]);
        }
        printf("\n");
    }
}

int main() {
    InitTransaction();
    printTransaction(curTransaction);
    SearchFrequent_1_itemset();
    printCandidate(1);
    printFrequency(1);

    int set_k = 2;
    while(true){
        apriori_gen(set_k);
        if(curCandidates[set_k-1].setNum == 0){
            break;
        }

        GetFrequency_set_k(set_k);
        printCandidate(set_k);
        printFrequency(set_k);
        set_k++;
    }
    return 0;
}


