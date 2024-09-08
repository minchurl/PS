#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long llint; 
const int MAXN = 100005;

struct Seg_Tree {
    int n;
    int V[MAXN];
    vector<int> lst[4 * MAXN];
    void read_n(int _n) {
        n = _n;
    }
    void read_V(int idx, int v) {
        V[idx] = v;
    }

    void merge(int u, int l, int r) {
        int li = 0;
        int ri = 0;
        int lsize = lst[l].size();
        int rsize = lst[r].size();
        while (li < lsize && ri < rsize) {
            if (lst[l][li] < lst[r][ri]) {
                lst[u].pb(lst[l][li]);
                li++;
            }
            else {
                lst[u].pb(lst[r][ri]);
                ri++;
            }
        }

        while (li < lsize) {
            lst[u].pb(lst[l][li]);
            li++;
        }

        while (ri < rsize) {
            lst[u].pb(lst[r][ri]);
            ri++;
        }
    }
    void construct_lst(int u, int l, int r) {
        if (l == r) {
            lst[u].pb(V[l]);
            return;
        }

        int mid = (l + r) >> 1;

        construct_lst(2 * u, l, mid);
        construct_lst(2 * u + 1, mid + 1, r);

        merge(u, 2 * u, 2 * u + 1);
    }

    void construct_lst() {
        construct_lst(1, 1, n);
    }

    int get(int u, int l, int r, int s, int e, int lt) {
        // get number of V[i] <= lt where s <= i <= e

        if (s <= l && r <= e) {
            return upper_bound(all(lst[u]), lt) - lst[u].begin();
        }

        int mid = (l + r) >> 1;
        if (e <= mid) {
            return get(2 * u, l, mid, s, e, lt);
        }
        else if (s > mid) {
            return get(2 * u + 1, mid + 1, r, s, e, lt);
        }
        else {
            return get(2 * u, l, mid, s, mid, lt) + get(2 * u + 1, mid + 1, r, mid + 1, e, lt);
        }
    }

    int get_1_to_lt(int s, int e, int lt) {
        return get(1, 1, n, s, e, lt);
    }

    int get_v(int s, int e, int v) {
        return get(1, 1, n, s, e, v) - get(1, 1, n, s, e, v - 1);
    }
}seg_tree[2];

int main() {
    int n;
    scanf("%d", &n);

    // init seg_tree
    seg_tree[0].read_n(n);
    seg_tree[1].read_n(n);

    // A
    for (int i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);
        seg_tree[0].read_V(i, v);
    }

    // B
    for (int i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);
        seg_tree[1].read_V(i, v);
    }

    seg_tree[0].construct_lst();
    seg_tree[1].construct_lst();

    int q;
    scanf("%d", &q);
    while (q--) {
        int s, e, k;
        scanf("%d %d %d", &s, &e, &k);
        int sqrt_k = sqrt(k);
        llint res = 0;
        for (int i = 1; i <= sqrt_k; i++) {
            res += (llint)seg_tree[0].get_v(s, e, i) * seg_tree[1].get_1_to_lt(s, e, k / i);
            res += (llint)seg_tree[1].get_v(s, e, i) * seg_tree[0].get_1_to_lt(s, e, k / i);
        }
        res -= (llint)seg_tree[0].get_1_to_lt(s, e, sqrt_k) * seg_tree[1].get_1_to_lt(s, e, sqrt_k);

        printf("%lld\n", res);
    }
    return 0;
}