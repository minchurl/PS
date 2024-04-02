#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 200005;
struct node {
    int range;
    int sum;
    int level;
}tree[8 * MAXN];
struct Query {
    int l, r;
    int y, sign;
    Query() {

    }

    Query(int _l, int _r, int _y, int _sign) {
        l = _l;
        r = _r;
        y = _y;
        sign = _sign;
    }
};
int n;
vector<int> X;
vector<Query> query;

long long res;

void init_seg_tree(int i, int l, int r) {
    if (l == r) {
        tree[i].range = X[l] - X[l - 1];
        return;
    }
    int mid = (l + r) >> 1;
    init_seg_tree(2 * i, l, mid);
    init_seg_tree(2 * i + 1, mid + 1, r);

    tree[i].range = tree[2 * i].range + tree[2 * i + 1].range;
}
void init_seg_tree() {
    init_seg_tree(1, 1, X.size() - 1);
}

void update(int i, int l, int r, int s, int e, int v) {
    if (s <= l && r <= e) {
        tree[i].level += v;
        if (tree[i].level > 0) {
            tree[i].sum = tree[i].range;
        }
        else if (l != r) {
            tree[i].sum = tree[2 * i].sum + tree[2 * i + 1].sum;
        }
        else {
            tree[i].sum = 0;
        }
        return;
    }

    int mid = (l + r) >> 1;
    if (s <= mid) {
        update(2 * i, l, mid, s, e, v);
    }
    if (e > mid) {
        update(2 * i + 1, mid + 1, r, s, e, v);
    }

    if (tree[i].level > 0) {
        tree[i].sum = tree[i].range;
    }
    else {
        tree[i].sum = tree[2 * i].sum + tree[2 * i + 1].sum;
    }
}

void update(int l, int r, int v) {
    l = lower_bound(all(X), l) - X.begin() + 1;
    r = lower_bound(all(X), r) - X.begin();
    update(1, 1, X.size() - 1, l, r, v);
}

int get() {
    return tree[1].sum;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
        query.pb(Query(x1, x2, y1, 1));
        query.pb(Query(x1, x2, y2, -1));

        X.pb(x1); X.pb(x2);
    }
    

    sort(all(X));X.erase(unique(all(X)), X.end());

    init_seg_tree();

    sort(all(query), [&](const Query x, const Query y) {
        return x.y < y.y;
    });

    int current_y = -1;

    for (Query q: query) {
        if (current_y != q.y) {
            res += (long long) get() * (q.y - current_y);
        }
        current_y = q.y;
        update(q.l, q.r, q.sign);
    }

    printf("%lld\n", res);
    return 0;
}