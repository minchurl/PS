#include<bits/stdc++.h>
using namespace std;
int n;
int main() {
    freopen("input.txt", "r", stdin);
    int TC;
    scanf("%d", &TC);
    while (TC--) {
        scanf("%d", &n);
        int sum = 0;
        int res = 100;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            sum += x;
            int y = x % 2;
            int val = 0;
            while (x % 2 == y) {
                x /= 2;
                val++;
            }
            res = min(res, val);
        }
        if (sum % 2) {
            printf("%d\n", res);
        }
        else {
            printf("0\n");
        }
    }
    return 0;
}