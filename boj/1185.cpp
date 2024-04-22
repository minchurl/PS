#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 10005;
struct edge {
    int val;
    int s, e;
};
int n, m;
int nodeVal[MAXN];
int par[MAXN];
vector<edge> edgeList;
int find_par (int x) {
    return (x == par[x]) ? (x) : (par[x] = find_par(par[x]));
}
void init() {
    for (int i = 1; i <= n; i++) {
        par[i] = i;
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    int res = 1001;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nodeVal[i]);
        res = min(res, nodeVal[i]);
    }
    for (int i = 1; i <= m; i++) {
        int s, e, v;
        scanf("%d %d %d", &s, &e, &v);
        edgeList.pb({2 * v + nodeVal[s] + nodeVal[e], s, e});
    }
    sort(all(edgeList), [&](const edge x, const edge y) {
        return x.val < y.val;
    });
    init();
    for (edge edge: edgeList) {
        int s = find_par(edge.s);
        int e = find_par(edge.e);
        if (s == e) {
            continue;;
        }
        par[s] = e;
        res += edge.val;
    }

    printf("%d\n", res);
    return 0;
}