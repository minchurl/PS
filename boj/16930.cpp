#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 1005;
const int MAXM = 1005;
int n, m, k;
char mapStr[MAXN][MAXM];
pii st, dest;
int dst[MAXN][MAXM];
queue<pii> Q;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool isVaildPoint(int x, int y) {
    if (x < 1 || y < 1 || x > n || y > m) {
        return false;
    }
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%s", mapStr[i] + 1);
        for (int j = 1; j <= m; j++) {
            dst[i][j] = -1;
        }
    }
    scanf("%d %d %d %d", &st.fi, &st.se, &dest.fi, &dest.se);
    dst[st.fi][st.se] = 0;
    Q.push(st);
    while (Q.size()) {
        pii cur = Q.front();
        Q.pop();
        int cx = cur.fi;
        int cy = cur.se;
        for (int i = 0; i < 4; i++) {
            for (int j = 1; j <= k; j++) {
                int nx = cx + j * dx[i];
                int ny = cy + j * dy[i];
                if (!isVaildPoint(nx, ny) || (dst[nx][ny] != -1 && dst[nx][ny] <= dst[cx][cy]) || mapStr[nx][ny] == '#') {
                    break;
                }
                if (dst[nx][ny] == -1) {
                    dst[nx][ny] = dst[cx][cy] + 1;
                    Q.push({nx, ny});
                }
            }
        }
    }

    printf("%d\n", dst[dest.fi][dest.se]);
    return 0;
}