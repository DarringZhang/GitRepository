//
// Created by lenovo on 2019/6/2.
//

#ifndef M_COLOR_COLOR_H
#define M_COLOR_COLOR_H

class Color{
    friend int mColoring(int,int,int(*)[4]);

private:
    bool Ok(int k);
    void Backtrack(int i);
    int n;//图的顶点数
    int m;//可用颜色数
    int **a;//图的邻接矩阵
    int *x;//当前解
    long sum;//当前已找到的着色方案树

};

bool Color:: Ok(int k){
    //检查颜色可用性
    for(int i = 1; i <= n; ++i){
        if((a[k][i]==1)&&(x[i] == x[k])){
            return false;
        }
    }
    return true;
};

void Color::Backtrack(int t){

    if (t>n) {
        sum++;
        for (int i=1; i<=n; i++)
            std::cout << x[i] << ' ';
        std::cout << std::endl;
    }
    else
        for (int i=1;i<=m;i++) {
            x[t]=i;
            if (Ok(t)) Backtrack(t+1);
            x[t] = 0;
        }

}

int mColoring(int n,int m,int (*a)[4]){
    Color X;
    X.n = n;
    X.m = m;
    X.a = a;
    X.sum = 0;
    int *p = new int[n+1];
    for(int i = 0; i <= n; ++i){
        p[i] = 0;
    }
    X.x = p;//当前解
    X.Backtrack(1);
    delete [] p;
    return X.sum;
}


#endif //M_COLOR_COLOR_H
