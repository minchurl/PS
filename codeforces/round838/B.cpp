#include<bits/stdc++.h>
using namespace std;
int n;
int main() {
    freopen("input.txt", "r", stdin);
    int TC;
    scanf("%d", &TC);
    while (TC--) {
        scanf("%d", &n);
        printf("%d\n", n);
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            int y = 1;
            while (y <= x) {
                y *= 2;
            }
            printf("%d %d\n", i, y - x);
        }
    }
    return 0;
}