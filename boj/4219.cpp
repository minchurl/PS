#include<bits/stdc++.h>
using namespace std;
const int MAXDX = 1005;
const int MAXDY = 1005;
int dx, dy, n, q;
int bound;
int sum[MAXDX + MAXDY][MAXDX + MAXDY];
int get_cafe(int sx, int sy, int ex, int ey) {
    sx = sx > 1 ? sx : 1;
    sy = sy > 1 ? sy : 1;
    ex = ex < bound ? ex : bound;
    ey = ey < bound ? ey : bound;
    return sum[ex][ey] - sum[ex][sy - 1] - sum[sx - 1][ey] + sum[sx - 1][sy - 1];
}
int main() {
    freopen("input.txt", "r", stdin);
    for(int TC = 1;; TC++){
        scanf("%d %d %d %d", &dx, &dy, &n, &q);
        if (dx == 0 && dy == 0 && n == 0 && q == 0) {
            return 0;
        }
        bound = dx + dy - 1;
        printf("Case %d:\n", TC);
        memset(sum, 0, sizeof(sum));
        for (int i = 1; i <= n; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            sum[x + y - 1][x - y + dy]++;
        }
        for (int i = 1; i <= bound; i++) {
            for (int j = 1; j <= bound; j++) {
                sum[i][j] += sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
            }
        }
        while (q--) {
            int m;
            scanf("%d", &m);
            int res = 0;
            int resx = 1;
            int resy = 1;
            for (int y = 1; y <= dy; y++) {
                for (int x = 1; x <= dx; x++) {
                    int sx = x + y - m - 1;
                    int sy = x - y - m + dy;
                    int ex = x + y + m - 1;
                    int ey = x - y + m + dy;
                    if (res < get_cafe(sx, sy, ex, ey)) {
                        resx = x;
                        resy = y;
                        res = get_cafe(sx, sy, ex, ey);
                    }
                }
            }
            printf("%d (%d,%d)\n", res, resx, resy);
        }
    }
    return 0;
}