#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100000;
int t[MAXN + 5];
int main() {
    freopen("input.txt","r",stdin);
    for (int i = 1; i <= MAXN; i++) {
        t[i] = i;
    }
    for (int i = 3; i <= MAXN; i++) {
        t[i] = min(t[i], t[i - 1] + 1);
        for (int j = 2; i * j <= MAXN; j++) {
            t[i * j] = min(t[i * j], t[i] + 2 + 2 * j);
        }
    }

    int TC;
    scanf("%d", &TC);
    for (int TI = 1; TI <= TC; TI++) {
        int n;
        scanf("%d", &n);
        printf("Case #%d: %d\n", TI, t[n]);
    }
    return 0;
}