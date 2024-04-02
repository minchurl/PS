#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int MAXN = 1000005;
vector<int> adj[MAXN];
int n, m, k;
int res = 1;
int gn;         // number of group
int gsum;       // sum(number of nodes - 2) in each groups
int fac[MAXN];
int chk[MAXN];
void terminate_process() {
    printf("0\n");
    exit(0);
}
void mul_res(int x) {
    res = (res * x) % k;
}

// check whether the main graph contains loop
// if contains, then terminate all the process
void check_loop(int u, int par) {
    chk[u] = 1;
    for (int v: adj[u]) {
        if (adj[v].size() < 2) {
            continue;
        }
        if (v == par) {
            continue;
        }
        if (chk[v] == 1) {
            // loop!
            terminate_process();
        }
        check_loop(v, u);
    }
}

int count_group_node(int u) {
    int sum = 1;
    chk[u] = 2;
    for (int v: adj[u]) {
        if (chk[v] == 2) {
            continue;
        }
        sum += count_group_node(v);
    }
    return sum;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &k);

    // construct power array
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = (fac[i - 1] * i) % k;
    }


    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x].pb(y);
        adj[y].pb(x);
    }

    // let's define main graph as the graph contains nodes which degree is larger than 1.
    // then the main graph should be a set of lines to satisfy the conditions of problem.

    int mn = 0;

    for (int u = 1; u <= n; u++) {
        if (adj[u].size() <= 1) {
            if (adj[u].size() == 0) {
                mn++;
            }
            continue;
        }
        int cnt = 0;
        for (int v: adj[u]) {
            if (adj[v].size() == 1) {
                cnt++;
            }
        }
        // if the degree of nodes in main graph is larger than 2, then the graph contains graph which is not a line.
        if (adj[u].size() - cnt > 2) {
            terminate_process();
        }
        // nodes whose degree is one and are connected in the main graph can switch positions each other.
        mul_res(max(cnt, 1));
    }

    // check whethere the main graph contains loop.
    // if it contains a loop, terminate the process.

    for (int i = 1; i <= n; i++) {
        if (adj[i].size() <= 1 || chk[i] == 1) {
            continue;
        }
        check_loop(i, 0);
    }

    for (int i = 1; i <= n; i++) {
        if (adj[i].size() == 0 || chk[i] == 2)  {
            continue;
        }
        gn++;
        gsum += count_group_node(i) - 2;
    }
    
    int sn = (gn + 1) * 2 + gsum;


    for (int i = 1; i <= gn; i++) {
        mul_res(2);
    }


    for (int i = sn; i < sn + mn; i++) {
        mul_res(i);
    }
    printf("%d\n", res);
    return 0;
}