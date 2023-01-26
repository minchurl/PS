#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef pair<int, int> pii;
const int MAXH = 105;
const int MAXW = 105;
int h, w;
int col[MAXH][MAXW];
int num[MAXH][MAXW], n;
vector<int> adj[MAXH * MAXW];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
bool isInBoundary(int x, int y) {
    if (x < 1 || y < 1 || x > h || y > w) {
        return false;
    }
    return true;
}
void numbering(int i, int j, int number) {
    num[i][j] = number;
    for (int k = 0; k < 4; k++) {
        int x = i + dx[k];
        int y = j + dy[k];

        if (!isInBoundary(x, y) || col[i][j] != col[x][y] || num[x][y]) {
            continue;
        }
        numbering(x, y, number);
    }
}
void numbering() {
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (num[i][j]) {
                continue;
            }
            n++;
            numbering(i, j, n);
        }
    }
}
void generateGraph() {
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            for (int k = 0; k < 4; k++) {
                int x = i + dx[k];
                int y = j + dy[k];

                if (!isInBoundary(x, y) || num[i][j] == num[x][y]) {
                    continue;
                }
                adj[num[i][j]].pb(num[x][y]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        sort(all(adj[i])); adj[i].erase(unique(all(adj[i])), adj[i].end());
    }
}

queue<int> Q;
int dst[MAXH * MAXW];
int bfs(int st) {
    while(Q.size()) {
        Q.pop();
    }
    Q.push(st);
    for (int i = 1; i <= n; i++) {
        dst[i] = h + w;
    }
    dst[st] = 0;
    int res = 0;
    while (Q.size()) {
        int x = Q.front();
        res = dst[x];
        Q.pop();

        for (int y: adj[x]) {
            if (dst[y] <= dst[x] + 1) {
                continue;
            }
            dst[y] = dst[x] + 1;
            Q.push(y);
        }
    }
    return res;
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &h, &w);
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            scanf("%d", &col[i][j]);
        }
    }

    numbering();
    generateGraph();

    int res = h + w;
    for (int i = 1; i <= n; i++) {
        res = min(res, bfs(i));
    }

    printf("%d\n", res);
    return 0;
}