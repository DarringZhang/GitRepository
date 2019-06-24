#include <iostream>
using namespace std;

class LuckyElevator {
public:
	int actualFloor(int);
};
bool check(int i){
    while (i > 1){
        if (i % 10 == 4){
            return false;
        }
        i /= 10;
    }
    return true;
}
int LuckyElevator::actualFloor(int buttonPressed) {
	int cnt = 0, ans = 0;
    for (int i = 1; i <= buttonPressed; i++){
        if (!check(i)){
            cnt++;
        }
    }
    return buttonPressed - cnt;
}
