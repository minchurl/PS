#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = 500005;
const int MAXK = 500005;
const int MAXM = MAXN + MAXK;
int n, m, k;
struct SegTree {
    int tree[4 * MAXM];
    int flag[4 * MAXM];
    void spread(int u) {
        tree[2 * u] += flag[u];
        flag[2 * u] += flag[u];
        tree[2 * u + 1] += flag[u];
        flag[2 * u + 1] += flag[u];
        flag[u] = 0;
    }

    void update(int u, int l, int r, int s, int e, int v) {
        if (l != r) {
            spread(u);
        }

        if (s <= l && r <= e) {
            tree[u] += v;
            flag[u] += v;
            return;
        }
        int mid = (l + r) >> 1;
        if (e <= mid) {
            update(2 * u, l, mid, s, e, v);
        }
        else if (s > mid) {
            update(2 * u + 1, mid + 1, r, s, e, v);
        }
        else {
            update(2 * u, l, mid, s, e, v);
            update(2 * u + 1, mid + 1, r, s, e, v);
        }
        tree[u] = max(tree[2 * u], tree[2 * u + 1]) + flag[u];
    }
    void update(int s, int e, int v) {
        update(1, 0, m, s, e, v);
    }

    int get(int u, int l, int r, int s, int e) {
        if (l != r) {
            spread(u);
        }

        if (s <= l && r <= e) {
            return tree[u];
        }

        int mid = (l + r) >> 1;
        int lx = s <= mid ? get(2 * u, l, mid, s, e) : 0;
        int rx = e > mid ? get(2 * u + 1, mid + 1, r, s, e) : 0;

        return max(lx, rx) + flag[u];
    }

    int get(int s, int e) {
        if (s > e) {
            return 0;
        }
        return get(1, 0, m, s, e);
    }
}segTree;
int pre[MAXK];
int dp[MAXM];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &k);
    m = n + (k + 1) / 2;
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        if (x != 0) {
            segTree.update(pre[x], i - 1, 1);
            pre[x] = i;
        }
        dp[i] = segTree.get(0, i - ((k + 1) / 2));
        segTree.update(i, i, dp[i]);
    }

    for (int i = n + 1; i <= m; i++) {
        dp[i] = segTree.get(0, i - ((k + 1) / 2));
        segTree.update(i, i, dp[i]);
    }

    printf("%d\n", dp[m]);
    return 0;
}