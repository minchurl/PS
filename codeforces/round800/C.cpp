#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef pair<int, int> pii;
const int inf = 0x3fffffff;
const int MAXN = 200005;
int n, m;
int dst[MAXN], cnt[MAXN];
vector<int> adj[MAXN], inverseAdj[MAXN];
priority_queue<pii> pq;
void init() {
    for (int i = 1; i <= n; i++) {
        dst[i] = inf;
    }
}
void dijkstra() {
    dst[n] = 0;
    cnt[n] = 0;
    pq.push(pii(0, n));
    while (pq.size()) {
        pii p = pq.top();
        pq.pop();
        if (dst[p.se] != -p.fi) {
            continue;
        }

        for (int nxt: inverseAdj[p.se]) {
            int val = adj[nxt].size() - cnt[nxt] + dst[p.se];
            cnt[nxt]++;
            if (dst[nxt] > val) {
                dst[nxt] = val;
                pq.push(pii(-dst[nxt], nxt));
            }
        }
    }
}
int main() {
    freopen("input.txt","r",stdin);

    scanf("%d %d", &n, &m);

    for (int i = 1; i <= m; i++) {
        int s, e;
        scanf("%d %d", &s, &e);
        adj[s].pb(e);
        inverseAdj[e].pb(s);
    }

    init();
    dijkstra();

    printf("%d\n", dst[1]);
    return 0;
}