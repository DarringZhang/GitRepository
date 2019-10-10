#include <stdio.h>
#include <stdlib.h>

#define max 1000

int main() {
    char a[max], b[max], c[max];
    int T;
    int i, j, k, x;
    int p = 0;
    char *address[100];
    scanf("%d", &T);
    for (x = 0; x < T; x++) {
        /*以读入字符串的方式输入两个我们需要进行加法运算的两个大正整数，并实现多组输入*/
        while (scanf("%s%s", a, b)!= EOF) {
            /*将存储结果的字符数组初始化为'0'*/
            for (i = 0; i < max - 1; i++)
                c[i] = '0';
            c[max - 1] = '\0';
            /*找到字符数组a的最后一个字符，然后整体移到字符数组尾*/
            for (i = 0; a[i]; i++);
            j = i - 1;
            k = max - 2;
            for (; i < max - 1; i++)
                a[i] = '0';
            i = j;
            for (; i >= 0; i--) {
                a[k] = a[i];
                k--;
                a[i] = '0';
            }
            a[max - 1] = '\0';
            /*对字符数组b进行与上相同的操作*/
            for (i = 0; b[i]; i++);
            j = i - 1;
            k = max - 2;
            for (; i < max - 1; i++)
                b[i] = '0';
            i = j;
            for (; i >= 0; i--) {
                b[k] = b[i];
                k--;
                b[i] = '0';
            }
            b[max - 1] = '\0';
            /*开始进行加法运算*/
            for (i = max - 2; i >= 0; i--) {
                /*因为我们字符数组存的每一个元素都是字符而不是数字，因此必须注意+-'0'的细节*/
                c[i] = c[i] + a[i] + b[i] - '0' - '0';
                j = i;
                /*进位处理*/
                if ((c[j] - '0') > 9) {
                    c[j] = (c[j] - '0') % 10 + '0';
                    c[j - 1]++;
                }
            }
            /* 处理前面多余的'0'：找到第一个不是'0'的元素，然后从该位置开始整体向前移并在结尾添上'\0'，大正整数相加的结果就出来了*/
            for (i = 0; c[i] == '0'; i++);
            j = i;
            for (k = 0; i <= max - 2; i++) {
                c[k++] = c[i];
                c[i] = '0';
            }
            c[max - 1 - j] = '\0';
            address[p] = c;
        }
        p++;
    }
    for(int w = 0; w < T; w++){
        printf("%s", address[w]);
    }
    return 0;
}