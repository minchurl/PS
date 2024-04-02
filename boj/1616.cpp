#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int MAXN = 10000005;
int k, m;
int n;
int idx[MAXN];
bool start = true;
int calcPow(int a, int b) { // return a^b
    int r = 1;
    while (b--) {
        r *= a;
    }
    return r;
}

void dfs(int u) {
    while (idx[u] < k) {
        int v = (u % (n / k)) * k + idx[u];
        idx[u]++;
        dfs(v);
    }
    if (!start) {
        printf("%d ", u / (n / k));
    }
    start = false;
}

int main() {
    scanf("%d %d", &k, &m);
    if (m == 1) {
        for (int i = 0; i < k; i++) {
            printf("%d ", i);
        }
        printf("\n");
        return 0;
    }

    n = calcPow(k, m - 1);
    dfs(0);
    printf("\n");
    return 0;
}