#include<bits/stdc++.h>
using namespace std;
int main() {
    int a, b, c;
    scanf("%d-%d-%d", &a, &b, &c);

    if (b < 9) {
        return !printf("GOOD\n");
    }
    if (b == 9 && c <= 16) {
        return !printf("GOOD\n");
    }
    printf("TOO LATE\n");
    return 0;
}