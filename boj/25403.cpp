#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 100005;
const int MAXM = 100005;
const int MAXK = 800005;
const int inf = 0x3fffffff;
struct SegTree {
    int n;
    int flag[2 * MAXK];
    int maxVal[2 * MAXK];
    int minVal[2 * MAXK];

    void init(int _n) {
        n = _n;
    }

    void adjustFlag(int u, int v) {
        flag[u] += v;
        maxVal[u] += v;
        minVal[u] += v;
    }
    void spread(int u) {
        adjustFlag(2 * u, flag[u]);
        adjustFlag(2 * u + 1, flag[u]);
        flag[u] = 0;
    }

    void update(int u, int l, int r, int s, int e, int v) {
        if (l < r) {
            spread(u);
        }
        if (s <= l && r <= e) {
            adjustFlag(u, v);
            return;
        }
        int mid = (l + r) >> 1;
        if (s <= mid) {
            update(2 * u, l, mid, s, e, v);
        }
        if (e > mid) {
            update(2 * u + 1, mid + 1, r, s, e, v);
        }
        maxVal[u] = max(maxVal[2 * u], maxVal[2 * u + 1]);
        minVal[u] = min(minVal[2 * u], minVal[2 * u + 1]);
    }

    void update(int s, int e, int v) {
        update(1, 0, n - 1, s, e, v);
    }

    int getMax() {
        return maxVal[1];
    }

    int getMin() {
        return minVal[1];
    }
}segTree;

struct Query {
    int x, y;
    bool isBlue;
    bool isEnter;

    Query() {

    }

    Query(int _x, int _y, bool _isBlue, bool _isEnter) {
        x = _x, y = _y, isBlue = _isBlue, isEnter = _isEnter;
    }
};
vector<Query> query;
int N, M;
int W, H;
vector<int> X;
void update(int i) {
    Query q = query[i];
    int l = 2 * (lower_bound(all(X), q.x - W) - X.begin() + 1);
    int r = 2 * (lower_bound(all(X), q.x) - X.begin() + 1);
    int v = (q.isEnter ? 1 : -1) * (q.isBlue ? 1 : -1);
    segTree.update(l, r, v);
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d %d %d", &N, &M, &W, &H);

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        X.pb(x - W);
        X.pb(x);
        query.pb(Query(x, y - H, true, true));
        query.pb(Query(x, y, true, false));
    }

    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        X.pb(x - W);
        X.pb(x);
        query.pb(Query(x, y - H, false, true));
        query.pb(Query(x, y, false, false));
    }

    sort(all(query), [&](const Query p, const Query q) {
        if (p.y == q.y) {
            return p.isEnter > q.isEnter;
        }
        return p.y < q.y;
    });
    sort(all(X)); X.erase(unique(all(X)), X.end());

    segTree.init(2 * query.size() + 2);
    int sz = query.size();
    int res = 0;
    for (int i = 0; i < sz; i++) {
        update(i);
        while (i + 1 < sz && query[i].y == query[i + 1].y && query[i].isEnter == query[i + 1].isEnter) {
            i++;
            update(i);
        }
        res = max(res, max(segTree.getMax(), -segTree.getMin()));
    }

    printf("%d\n", res);
    return 0;
}