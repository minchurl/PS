#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pil;
const int MAXN = 100005;
const int MAXM = 100005;

struct Edge {
    int s, e;
    int loc;
    bool isVisited;
    Edge() {

    }
    Edge(int _s, int _e) {
        s = _s;
        e = _e;
    }
}edge[2 * MAXM];
struct Vertex {
    LL x, y;
}vertex[MAXN];


vector<int> edgeList[MAXN];

int n, m;
vector<LL> res;

LL ccw(Vertex x, Vertex y, Vertex z) {
    return (x.x * y.y + y.x * z.y + z.x * x.y)
         - (x.y * y.x + y.y * z.x + z.y * x.x);
}

LL ccw(int x, int y, int z) {
    return ccw(vertex[x], vertex[y], vertex[z]);
}


LL calc(int en) {
    Edge &e = edge[en];
    e.isVisited = true;

    int revLoc = edge[en ^ 1].loc;
    int revSZ = edgeList[e.e].size();
    int i = (revLoc + 1) % revSZ;
    int nxt = edgeList[e.e][i];

    LL area = (vertex[e.s].x * vertex[e.e].y) - (vertex[e.s].y * vertex[e.e].x);
    if (edge[nxt].isVisited) {
        return area;
    }
    return area + calc(nxt);
    
}

int main() {
    freopen("input.txt","r",stdin);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &vertex[i].x, &vertex[i].y);
    }

    for (int i = 0; i < m; i++) {
        int s, e;
        scanf("%d %d", &s, &e);
        edge[2 * i] = Edge(s, e);
        edge[2 * i + 1] = Edge(e, s);
        edgeList[s].pb(2 * i);
        edgeList[e].pb(2 * i + 1);
    }

    for (int i = 1; i <= n; i++) {
        sort(all(edgeList[i]), [&] (const int x, const int y) {
            Vertex p = vertex[edge[x].s];
            Vertex q = vertex[edge[x].e];
            Vertex r = vertex[edge[y].e];

            if (p.y == q.y || p.y == r.y) {
                if (q.y == r.y) {
                    return q.x > r.x;
                }
                if (p.y > q.y) {
                    return false;
                }
                if (p.y > r.y) {
                    return true;
                }
            }

            if ((q.y - p.y) * (r.y - p.y) < 0) {
                return q.y > r.y;
            }

            return ccw(q, p, r) < 0;
        });
    }

    int sz;
    for (int i = 0; i < m; i++) {
        sz = edgeList[i].size();
        for (int j = 0; j < sz; j++) {
            edge[edgeList[i][j]].loc = j;
        }
    }


    for (int i = 1; i <= n; i++) {
        for (int en: edgeList[i]) {
            if (edge[en].isVisited) {
                continue;
            }
            LL r = calc(en);
            if (r) {
                res.pb(abs(r));
            }
        }
    }


    sort(all(res));
    sz = res.size();
    printf("%d\n", sz - 1);
    for (int i = 0; i < sz - 1; i++) {
        printf("%.1lf\n", (double) res[i] / 2);
    }
    return 0;
}