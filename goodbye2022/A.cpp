#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5000;
const int MAXT = 505;
int isWhat[MAXN + 5]; // 0 -> 부족, 1 -> 완전, 2 -> 과잉
int main() {
    freopen("input.txt", "r", stdin);
    for (int i = 1; i <= MAXN; i++) {
        int sumPrime = 0;
        for (int j = 1; j < i; j++) {
            if (i % j == 0) {
                sumPrime += j;
            }
        }
        if (sumPrime < i) {
            isWhat[i] = 0;
        }
        else if (sumPrime == i) {
            isWhat[i] = 1;
        }
        else {
            isWhat[i] = 2;
        }
    }
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        if (isWhat[n] != 2) {
            printf("BOJ 2022\n");
            continue;
        }
        int j = 1;
        for (; j < n; j++) {
            if (n % j == 0 && isWhat[j] == 2) {
                break;
            }
        }
        if (j != n) {
            printf("BOJ 2022\n");
        }
        else {
            printf("Good Bye\n");
        }
    }
    return 0;
}