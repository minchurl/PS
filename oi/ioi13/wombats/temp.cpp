#include "wombats.h"
#include<bits/stdc++.h>
using namespace std;

const int inf = 0x3fffffff;

// duplication of the original data
int r, c;
int h[5000][200], v[5000][200];

// related with 3-way segment tree
int n;
int DP[8281][200][200];
int LC[8281], MC[8281], RC[8281];



// array used in merge function
int D[200][200];
int temp[200][200];
void merge(int A[200][200], int B[200][200], int cost[200], int M[200][200]) {
    // s == e
    for (int i = 0; i < c; i++) {
        temp[i][i] = inf;
        for (int j = 0; j < c; j++) {
            temp[i][i] = min(temp[i][i], A[i][j] + cost[j] + B[j][i]);
            printf("     a %d %d : %d %d %d\n", i, j, A[i][j], cost[j], B[j][i]);
        }
        D[i][i] = i;
    }

    // s < e

    for (int len = 2; len <= c; len++) {
        for (int s = 0; s <= c - len; s++) {
            int e = s + len - 1;
            temp[s][e] = inf;
            D[s][e] = s;
            for (int i = D[s][e - 1]; i <= D[s + 1][e]; i++) {
                if (temp[s][e] > A[s][i] + cost[i] + B[i][e]) {
                    temp[s][e] = A[s][i] + cost[i] + B[i][e];
                    D[s][e] = i;
                }
            }

            temp[s][e] = min({temp[s][e], temp[s][s] + B[s][e], A[s][e] + temp[e][e]});
        }
    }

    // s > e

    for (int len = 2; len <= c; len++) {
        for (int s = len - 1; s < c; s++) {
            int e = s - len + 1;
            temp[s][e] = inf;
            D[s][e] = s;
            for (int i = D[s - 1][e]; i <= D[s][e + 1]; i++) {
                if (temp[s][e] > A[s][i] + cost[i] + B[i][e]) {
                    temp[s][e] = A[s][i] + cost[i] + B[i][e];
                    printf("   %d %d : %d :: %d %d %d : %d\n", s, e, i, A[s][i], cost[i], B[i][e], temp[s][e]);
                    D[s][e] = i;
                }
            }

            temp[s][e] = min({temp[s][e], temp[s][s] + B[s][e], A[s][e] + temp[e][e]});
            printf("   %d %d : %d %d\n", s, e, temp[s][s] + B[s][e], A[s][e] + temp[e][e]);
        }
    }

    for (int s = 0; s < c; s++) {
        for (int e = 0; e < c; e++) {
            M[s][e] = temp[s][e];
        }
    }
}

void set_mono_dp(int u, int i) {
    for (int s = 0; s < c; s++) {
        DP[u][s][s] = 0;
        for (int e = s + 1; e < c; e++) {
            DP[u][s][e] = DP[u][s][e - 1] + h[i][e - 1];
            DP[u][e][s] = DP[u][s][e];
        }
    }
}

void init_seg(int u, int l, int r) {
    if (l == r) {
        set_mono_dp(u, l);
    }

    else if (l + 1 == r) {
        LC[u] = ++n;
        RC[u] = ++n;
        init_seg(LC[u], l, l);
        init_seg(RC[u], r, r);
        merge(DP[LC[u]], DP[RC[u]], v[l], DP[u]);
    }
    else {
        int lmid = (2 * l + r) / 3;
        int rmid = (l + 2 * r) / 3;
        LC[u] = ++n;
        MC[u] = ++n;
        RC[u] = ++n;
        init_seg(LC[u], l, lmid);
        init_seg(MC[u], lmid + 1, rmid);
        init_seg(RC[u], rmid + 1, r);
        merge(DP[LC[u]], DP[MC[u]], v[lmid], DP[u]);
        printf("%d %d :: \n", l, rmid);
        for (int s = 0; s < c; s++) {
            for (int e = 0; e < c; e++) {
                printf("%d %d : %d\n", s, e, DP[u][s][e]);
            }
        }
        merge(DP[u], DP[RC[u]], v[rmid], DP[u]);
    }

    printf("%d %d :: \n", l, r);
    for (int s = 0; s < c; s++) {
        for (int e = 0; e < c; e++) {
            printf("%d %d : %d\n", s, e, DP[u][s][e]);
        }
    }

}

void init(int R, int C, int H[5000][200], int V[5000][200]) {
    /* ... */
    r = R;
    c = C;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            h[i][j] = H[i][j];
            v[i][j] = V[i][j];
        }
    }

    init_seg(1, 0, r - 1);
}

void changeH(int P, int Q, int W) {
    /* ... */
}

void changeV(int P, int Q, int W) {
    /* ... */
}

int escape(int V1, int V2) {
    return DP[1][V1][V2];
}