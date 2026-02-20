#include<bits/stdc++.h>
#define eb emplace_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = 100005;
struct Edge {
    int i, u, v, c;
    Edge() {
    }
    Edge(int _i, int _u, int _v, int _c) {
        i = _i;
        u = _u;
        v = _v;
        c = _c;
    }
};
vector<Edge> edges;
set<pii> S;
int par[MAXN];
int N, M;
int find_par(int x) {
    return (par[x] == x) ? x : (par[x] = find_par(par[x]));
}
void init_kruskal() {
    for (int i = 1; i <= N; i++) {
        par[i] = i;
    }
}
LL get_st_cost_by_kruskal() {
    sort(all(edges), [&](Edge x, Edge y) {
        return x.c < y.c;
    });

    LL cost = 0;
    for (Edge e: edges) {
        int u = find_par(e.u);
        int v = find_par(e.v);
        if (u == v) {
            continue;
        }
        par[u] = v;
        cost += e.c;
    }
    return cost;
}
int main() {
    int T;
    scanf("%d", &T);
    for (int TC = 1; TC <= T; TC++) {
        printf("Case #%d\n", TC);
        scanf("%d %d", &N, &M);
        edges.clear();
        S.clear();
        for (int i = 0; i < M; i++) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            if (u > v) {
                swap(u, v);
            }
            edges.eb(i, u, v, c);
            S.insert(pii(-c, i));
        }
        sort(all(edges), [&](const Edge x, const Edge y){
            if (x.u == y.u) {
                if (x.v == y.v) {
                    return x.c < y.c;
                }
                return x.v < y.v;
            }
            return x.u < y.u;
        });
        if (N == 2) {
            printf("0 %d\n", edges.front().c);
            fflush(stdout);
            continue;
        }
        int max_diff = -1;
        Edge lo_edge;
        int hi_edge_idx;

        for (int i = 0; i < M; i++) {
            int j = i;
            while (j < M && edges[i].u == edges[j].u && edges[i].v == edges[j].v) {
                S.erase(pii(-edges[j].c, edges[j].i));
                j++;
            }
            int max_cost = -(S.begin() -> first);
            printf("%d %d : %d : %d\n", edges[i].u, edges[i].v, edges[i].c, max_cost);
            if (max_cost - edges[i].c > max_diff || (max_cost - edges[i].c == max_diff && edges[i].c < lo_edge.c)) {
                max_diff = max_cost - edges[i].c;
                lo_edge = edges[i];
                hi_edge_idx = S.begin() -> second;
            }

            for (; i < j; i++) {
                S.insert(pii(-edges[i].c, edges[i].i));
            }
            i--;
        }
        Edge hi_edge;
        for (int i = 0; i < M; i++) {
            if (edges[i].i == hi_edge_idx) {
                hi_edge = edges[i];
            }
        }
        init_kruskal();
        par[find_par(lo_edge.u)] = find_par(lo_edge.v);
        par[find_par(hi_edge.u)] = find_par(hi_edge.v);
        LL st_cost = lo_edge.c + hi_edge.c + get_st_cost_by_kruskal();
        printf("%d %lld\n", max_diff, st_cost);
        fflush(stdout);
    }
    return 0;
}