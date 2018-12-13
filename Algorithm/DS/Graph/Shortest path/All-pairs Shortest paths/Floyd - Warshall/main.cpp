#include "Floyd.h"

int main() {
    Floyd f;
    f.CreateGraph(6,11);
    f.Calculate_floyd();
    return 0;
}