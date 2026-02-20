#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = 1005;
const int MAXM = 2005;
const LL inf = (1LL<<60);
struct Frac{
    Frac() {}
    Frac(LL _p, LL _q) {
        p = _p;
        q = _q;
    }
    LL p, q;
};
Frac get_max(Frac x, Frac y) {
    return (x.p * y.q > x.q * y.p) ? x : y;
}

Frac get_min(Frac x, Frac y) {
    return (x.p * y.q < x.q * y.p) ? x : y;
}

LL H[MAXN][MAXN];
LL G[MAXN][MAXN];
bool vis[MAXN];
int n, m;
int U[MAXM], V[MAXM];
LL C[MAXM];
int HI[MAXN];
bool CHI[MAXM];

void init_vis() {
    for (int i = 1; i <= n; i++) {
        vis[i] = false;
    }
}
void is_H_st(int u) {
    vis[u] = true;
    for (int i = 1; i <= n; i++) {
        if (H[u][i] != inf && !vis[i]) {
            is_H_st(i);
        }
    }
}
bool is_H_st() {
    init_vis();
    is_H_st(1);
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            return false;
        }
    }
    return true;
}
void init_H() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            H[i][j] = inf;
        }
    }

    for (int i = 1; i < n; i++) {
        int u = U[HI[i]];
        int v = V[HI[i]];
        H[u][v] = H[v][u] = C[i];
    }
}
void calc_H() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (k == i) {
                continue;
            }
            for (int j = 1; j <= n; j++) {
                if (k == j || i == j) {
                    continue;
                }
                if (H[i][k] + H[k][j] < H[i][j]) {
                    H[i][j] = H[i][k] + H[k][j];
                }
            }
        }
    }
}
void init_G() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            G[i][j] = inf;
        }
    }

    for (int i = 1; i <= m; i++) {
        int u = U[i];
        int v = V[i];
        G[u][v] = G[v][u] = C[i];
    }

}
void calc_G() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (k == i) {
                continue;
            }
            for (int j = 1; j <= n; j++) {
                if (k == j || i == j) {
                    continue;
                }
                if (G[i][k] + G[k][j] < G[i][j]) {
                    G[i][j] = G[i][k] + G[k][j];
                }
            }
        }
    }
}
void init_CHI() {
    for (int i = 1; i <= m; i++) {
        CHI[i] = false;
    }
}

Frac calc_Q() {
    calc_H();
    Frac res = Frac(0, 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                res = get_max(res, Frac(H[i, j], G[i, j]));
            }
        }
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int TC = 1; TC <= T; TC++) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= m; i++) {
            scanf("%d %d %lld", &U[i], &V[i], &C[i]);
        }
        init_G();
        calc_G();

        init_CHI();
        for (int i = 1; i < n; i++) {
            scanf("%d", &HI[i]);
            CHI[HI[i]] = true;
        }

        for (int hi = 1; hi < n; hi++) {
            Frac res = Frac(inf, 1);
            for (int e = 1; e <= m; e++) {
                if (CHI[e]) {
                    continue;
                }
                init_H();
                H[U[hi]][V[hi]] = H[V[hi]][U[hi]] = inf;
                H[U[e]][V[e]] = H[V[e]][U[e]] = C[e];
                if (!is_H_st()) {
                    continue;
                }
                res = get_min(res, calc_Q());
            }

            printf("%.9lf ", (double) res.p / res.q);
        }
    }
    return 0;
}