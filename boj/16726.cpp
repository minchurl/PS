#include<bits/stdc++.h>

#define fi first
#define se second

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 55;
const int MAXM = 55;

int n, m;
int adj[MAXN][MAXM][MAXN][MAXM];


bool isInBoundary(int i, int j) {
    if (i < 0 || j < 0 || i >= n || j >= m) {
        return false;
    }
    return true;
}

pii from[MAXN][MAXM];
bool isVisited[MAXN][MAXM];

bool findPath(int i, int j) {
    isVisited[i][j] = true;
    if (i == n && j == 1) {
        return true;
    }
    for (int ii = 0; ii <= n; ii++) {
        for (int jj = 0; jj <= m; jj++) {
            if (!adj[i][j][ii][jj] || isVisited[ii][jj]) {
                continue;
            }
            from[ii][jj] = pii(i, j);
            if (findPath(ii, jj)) {
                return true;
            }
        }
    }
    return false;
}

void initArray() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            from[i][j] = pii(-1, 0);
            isVisited[i][j] = false;
        }
    }
}

bool findPath() {
    initArray();
    return findPath(n, 0);
}

void updateAdj(int i, int j) {
    if (i == n && j == 0) {
        return;
    }
    pii p = from[i][j];
    int ii = p.fi;
    int jj = p.se;

    adj[i][j][ii][jj]++;
    adj[ii][jj][i][j]--;

    updateAdj(ii, jj);
}

void updateAdj() {
    updateAdj(n, 1);
}

void initAdj() {

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i + j) % 2 == 1) {
                continue;
            }
            for (int k = 0; k < 4; k++) {
                int ii = i + dx[k];
                int jj = j + dy[k];
                if (isInBoundary(ii, jj)) {
                    adj[i][j][ii][jj] = 1;
                }
            }
        }
    }

}

int main() {
    freopen("input.txt","r",stdin);
    scanf("%d %d", &n, &m);
    int blanked = 0;
    char Map[MAXN][MAXM];

    initAdj();

    for (int i = 0; i < n; i++) {
        scanf("%s", Map[i]);
        for (int j = 0; j < m; j++) {
            if (Map[i][j] == '.') {
                blanked++;
                if ((i + j) % 2 == 0) {
                    adj[n][0][i][j] = 1;
                }
                else {
                    adj[i][j][n][1] = 1;
                }
            }
        }
    }
    int max1x2Block = 0;
    while (true) {
        bool delta = findPath();
        if (delta == false) {
            break;
        }
        max1x2Block++;
        updateAdj();
    }
    int res = blanked - max1x2Block;
    printf("%d\n", res);
    return 0;
}