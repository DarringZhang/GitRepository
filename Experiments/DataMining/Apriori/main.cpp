#include <bits/stdc++.h>
using namespace std;
#define ITEMMAX 100

//定义存储事务的结构，每条事务最多包含100元素
typedef struct tag_TransactionItem{
    int item[ITEMMAX];
    int itemNum;  //最大值100；
}STTransactionItem,*STPTransactionItem;


typedef struct tag_Transaction{
    STTransactionItem transactions[ITEMMAX];
    int Trancount;
}Transaction;


//候选集结构的定义
typedef struct tag_CandidateItem{
    int item[ITEMMAX];
    int itemcount;
}STCondidateItem,*STPCondidateItem;

typedef struct tag_candidate{
    tag_CandidateItem items[ITEMMAX];
    int setNum;         //候选集元素个数
    int CandidateIndex; //候选集下标
}STCandidate,*STPCandidate;


//频繁集结构定义
typedef struct tag_FrequencyItem{
    int item[ITEMMAX];
    int itemcount;
}STFrequencyItem,*STPFreQuencyItem;

typedef  struct  tag_Frequency{
    tag_CandidateItem items[ITEMMAX];
    int setNum;         //频繁集元素个数
    int CandidateIndex; //频繁集下标，相当于算法里的K
}STFrequency,*STPFrequency;



Transaction curTransaction;
STCandidate curCandidates[ITEMMAX];
STFrequency curFrequencys[ITEMMAX];
int minup = 2;  //支持度


//输入数据集
void InitTransaction(){
    freopen("F://input.txt","r",stdin);
    //freopen("F://output.txt","w",stdout);

    printf("输入当前事务的记录条数：");
    scanf("%d",&(curTransaction.Trancount));


    for(int i = 0; i < curTransaction.Trancount; i ++){
        printf("输入第%d条记录的记录项数目",i);
        scanf("%d",&(curTransaction.transactions[i].itemNum));

        printf("输入%d条记录的记录项（以数值替代，并要求有序）:",i);
        for(int j = 0; j < curTransaction.transactions[i].itemNum; j++){
            scanf("%d",&(curTransaction.transactions[i].item[j]));
        }
    }

    fclose(stdin);
    //fclose(stdout);
}



//寻找频繁1-项集
void SearchFrequent_1_itemset(){
    int tranCount = curTransaction.Trancount;
    for(int i = 0; i < tranCount; i ++){
        int itemCount = curTransaction.transactions[i].itemNum;  //每一行的商品个数
        for(int j = 0; j < itemCount; j ++){  //每一行
            int candItemNum = curCandidates[0].setNum;
            bool isFind = false;

            //先在候选集中查找有没有这个元素
            for(int k = 0; k < candItemNum; k ++){
                if(curCandidates[0].items[k].item[0] == curTransaction.transactions[i].item[j]){
                    curCandidates[0].items[k].itemcount++;
                    isFind = true;
                    break;
                }
            }

            //没查找到，在候选项中找到属于元素的位置，插入
            if(!isFind){
                int k = 0;
                int index = 0;
                for(k = 0; k < candItemNum; k ++){ //因按大小顺序输入，直接比较大小找到位置
                    if(curCandidates[0].items[k].item[0] > curTransaction.transactions[i].item[j]){
                        break;
                    }
                }

                //候选集合向后挪一个位置，腾出空插入新的
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


    //根据支持度从候选项集中筛选出频繁
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
    //1-项集
    if(set_k < 1){
        return;
    }

    //由n-1项集生成n项集 n = 2,3,4...
    //策略：Fn-1 × Fn-1
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
    printf("候选集%d中共有%d个项集\n",set_k,setItems);
    for(int i = 0; i < setItems; i ++){
        for(int j = 0; j < curCandidates[set_k-1].CandidateIndex; j++){
            printf("%4d",curCandidates[set_k-1].items[i].item[j]);
        }
        printf("%8d\n",curCandidates[set_k-1].items[i].itemcount);
    }

}

void printFrequency(int set_k){
    int setItems = curFrequencys[set_k-1].setNum;
    printf("频繁集%d中共有%d项集\n",set_k,setItems);
    for(int i = 0; i < setItems; i ++){
        for(int j = 0; j < curFrequencys[set_k-1].CandidateIndex; j++){
            printf("%4d",curFrequencys[set_k-1].items[i].item[j]);
        }
        printf("%8d\n",curFrequencys[set_k-1].items[i].itemcount);
    }
}


void printTransaction(Transaction transaction){
    int tranCount = transaction.Trancount;
    printf("事务有%d条记录\n",tranCount);
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


