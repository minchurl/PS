#include "bits/stdc++.h"
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long LL;
const int MAXN = 405;
const int MAXK = 805;
const int MAXM = 2 * MAXK + MAXN + 2;
int n, k;
int m;
int flow[MAXM][MAXM];
int val[MAXM];
int from[MAXM];
queue<int> Q;
bool is_in_queue[MAXM];
void SPFA_init() {
    for (int i = 0; i <= m; i++) {
        val[i] = 0;
        from[i] = -1;
        is_in_queue[i] = false;
    }

    while (Q.size()) {
        Q.pop();
    }
    val[0] = 1;
    Q.push(0);
    is_in_queue[0] = true;

}
int SPFA() {
    SPFA_init();
    while (Q.size()) {
        int u = Q.front();
        Q.pop();
        is_in_queue[u] = false;
        for (int v = 0; v <= m; v++) {
            if (flow[u][v] == 0 || val[v] != 0) {
                continue;
            }
            // insert edge u -> v
            val[v] = 1;
            from[v] = u;
            Q.push(v);
            is_in_queue[v] = true;

            if (v == m) {
                return 1;
            }
        }
    }
    return 0;
}
void construct_back_edge() {
    int v = m;
    while (v != 0) {
        int u = from[v];
        flow[u][v]--;
        flow[v][u]++;

        v = u;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &k);
    m = 2 * k + n + 1;
    // source : 0
    // layer 1 : 1 ~ k
    // layer 2 : k + 1 ~ 2k
    // layer 3 : 2k + 1 ~ 2k + n
    // sink : m = 2k + n + 1
    for (int i = 1; i <= k; i++) {
        // source to layer 1
        flow[0][i] = 1 - i % 2;
        for (int j = i; j <= k; j++) {
            // layer 1 to layer 1
            flow[i][j] = 1;
        }
        // layer 1 to layer 2
        flow[i][k + i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            int f;
            scanf("%d", &f);
            // later 2 to layer 3
            flow[k + j][2 * k + i] = f;
        }
        // layer 3 to sink
        flow[2 * k + i][m] = 1;
    }

    // flow

    int res = 0;
    while (true) {
        int f = SPFA();
        if (f == 0) {
            break;
        }
        res += f;
        construct_back_edge();
    }

    printf("%d\n", res);
    return 0;
}