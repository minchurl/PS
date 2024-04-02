#include "wombats.h"
#include<bits/stdc++.h>
using namespace std;

const int inf = 0x3fffffff;

// duplication of the original data
int r, c;
int dr;
int h[5000][200], v[5000][200];

// seg_tree
struct node {
    int dp[200][200];
    node *l, *r;
    node(){}

}*root;

// array used in merge function
int D[200][200];
int temp[200][200];
void merge(int A[200][200], int B[200][200], int cost[200], int M[200][200]) {
    // s == e
    for (int i = 0; i < c; i++) {
        temp[i][i] = inf;
        D[i][i] = i;
        for (int j = 0; j < c; j++) {
            if (temp[i][i] > A[i][j] + cost[j] + B[j][i]) {
                temp[i][i] = A[i][j] + cost[j] + B[j][i];
                D[i][i] = j;
            }
        }
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
                    D[s][e] = i;
                }
            }
        }
    }

    for (int s = 0; s < c; s++) {
        for (int e = 0; e < c; e++) {
            M[s][e] = temp[s][e];
        }
    }
}

void set_mono(int i, int A[200][200]) {
    for (int s = 0; s < c; s++) {
        A[s][s] = 0;
        for (int e = s + 1; e < c; e++) {
            A[s][e] = A[s][e - 1] + h[i][e - 1];
            A[e][s] = A[s][e];
        }
    }
}

int tmp[200][200];
void calc(node *u, int l, int r) {
    set_mono(l, u -> dp);
    for (int i = l + 1; i <= r; i++) {
        set_mono(i, tmp);
        merge(u -> dp, tmp, v[i - 1], u -> dp);
    }
}

void init_seg(node *u, int l, int r) {
    if (r - l <= 20) {
        calc(u, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    if (u -> l == NULL) u -> l = new node();
    if (u -> r == NULL) u -> r = new node();

    init_seg(u -> l, l, mid);
    init_seg(u -> r, mid + 1, r);
    merge(u -> l -> dp, u -> r -> dp, v[mid], u -> dp);
}

void init(int R, int C, int H[5000][200], int V[5000][200]) {
    r = R;
    c = C;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            h[i][j] = H[i][j];
            v[i][j] = V[i][j];
        }
    }
    root = new node();
    init_seg(root, 0, r - 1);
}

void update(node *u, int l, int r, int p) {
    if (r - l <= 20) {
        calc(u, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) {
        update(u -> l, l, mid, p);
    }
    else {
        update(u -> r, mid + 1, r, p);
    }
    merge(u -> l -> dp, u -> r -> dp, v[mid], u -> dp);
}

void changeH(int P, int Q, int W) {
    h[P][Q] = W;
    update(root, 0, r - 1, P);
}


void changeV(int P, int Q, int W) {
    v[P][Q] = W;
    update(root, 0, r - 1, P);
}

int escape(int V1, int V2) {
    return root -> dp[V1][V2];
}
