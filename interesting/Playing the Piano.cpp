#include <Windows.h>
#include<conio.h>
#include<stdio.h>
int main(int argc, char const *argv[])
{
    char c='c';
    int i,j;
    int m[] = { 0, 523, 587, 659, 698, 784, 880, 932,1046,1175};
    int s[] = { 1, 1, 5, 5, 6, 6, 5, 4, 4, 3, 3, 2, 2, 1 };
    int t[] = { 300, 300, 300, 300, 300, 300, 350, 300, 300, 300, 300, 300, 300, 300 };
    int a='1'-1;

    do{
        printf("按1播放小星星\n按2通过键盘数字发出相应的声调\n按其他任意键退出：\n");
        scanf("%d",&j);
        getchar();
        switch(j)
        {
            case 1:
                for(i=0;i<14;i++)
                {
                    Beep(m[s[i%14]], 300);
                    Sleep(270);
                    if(i==6)
                        Sleep(270);
                }
                break;
            case 2:
                printf("在弹奏时可以按0退出\n");
                while((i=getch()-a)!=0)
                {
                    Beep(m[i], 300);
                }
                break;
            default:
                c='0';
                break;
        }
        if(c=='c') printf("按c继续，任意键退出:\n");
    }while(scanf("%c",&c)&&c=='c');
    return 0;
}

