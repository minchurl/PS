#include<bits/stdc++.h>
using namespace std;
const int MAXN = 25;
int n, m, k;
int ord[MAXN];
int X[MAXN], Y[MAXN];
int is_possible() {
    for (int i = 0; i < m; i++) {
        if (ord[X[i]] + ord[Y[i]] > k) {
            return 0;
        }
    }
    return 1;
}
int calc(int p) {
    if (p >= n) {
        return is_possible();
    }

    int res = 0;

    for (int i = p; i <= n; i++) {
        swap(ord[i], ord[p]);
        res += calc(p + 1);
        swap(ord[i], ord[p]);
    }
    return res;
}
int main() {
    freopen("input.txt", "r", stdin);
    int TN;
    scanf("%d", &TN);
    for (int TC = 1; TC <= TN; TC++) {
        printf("Case #%d\n", TC);
        scanf("%d %d", &n, &k);
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &X[i], &Y[i]);
        }
        if (n > 8) {
            printf("0\n");
            continue;
        }
        for (int i = 1; i <= n; i++) {
            ord[i] = i;
        }
        printf("%d\n", calc(1));
    }
    return 0;
}