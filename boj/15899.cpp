#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 200005;
const int mod_value = 1000000007;
int n, m;
int rn;
int initial_color[MAXN];
pii range[MAXN];
int temp[(1 << 18) + 1];
vector<int> merge_tree[(1 << 19) + 1];
vector<int> adj[MAXN];
void set_initial_value(int v, int c) {
    merge_tree[v + (1 << 18) - 1].pb(c);
}
void construct_merge_tree(int i, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    construct_merge_tree(2 * i, l, mid);
    construct_merge_tree(2 * i + 1, mid + 1, r);


    // merge
    int li = 0, ri = 0;
    int lsize = merge_tree[2 * i].size();
    int rsize = merge_tree[2 * i + 1].size();

    while (li < lsize || ri < rsize) {
        if (li == lsize) {
            merge_tree[i].pb(merge_tree[2 * i + 1][ri++]);
        }
        else if (ri == rsize || merge_tree[2 * i][li] <= merge_tree[2 * i + 1][ri]) {
            merge_tree[i].pb(merge_tree[2 * i][li++]);
        }
        else {
            merge_tree[i].pb(merge_tree[2 * i + 1][ri++]);
        }
    }
}
void construct_merge_tree() {
    for (int i = 1; i <= n; i++) {
        set_initial_value(range[i].fi, initial_color[i]);
    }
    construct_merge_tree(1, 1, (1 << 18));
}
int get(int i, int l, int r, int s, int e, int c) {
    if (s > r || e < l) {
        return 0;
    }
    if (s <= l && r <= e) {
        return upper_bound(all(merge_tree[i]), c) - merge_tree[i].begin();
    }

    int mid = (l + r) >> 1;
    return get(2 * i, l, mid, s, e, c) + get(2 * i + 1, mid + 1, r, s, e, c);

}
int get(int v, int c) {
    return get(1, 1, (1 << 18), range[v].fi, range[v].se, c);
}
void construct_range(int u, int par) {
    range[u].fi = ++rn;

    for (int v: adj[u]) {
        if (v == par) {
            continue;
        }
        construct_range(v, u);
    }
    range[u].se = rn;
}
int main() {
    freopen("input.txt", "r", stdin);
    int x;
    scanf("%d %d %d", &n, &m, &x);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &initial_color[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].pb(v);
        adj[v].pb(u);
    }
    construct_range(1, 0);
    construct_merge_tree();

    int res = 0;
    for (int i = 0; i < m; i++) {
        int v, c;
        scanf("%d %d", &v, &c);
        res = (res + get(v, c)) % mod_value;
    }
    
    printf("%d\n", res);
    return 0;
}