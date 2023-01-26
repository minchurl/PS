#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
struct Node {
    int s, e;
};
Node node[MAXN];
Node temp[MAXN];
int n, m;
int locS[MAXN], locE[MAXN];
int res[MAXN][2];
bool isS[MAXN], isE[MAXN];
int calcStartIdx(int idx) {
    int sum = 1;
    for (int i = 1; i < idx; i++) {
        sum += node[i].e - node[i].s + 1;
    }
    return sum;
}
int calcEndIdx(int idx) {
    return calcStartIdx(idx) + node[idx].e - node[idx].s;
}
void init() {
    for (int i = 1; i <= n; i++) {
        isS[i] = isE[i] = false;
    }
}

void merge1(int resi) {
    int d = locE[node[1].s - 1];
    res[resi][0] = calcEndIdx(d - 1);
    res[resi][1] = calcEndIdx(d);
    int j = 1;
    for (int i = d + 1; i <= n; i++) {
        temp[j++] = node[i];
    }
    temp[j] = node[1];
    temp[j++].s = node[d].s;
    for (int i = 2; i <= d - 1; i++) {
        temp[j++] = node[i];
    }
    n--;

    for (int i = 1; i <= n; i++) {
        node[i] = temp[i];
    }
}
void merge2(int resi) {
    int c = locE[node[n].e + 1];
    res[resi][0] = calcEndIdx(c - 1);
    res[resi][1] = calcEndIdx(c);
    int j = 1;
    for (int i = c + 1; i < n; i++) {
        temp[j++] = node[i];
    }
    temp[j] = node[c];
    temp[j++].e = node[n].e;
    for (int i = 1; i <= c - 1; i++) {
        temp[j++] = node[i];
    }
    n--;

    for (int i = 1; i <= n; i++) {
        node[i] = temp[i];
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &m);
    int x, y;
    n++;
    scanf("%d", &x);
    x = y;
    node[n].s = node[n].e = x;
    for (int i = 2; i <= m; i++) {
        scanf("%d", &y);
        if (y != x + 1) {
            n++;
            node[n].s = y;
        }
        node[n].e = y;
        x = y;
    }
    m = n - 1;
    for (int resi = 0; resi < m; resi++) {
        int i;
        for (i = 1; i <= n; i++) {
            locS[node[i].s] = i;
            locE[node[i].e] = i;
            isS[node[i].s] = true;
            isE[node[i].e] = true;
        }
        if (isE[node[1].s - 1]) {
            merge1(resi);
        }
        else if (isS[node[n].e + 1]) {
            merge2(resi);
        }
    }

    for (int i = m - 1; i >= 0; i--) {
        if (res[i][1] == n) {
            printf("2 %d\n", res[i][0]);
        }
        else {
            printf("3 %d %d\n", res[i][0], res[i][1]);
        }
    }
    return 0;
}
