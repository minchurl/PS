#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
int n;
int V[MAXN][3];
int deg[MAXN];
bool isEaten[MAXN];
bool adj[MAXN][MAXN];
queue<int> Q;
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &V[i][0] ,&V[i][1], &V[i][2]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (V[i][0] >= V[j][0] && V[i][1] >= V[j][1] && V[i][2] >= V[j][2]) {
                if (V[i][0] == V[j][0] && V[i][1] == V[j][1] && V[i][2] == V[j][2] && i >= j) {
                    continue;
                }
                adj[i][j] = true;
                deg[i]++;
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            Q.push(i);
        }
    }

    while (Q.size()) {
        int p = Q.front();
        Q.pop();
        int c = 0;
        for (int i = 1; i <= n; i++) {
            if (adj[i][p]) {

            }
            if (adj[p][i]) {

            }
        }
    }
    return 0;
}