#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 1e9;
const int MAXP = 100005;
struct node {
    int x, y;
    int i;
    int z;
};
int n, p;
int m;
int V[MAXP];
int t[2 * MAXP];
vector<node> lst;
vector<int> Y;
int get(int i) {
    int res = 0;
    for (; i > 0; i -= (i & -i)) {
        res = max(res, t[i]);
    }
    return res;
}
void update(int i, int v) {
    for (; i <= m; i += (i & -i)) {
        t[i] = max(t[i], v);
    }
}
int main() {
    scanf("%d %d", &n, &p);
    for (int i = 0; i < p; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        V[i] = (x2 - x1) + (y2 - y1);
        Y.pb(y1);
        Y.pb(y2);
        lst.pb({x1, y1, i, 1});
        lst.pb({x2, y2, i, -1});
    }

    sort(all(Y)); Y.erase(unique(all(Y)), Y.end());
    m = Y.size();

    sort(all(lst), [&](const node x, const node y) {
        if (x.x == y.x && x.y == y.y) {
            return x.z < y.z;
        }
        if (x.x == y.x) {
            return x.y < y.y;
        }
        return x.x < y.x;
    });

    for (node p: lst) {
        p.y = lower_bound(all(Y), p.y) - Y.begin() + 1;
        if (p.z == 1) {
            V[p.i] += get(p.y);
        }
        else {
            update(p.y, V[p.i]);
        }
    }
    printf("%d\n", 2 * n - get(m));
    return 0;
}