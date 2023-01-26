#include<bits/stdc++.h>

#define pb push_back
#define all(v) (v).begin(), (v).end()

using namespace std;

typedef long long LL;

const int MAXN = 10005;
const int MAXM = 50005;
const int MAXCORSIZE = 100000;
const int LOGMAXCORSIZE = 16;

struct Point {
    int x, y;
    Point(){}
    Point(int x, int y): x(x), y(y){}
};
struct node {
    int v;
    node *l, *r;
    node(int v, node *l, node *r): v(v), l(l), r(r){}
    node *update(int idx, int p) {
        if (idx < 0) {
            return new node(v + 1, NULL, NULL);
        }

        if (p >> idx & 1) {
            return new node(v + 1,  l, r -> update(idx - 1, p));
        }
        else {
            return new node(v + 1, l -> update(idx - 1, p), r);
        }
    }
    node *update(int p) {
        return update(LOGMAXCORSIZE, p);
    }
};
node *root[MAXN];
int rn;
int n, m;
Point point[MAXN];
vector<int> X, Y;
void init() {
    rn = 1;
    X.clear();
    X.pb(-1);

    Y.clear();
    Y.pb(-1);
}


int get(int idx, node *l, node *r, int p) {
    if (idx < 0) {
        return r -> v - l -> v;
    }
    if (p >> idx & 1) {
        return r -> l -> v - l -> l -> v + get(idx - 1, l -> r, r -> r, p);
    }
    return get(idx - 1, l -> l, r -> l, p);
}

int get(node *l, node *r, int p) {
    return get(LOGMAXCORSIZE, l, r, p);
}

int main() {
    freopen("input.txt", "r", stdin);
    int TC;
    scanf("%d", &TC);

    root[0] = new node(0, NULL, NULL);
    root[0] -> l = root[0];
    root[0] -> r = root[0];
    rn = 1;

    while (TC--) {
        init();
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++) {
            scanf("%d %d", &point[i].x, &point[i].y);
            X.pb(point[i].x);
            Y.pb(point[i].y);
        }

        sort(all(X));
        sort(all(Y));Y.erase(unique(all(Y)), Y.end());

        sort(point + 1, point + n + 1, [&](const Point x, const Point y) {
            return x.x < y.x;
        });

        for (int i = 1; i <= n; i++) {
            int y = lower_bound(all(Y), point[i].y) - Y.begin();
            root[rn] = root[rn - 1] -> update(y);
            rn++;
        }

        LL res = 0;
        for (int i = 0; i < m; i++) {
            int sx, sy, ex, ey;
            scanf("%d %d %d %d", &sx, &ex, &sy, &ey);
            sx = lower_bound(all(X), sx) - X.begin();
            ex = lower_bound(all(X), ex + 1) - X.begin() - 1;
            sy = lower_bound(all(Y), sy) - Y.begin();
            ey = lower_bound(all(Y), ey + 1) - Y.begin() - 1;

            res += get(root[sx - 1], root[ex], ey) - get(root[sx - 1], root[ex], sy - 1);
        }
        printf("%lld\n", res);
    }
    return 0;
}