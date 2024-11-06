#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long LL;
const int MAXN = 1015;
const int MAXK = 2015;
const LL inf = (1LL << 60);
struct Point {
    int x, y;
    Point() {
        x = y = 0;
    }
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }
    bool operator < (const Point &d) const {
        return (x == d.x) ? (y < d.y) : (x < d.x);
    }
};

struct DirectEdge {
    Point e;
    LL c;
    DirectEdge() {
        e = Point(0, 0);
        c = 0;
    }
    DirectEdge(Point _e, LL _c) {
        e = _e;
        c = _c;
    }
};

struct Rectangle {
    int lx, ly, hx, hy;
    Rectangle() {
        lx = ly = hx = hy = 0;
    }
    Rectangle(int _lx, int _ly, int _hx, int _hy) {
        lx = _lx;
        ly = _ly;
        hx = _hx;
        hy = _hy;
    }
};

struct Bar {
    int x, l, r;
    bool statue;
    Bar() {
        x = l = r = 0;
        statue = false;
    }
    Bar(int _x, int _l, int _r, bool _statue) {
        x = _x;
        l = _l;
        r = _r;
        statue = _statue;
    }
    // statue = false -> read
    // statue = true -> write
};

Rectangle rect[MAXN];
LL dst[MAXK][MAXK];
vector<DirectEdge> adj[MAXK][MAXK];
vector<int> X, Y;
int n, k;
Point st;
Point ed;

int pre[MAXK];
vector<Bar> lst;

void coordinate_compression() {
    sort(all(X)); X.erase(unique(all(X)), X.end());
    sort(all(Y)); Y.erase(unique(all(Y)), Y.end());

    st.x = lower_bound(all(X), st.x) - X.begin();
    st.y = lower_bound(all(Y), st.y) - Y.begin();

    ed.x = lower_bound(all(X), ed.x) - X.begin();
    ed.y = lower_bound(all(Y), ed.y) - Y.begin();

    for (int i = 1; i <= n; i++) {
        rect[i].lx = lower_bound(all(X), rect[i].lx) - X.begin();
        rect[i].ly = lower_bound(all(Y), rect[i].ly) - Y.begin();

        rect[i].hx = lower_bound(all(X), rect[i].hx) - X.begin();
        rect[i].hy = lower_bound(all(Y), rect[i].hy) - Y.begin();
    }
}

void construct_adj_x_direction() {
    lst.clear();
    lst.pb(Bar(st.x, st.y, st.y, false));
    lst.pb(Bar(st.x, st.y, st.y, true));

    lst.pb(Bar(ed.x, ed.y, ed.y, false));
    lst.pb(Bar(ed.x, ed.y, ed.y, true));


    for (int i = 0; i <= k; i++) {
        pre[i] = -1;
    }

    for (int i = 1; i <= n; i++) {
        lst.pb(Bar(rect[i].lx, rect[i].ly, rect[i].hy, false));
        lst.pb(Bar(rect[i].hx, rect[i].ly, rect[i].hy, true));
    }

    sort(all(lst), [&](const Bar p, const Bar q) {
        if (p.x == q.x) {
            return p.statue < q.statue;
        }
        return p.x < q.x;
    });

    for (Bar b: lst) {
        for (int y = b.l; y <= b.r; y++) {
            // const up adj
            if (y != b.l) {
                adj[b.x][y].pb(DirectEdge(Point(b.x, y - 1), Y[y] - Y[y - 1]));
            }
            // const down adj
            if (y != b.r) {
                adj[b.x][y].pb(DirectEdge(Point(b.x, y + 1), Y[y + 1] - Y[y]));
            }
            // if b.statue true than write
            if (b.statue) {
                pre[y] = b.x;
            }
            // if b.statue false than read
            else {
                if (pre[y] != -1) {
                    adj[b.x][y].pb(DirectEdge(Point(pre[y], y), X[b.x] - X[pre[y]]));
                    adj[pre[y]][y].pb(DirectEdge(Point(b.x, y), X[b.x] - X[pre[y]]));
                }
            }
        }
    }
}

void construct_adj_y_direction() {
    lst.clear();
    lst.pb(Bar(st.y, st.x, st.x, false));
    lst.pb(Bar(st.y, st.x, st.x, true));

    lst.pb(Bar(ed.y, ed.x, ed.x, false));
    lst.pb(Bar(ed.y, ed.x, ed.x, true));

    for (int i = 0; i <= k; i++) {
        pre[i] = -1;
    }

    for (int i = 1; i <= n; i++) {
        lst.pb(Bar(rect[i].ly, rect[i].lx, rect[i].hx, false));
        lst.pb(Bar(rect[i].hy, rect[i].lx, rect[i].hx, true));
    }

    sort(all(lst), [&](const Bar p, const Bar q) {
        if (p.x == q.x) {
            return p.statue < q.statue;
        }
        return p.x < q.x;
    });

    for (Bar b: lst) {
        for (int x = b.l; x <= b.r; x++) {
            // const left adj
            if (x != b.l) {
                adj[x][b.x].pb(DirectEdge(Point(x - 1, b.x), X[x] - X[x - 1]));
            }
            // const down adj
            if (x != b.r) {
                adj[x][b.x].pb(DirectEdge(Point(x + 1, b.x), X[x + 1] - X[x]));
            }
            // if b.statue true than write
            if (b.statue) {
                pre[x] = b.x;
            }
            // if b.statue false than read
            else {
                if (pre[x] != -1) {
                    adj[x][b.x].pb(DirectEdge(Point(x, pre[x]), Y[b.x] - Y[pre[x]]));
                    adj[x][pre[x]].pb(DirectEdge(Point(x, b.x), Y[b.x] - Y[pre[x]]));
                }
            }
        }
    }
}
void init_adj_dst() {
    for (int x = 0; x <= k; x++) {
        for (int y = 0; y <= k; y++) {
            adj[x][y].clear();
            dst[x][y] = inf;
        }
    }
}
priority_queue<pair<int, Point>> pq;
void dijkstra() {
    pq.push(pair<int, Point>(0, st));
    dst[st.x][st.y] = 0;
    while (pq.size()) {
        pair<int, Point> p = pq.top();
        Point u = p.se;
        pq.pop();
        if (dst[u.x][u.y] != -p.fi) {
            continue;
        }

        if (u.x == ed.x && u.y == ed.y) {
            // pop all element of pq
            while (pq.size()) {
                pq.pop();
            }
            break;
        }

        for (DirectEdge e: adj[u.x][u.y]) {
            if (dst[e.e.x][e.e.y] > dst[u.x][u.y] + e.c) {
                dst[e.e.x][e.e.y] = dst[u.x][u.y] + e.c;
                pq.push(pair<int, Point>(-dst[e.e.x][e.e.y], e.e));
            }
        }
    }
    if (dst[ed.x][ed.y] == inf) {
        printf("No Path\n");
    }
    else {
        printf("%lld\n", dst[ed.x][ed.y]);
    }
}
int main() {
    int tc;
    scanf("%d", &tc);
    while (tc--) {
        X.clear();
        Y.clear();
        scanf("%d %d %d %d", &st.x, &st.y, &ed.x, &ed.y);

        X.pb(st.x);
        X.pb(ed.x);

        Y.pb(st.y);
        Y.pb(ed.y);


        scanf("%d", &n);
        bool is_inner = false;
        for (int i = 1; i <= n; i++) {
            scanf("%d %d %d %d", &rect[i].lx, &rect[i].ly, &rect[i].hx, &rect[i].hy);
            if (rect[i].lx > rect[i].hx) {
                swap(rect[i].lx, rect[i].hx);
            }
            if (rect[i].ly > rect[i].hy) {
                swap(rect[i].ly, rect[i].hy);
            }

            if (rect[i].lx <= st.x && st.x <= rect[i].hx && rect[i].ly <= st.y && st.y <= rect[i].hy) {
                is_inner = true;
            }
            if (rect[i].lx <= ed.x && ed.x <= rect[i].hx && rect[i].ly <= ed.y && ed.y <= rect[i].hy) {
                is_inner = true;
            }

            X.pb(rect[i].lx);
            X.pb(rect[i].hx);

            Y.pb(rect[i].ly);
            Y.pb(rect[i].hy);
        }

        if (is_inner) {
            printf("No Path");
            continue;
        }
        coordinate_compression();

        k = max(X.size(), Y.size());
        init_adj_dst();

        construct_adj_x_direction();
        construct_adj_y_direction();

        dijkstra();
    }
    return 0;
}