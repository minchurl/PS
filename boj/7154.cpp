#include<bits/stdc++.h>
#define MAX_N 145
#define MAX_M 75
#define pb push_back
#define fi first
#define se second
#define inf 0x3fffffff
using namespace std;
typedef pair<int, int> pii;
struct edge{
    int val, cap;
};
struct node{
    int x, val, cap;
};
int n,m;
bool chk[MAX_M + MAX_N];
int from[MAX_M + MAX_N];
int dst[MAX_M + MAX_N];
int cap[MAX_M + MAX_N][MAX_M + MAX_N], val[MAX_M + MAX_N][MAX_M + MAX_N];
vector<int> adj[MAX_M + MAX_N];
queue<int> Q;
void add_edge(int s, int e, int v, int c){
    adj[s].pb(e);
    adj[e].pb(s);
    cap[s][e] = c;
    cap[e][s] = 0;
    val[s][e] = -v;
    val[e][s] = v;
}
int SPFA(){
    int i;
    for(i=0;i<=n+m+1;i++){
        dst[i] = inf;
        from[i] = 0;
        chk[i] = false;
    }
    dst[0] = 0;
    Q.push(0);
    chk[0] = true;
    while(Q.size()){
        int p = Q.front();
        Q.pop();
        chk[p] = false;
        for(int q:adj[p]){
            if(!cap[p][q] || val[p][q] + dst[p] >= dst[q])  continue;
            dst[q] = dst[p] + val[p][q];
            from[q] = p;
            if(!chk[p]) Q.push(q);
        }
    }
    
    return dst[m + n + 1];
}
void udt(){
    for(int v = n + m + 1 ; v != 0 ; v = from[v]){
        int u = from[v];
        cap[u][v]--;
        cap[v][u]++;
    }
}
int main(){
    freopen("input.txt","r",stdin);
    int i, j;
    int y, p;
    while(1){
        scanf("%d %d",&n,&m);
        if(n == 0 && m == 0){
            break;
        }
        for(i=1;i<=n;i++){
            scanf("%d",&p);
            add_edge(m + i, m + n + 1, 0, p);
        }
        for(i=1;i<=m;i++){
            add_edge(0, i, 0, 1);
            scanf("%d",&y);
            y--;
            for(j=0;j<4;j++){
                scanf("%d",&p);
                p++;
                add_edge(i, m + p, 4 * y + 4 - j, 1);
            }
        }
        int ans = 0;
        while(1){
            p = SPFA();
            if(p == inf){
                break;
            }
            ans -= p;
            udt();
        }
        printf("%d\n",ans);
        for(i=0;i<=n+m+1;i++){
            for(j=0;j<=n+m+1;j++){
                cap[i][j] = 0;
                val[i][j] = 0;
            }
            adj[i].clear();
            adj[i].resize(0);
        }
    }
    return 0;
}