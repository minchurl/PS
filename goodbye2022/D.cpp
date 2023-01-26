#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 505;
const int MAXM = 505;
int n, m;
LL X;
int k;
LL V[MAXN][MAXM], originalV[MAXN][MAXN];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
bool isInBound(int x, int y) {
    if (x < 1 || y < 1 || x > n || y > m) {
        return false;
    }
    return true;
}

int dfs(int x, int y, LL d) {
    int i;
    int res = 0;
    for (i = 0; i < 4; i++) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (!isInBound(xx, yy) || V[xx][yy] - V[x][y] <= d) {
            continue;
        }
        break;
    }
    if (i != 4) {
        res++;
        V[x][y] = X;
    }
    else {
        return 0;
    }

    for (i = 0; i < 4; i++) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (!isInBound(xx, yy) || V[x][y] - V[xx][yy] <= d) {
            continue;
        }
        res += dfs(xx, yy, d);
    }
    return res;
}
bool isPossible(LL d) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            V[i][j] = originalV[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            sum += dfs(i, j, d);
        }
    }
    return sum <= k;
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d %d %lld", &n, &m, &k, &X);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &originalV[i][j]);
        }
    }
    LL l = 0;
    LL r = X;
    while (l < r) {
        LL mid = (l + r) >> 1;
        if (isPossible(mid)) {
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }
    printf("%lld\n", l);
    return 0;
}