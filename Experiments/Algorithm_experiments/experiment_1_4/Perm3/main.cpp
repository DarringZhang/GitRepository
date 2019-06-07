
#include <iostream>
using namespace std;
void init(int *arr, int start, int end);
void initSrc(int *arr, int start, int end);
void print(int *arr, int start, int end);
void stackInOrOut(int *src, int *st, int *dest, int index, int size, bool flag);
int main()
{
    int size;
    cout << "please input size of src:" << endl;
    cin >> size;
    int *src = new int[size];
    int *st = new int[size + 1], *dest = new int[size + 1];
    initSrc(src, 0, size - 1);
    init(st, 0, size);
    init(dest, 0, size);
    stackInOrOut(src, st, dest, 0, size, true);   //刚开始只能入栈，不能出栈
    delete []src;
    delete []st;
    delete []dest;
}

void init(int *arr, int start, int end)
{
    for (int i = start; i <= end; ++i)
        arr[i] = 0;
}
void initSrc(int *arr, int start, int end)
{
    for (int i = start; i <= end; ++i)
        arr[i] = i + 1;
}
void print(int *arr, int start, int end)
{
    static int count = 1;
    cout << "count = " << count << ",arr[0] = " << arr[0] << '\t';
    for (int i = start; i <= end; ++i)
        cout << arr[i] << ' ';
    cout << endl;
    ++count;
}

void stackInOrOut(int *src, int *st, int *dest, int index, int size, bool flag) {
    if (index == size) {
        if (flag == true)    //如果是入栈，打印结果，出栈直接退出
        {
            int j = dest[0];
            for (int i = st[0]; i != 0; --i)
                dest[++j] = st[i];
            print(dest, 1, size);
        }
        return;
    }
    if (true == flag) {
        st[++st[0]] = src[index];        //进栈
        stackInOrOut(src, st, dest, index + 1, size, true);
        stackInOrOut(src, st, dest, index + 1, size, false);
        --st[0];                        //恢复top指针
    } else {
        if (st[0] != 0) {
            dest[++dest[0]] = st[st[0]--];                    //出栈顶元素到目标数组
            stackInOrOut(src, st, dest, index, size, true);
            stackInOrOut(src, st, dest, index, size, false);
            ++st[0];                                        //恢复top指针
            st[st[0]] = dest[dest[0]];                        //问题出在这里，原来的程序没有恢复栈中元素的值，只是恢复了top指针
            --dest[0];                                        //恢复目标数组top指针
        }
    }
}