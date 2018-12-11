#include <iostream>
#include <map>
using namespace std;
/*
 * һֻ����һ�ο�������1��̨�ף�Ҳ��������2���������������һ��n����̨���ܹ��ж���������
 *
 * ָ�����ĸ��Ӷȵݹ飺
 * 1.��һ�����������������һ������֮��Ĺ�ϵ��

������n��̨�ף�����һ��n����̨�׵���������Ϊf(n).

���������Ĺ����У�ÿһ������������������һ��������̨�ס�

 ��һ����������һ��������һ��̨�ף���ô��ʣ��n-1��̨�׻�û����ʣ�µ�n-1��̨�׵�������f(n-1)�֡�

������

�ڶ�����������һ����������̨�ף���ô��ʣ��n-2��̨�׻�û��ʣ�µ�n-2��̨�׵�������f(n-2)�֡�

�ɴ˲��ѵó��ݹ鹫ʽ��f(n) = f(n-1) + f(n-2);



2.�ڶ������ҳ��ݹ�Ľ�������

    ��n <= 0ʱ������Ϊ0������ʱf(n) = 0

    ��ֻʣ��һ��̨��n = 1ʱ����ôֻ��һ����������f(1) = 1;

    ��n = 2ʱ����ʱ����Ϊ2�֣���f(2) = 2;
 * */

int f1(int n){
    if(n<=0){
        return 0;
    }
    else if(n<=2){
        return n;
    }
    else{
        return f1(n-1)+f1(n-2);
    }
}

/*�Ż������ڼ������f(n)��������һ��map�������棬n��Ϊkey,f(n)��Ϊvalue;
 * ÿ�εݹ�ʱ���Ȳ鿴һ��f(n)�Ƿ��Ѿ�������ˣ�����ֱ��ȡ�����񣬼��㲢put into map;
 * */
map<int,int> map_f2;//���Ҹ��Ӷ�logn
int f2(int n){
    if(n<=0){
        return 0;
    }
    else if(n<=2){
        return n;
    }
    else{
        if(map_f2.count(n)==1){
            return map_f2[n];
        }
        else{
            int m = f2(n-1)+f2(n-2);
            map_f2.insert(pair<int, int>(n,m));
            return m;
        }

    }
}

/*
 * ����f(n) = f(n-1) + f(n-2)��������ʽ����쳲���������
 *
 */

int f3(int n){
    if(n<=0){
        return 0;
    }
    else if(n<=2){
        return n;
    }
    //쳲�������������ѭ��Ƕ�ף����¶���
    int fa = 0;
    int fb = 1;
    int sum = 0;
    for(int i = 1; i <= n; ++i){
        sum = fa + fb;
        fa = fb;
        fb = sum;
    }
    return sum;
}



/*
 * ����2�� һֻ����һ�ο�������1��̨�ף�Ҳ��������2��������Ҳ��������n����
 * �����������һ��n����̨���ܹ��ж�����������
 * */
map<int,int> map_f4;
int f4(int n){
    if(n<=0){
        return 0;
    }
    else if(n<=2){
        return n;
    }
    else{
        int m = 0;
        //int m = f4(n-1)+f4(n-2);
        for(int i = 1; i <= n; ++i){
            m += f4(n-i);
        }
        map_f4.insert(pair<int, int>(n,m)); // f��n�� = f(n-1) + f(n-2) +......+f(1)
        return m;
    }

}

int main() {
    int num;
    while(scanf("%d",&num)&&num){
        cout<<"�ݹ�:"<<f1(num)<<endl;
        cout<<"map�Ż�"<<f2(num)<<endl;
        cout<<"쳲�����"<<f3(num)<<endl;
        cout<<"��ʽ��"<<f4(num)<<endl;
    }



    return 0;
}