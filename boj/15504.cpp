#include<bits/stdc++.h>
#define MAX_N 305
#define inf 0x3fffffff
using namespace std;
struct Player{
    int a, h, l;
    bool operator < (const Player d){
        return a > d.a;
    }
}player[MAX_N];
int n;
int cap[2 * MAX_N][2 * MAX_N], val[2 * MAX_N][2 * MAX_N];
int dst[2 * MAX_N], from[2 * MAX_N];
int ans;
bool chk[2 * MAX_N];
queue<int> Q;
bool SPFA(){
    int i;
    for(i = 0 ; i <= 2 * n + 1 ; i++){
        dst[i] = inf;
        chk[i] = false;
    }
    dst[0] = 0;
    chk[0] = true;
    Q.push(0);
    while(Q.size()){
        int u = Q.front();
        Q.pop();
        chk[u] = false;
        for(int v = 0 ; v <= 2 * n + 1 ; v++){
            if(!cap[u][v] || dst[v] <= dst[u] + val[u][v])  continue;
            dst[v] = dst[u] + val[u][v];
            from[v] = u;
            if(!chk[v]) Q.push(v);
            chk[v] = true;
        }
    }
    if(dst[2 * n + 1] != inf){
        ans -= dst[2 * n + 1];
        return true;
    }
    return false;
}
int main(){
    freopen("input.txt","r",stdin);
    int i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++)   scanf("%d",&player[i].a);
    for(i=1;i<=n;i++)   scanf("%d",&player[i].h);
    for(i=1;i<=n;i++)   scanf("%d",&player[i].l);
    sort(player + 1, player + n + 1);
    cap[n + 1][2 * n + 1] = player[1].l;
    for(i=2;i<=n;i++){
        cap[0][i] = 1;
        cap[n + i][2 * n + 1] = player[i].l - 1;

        for(j=1;j<i;j++){
            cap[i][j + n] = 1;
            val[i][j + n] = -((player[i].a ^ player[j].a) - player[i].h - player[j].h);
            val[j + n][i] = -val[i][j + n];
        }
    }
    while(SPFA()){
        for(int v = 2 * n + 1 ; v ; v = from[v]){
            int u = from[v];
            cap[u][v]--;
            cap[v][u]++;
        }
    }
    printf("%d\n",ans);
    return 0;
}