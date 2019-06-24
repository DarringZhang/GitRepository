#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class LuckyElevator {
public:
    int actualFloor(int);
};

bool has_four(int f){
    while(f!= 0){
        if(f%10 == 4){
            return true;
        }
       f /= 10;
    }
    return false;
}


int LuckyElevator::actualFloor(int buttonPressed) {
    for(int i = 0,flag = 0; i < buttonPressed; i++,flag++){
        while(has_four(flag)){
           flag ++;
        }

        if(flag == buttonPressed){
            return i;
        }

    }
}


int main(){
    LuckyElevator a;


    cout << a.actualFloor(100000) << endl;
}