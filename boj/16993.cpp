#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int inf = 100000005;
struct node {
    int lmx, rmx, mx;
    int sum;
    node() {
        lmx = -inf;
        rmx = -inf;
        mx = -inf;
        sum = -inf;
    }
};
node tree[(1 << 18)];
void update(int x, int l, int r, int p, int v) {
    if (l == r) {
        tree[x].lmx = tree[x].rmx = tree[x].mx = v;
        tree[x].sum = 0;
        return ;
    }

    int mid = (l + r) >> 1;
    if (p <= mid) {
        update(2 * x, l, mid, p, v);
    }
    else {
        update(2 * x + 1, mid + 1, r, p, v);
    }
    tree[x].lmx = max(tree[2 * x].lmx, tree[2 * x].sum + tree[2 * x + 1].lmx);
    tree[x].rmx = max(tree[2 * x + 1].rmx, tree[2 * x + 1].sum + tree[2 * x].rmx);
    tree[x].sum = tree[2 * x].sum + tree[2 * x + 1].sum;
    tree[x].mx = max({tree[x].lmx, tree[x].rmx, tree[2 * x].rmx + tree[2 * x + 1].lmx, tree[2 * x].mx, tree[2 * x + 1].mx});
}

void update(int p, int v) {
    update(1, 1, n, p, v);
}

node get(int x, int l, int r, int s, int e) {

    if (r < s || e < l) {
        return node();
    }

    if (s <= l && r <= e) {
        return tree[x];
    }


}

int get(int s, int e) {
    return get(1, 1, n, s, e).mx;
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    return 0;
}