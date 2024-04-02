#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int MAXN = 500005;
const int MAXP = 500005;
struct Edge {
    int dest;
    char color;
    Edge(){}
    Edge(int _dest, char _color) {
        dest = _dest;
        color = _color;
    }
};
int n;
int f[MAXP];
int len_p;
char P[MAXP];
vector<Edge> adj[MAXN];
void construct_failure_function() {
    int i = 0, j = -1;
    f[i] = j;
    while (i < len_p) {
        while (j != -1 && P[i] != P[j]) {
            j = f[j];
        }
        i++;
        j++;
        f[i] = j;
    }
}
int dfs(int i, int j) {
    int jj;
    int res = 0;
    for (Edge e: adj[i]) {
        jj = j;
        while (jj != -1 && e.color != P[jj]) {
            jj = f[jj];
        }
        jj++;
        if (jj == len_p) {
            res++;
            jj = f[jj];
        }
        res += dfs(e.dest, jj);
    }
    return res;
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int s, e;
        char str[4];
        scanf("%d %d %s", &s, &e, str);
        adj[s].pb(Edge(e, str[0]));
    }
    scanf("%s", P);
    len_p = strlen(P);
    construct_failure_function();
    printf("%d\n", dfs(1, 0));
    return 0;
}