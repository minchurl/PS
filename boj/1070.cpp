#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long LL;
const int MAXN = 55;
const int MAXM = 55;
const int MAXV = 2 * MAXN * MAXM;
const int inf = 0x3fffffff;
const LL infLL = (1LL << 40);
struct Edge {
    int dest, cap, rev;
    LL cost;
    Edge() {
        dest = cap = rev = 0;
        cost = 0;
    }

    Edge(int _dest, int _cap, int _rev, LL _cost) {
        dest = _dest;
        cap = _cap;
        rev = _rev;
        cost = _cost;
    }
};
vector<Edge> adj[MAXV];
int n, m;
int source, destination;
int blockVal[30];
char kingdom[MAXN][MAXM];
void generateEdge(int st, int ed, int cap, LL cost) {
    adj[st].pb(Edge(ed, cap, adj[ed].size(), cost));
    adj[ed].pb(Edge(st, 0, adj[st].size() - 1, -cost));
}
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
bool isInBoundary(int x, int y) {
    if (x < 0 || y < 0 || x >= n || y >= m) {
        return false;
    }
    return true;
}
void generateGraph() {
    // generate inner edge (i, j) -> (i, j)'
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (kingdom[i][j] < 'A' || kingdom[i][j] > 'Z') {
                continue;
            }
            generateEdge(i * m + j, i * m + j + n * m, 1, blockVal[kingdom[i][j] - 'A']);
        }
    }
   

    // generate outer edge (i, j)' -> (x, y)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 4; k++) {
                int x = i + dx[k];
                int y = j + dy[k];

                if (!isInBoundary(x, y)) {
                    continue;
                }
                generateEdge(i * m + j + n * m, x * m + y, inf, 0);
            }
        }
    }

    // source -> (i, j)
    for (int k = 0; k < 4; k++) {
        int i = (source - m * n) / m + dx[k];
        int j = (source - m * n) % m + dy[k];

        if (!isInBoundary(i, j)) {
            continue;
        }
        generateEdge(source, i * m + j, inf, 0);
    }

    // (i, j)' -> destination
    for (int i = 1; i < n - 1; i++) {
        int j = 0;
        generateEdge(i * m + j + n * m, destination, inf, 0);
        j = m - 1;
        generateEdge(i * m + j + n * m, destination, inf, 0);
    }
    for (int j = 0; j < m; j++) {
        int i = 0;
        generateEdge(i * m + j + n * m, destination, inf, 0);
        i = n - 1;
        generateEdge(i * m + j + n * m, destination, inf, 0);
    }

}
Edge from[MAXV];
int cap[MAXV];
LL dst[MAXV];
bool isInQueue[MAXV];
queue<int> Q;
void init() {
    while (Q.size()) {
        Q.pop();
    }
    for (int i = 0; i < MAXV; i++) {
        cap[i] = 0;
        dst[i] = inf;
        isInQueue[i] = false;
    }
}
void SPFA() {
    init();

    cap[source] = inf;
    dst[source] = 0;
    Q.push(source);
    while (Q.size()) {
        int p = Q.front();
        Q.pop();
        isInQueue[p] = false;
        
        if (cap[p] <= 0) {
            continue;
        }

        for (Edge e: adj[p]) {
            if (e.cap <= 0 || dst[e.dest] <= dst[p] + e.cost) {
                continue;
            }
            cap[e.dest] = min(cap[p], e.cap);
            dst[e.dest] = dst[p] + e.cost;
            from[e.dest] = adj[e.dest][e.rev];

            if (!isInQueue[e.dest]) {
                Q.push(e.dest);
                isInQueue[e.dest] = true;
            }
        }
    }
}
void changeGraph(int c) {
    int ed = destination;
    while (ed != source) {
        int st = from[ed].dest;
        int idx = from[ed].rev;
        int revIdx = adj[st][idx].rev;
        
        printf("%d %d -> %d %d : %d\n", st / m, st % m, ed / m, ed % m, c);

        adj[st][idx].cap -= c;
        adj[ed][revIdx].cap += c;

        ed = st;
    }
}
LL MCMF() {
    LL res = 0;
    while (1) {
        SPFA();
        int c = cap[destination];
        printf("%d %lld\n", c, dst[destination]);
        if (c == 0) {
            break;
        }
        res += dst[destination];
        changeGraph(c);
    }
    return res;
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", kingdom[i]);
        for (int j = 0; j < m; j++) {
            if (kingdom[i][j] == '*') {
                source = i * m + j + m * n;
                destination = i * m + j;
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        scanf("%d", &blockVal[i]);
    }

    generateGraph();
    printf("%lld\n", MCMF());

    return 0;
}