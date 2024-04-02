#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<LL, LL> pll;
const int MAXM = 60 * 30;
int n, m;
vector<int> adj[MAXM];
map<string, int> match;

int dn, dfn[MAXM], cmp[MAXM];
int in_degree[MAXM];

int sn;
stack<int> S;

queue<int> Q;
LL score[MAXM];

int get_input() {
    char s[100];
    scanf("%s", s);
    string name(s);
    if (match.find(name) == match.end()) {
        match[name] = ++m;
    }
    return match[name];
}

int construct_scc(int u) {
    int low = dfn[u] = ++dn;
    S.push(u);
    for (int v: adj[u]) {
        if (dfn[v] && !cmp[v]) {
            low = min(low, dfn[v]);
        }
        else if (!dfn[v]) {
            low = min(low, construct_scc(v));
        }
    }
    if (low >= dfn[u]) {
        sn++;
        while (S.size()) {
            LL t = S.top();
            S.pop();
            cmp[t] = sn;
            if (t == u) {
                break;
            }
        }
    }
    return low;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int ed = get_input();
        int sz;
        scanf("%d", &sz);
        while (sz--) {
            int st = get_input();
            adj[st].pb(ed);
        }
    }
    for (int i = 1; i <= m; i++) {
        if (dfn[i]) {
            continue;
        }
        construct_scc(i);
    }

    for (int u = 1; u <= m; u++) {
        for (int v: adj[u]) {
            if (cmp[u] == cmp[v]) {
                continue;
            }
            in_degree[v]++;
        }
    }

    for (int i = 1; i <= m; i++) {
        score[i] = 1;
        if (in_degree[i] == 0) {
            Q.push(i);
        }
    }


    while (Q.size()) {
        int u = Q.front();
        Q.pop();

        for (int v: adj[u]) {
            if (cmp[u] == cmp[v]) {
                continue;
            }
            score[v] += score[u];
            in_degree[v]--;
            if (in_degree[v] == 0) {
                Q.push(v);
            }
        }
    }
    
    int st = get_input();
    printf("%lld\n", score[st]);
    return 0;
}