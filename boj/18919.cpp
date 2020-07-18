#include<bits/stdc++.h>
#define MAX_N 1005
#define MAX_M 100005
#define MAX_K 25
#define MAX_Q 200005
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).rezsize(0);
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))
#define fi first
#define se second
#define inf 0x3fffffff
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
//#define inf 0x3fffffff
#define MOD 1000000007LL
#define cpx_mod(x) (((LD)(((LL)x.real())%MOD)),((LD)(((LL)x.imag())%MOD)))
#define prev(x) (((x)+n-1)%n)
#define next(x) (((x)+1)%n)
#define mod(x) ((int)((((LL)x)%1000000007LL + 1000000007LL)%1000000007LL))
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls; 
typedef complex<LD> Complex;
int n,m;
int arr[MAX_N],par[MAX_N],loc[MAX_N];
vector<int> adj[MAX_N];
vector<pii> lst;
vector<pii> ans;
int find_par(int x){
    return (x == par[x])?(x):(par[x] = find_par(par[x]));
}
void dfs(int u,int dep){
    lst.eb(-dep,u);
    for(int v:adj[u]){
        if(par[v])  continue;
        par[v] = u;
        dfs(v,dep+1);
    }
}
void _swap(int x,int y){
    swap(arr[x],arr[y]);
    loc[arr[x]] = x;
    loc[arr[y]] = y;
    ans.eb(x,y);
}
bool go(int u,int e){
    par[u] = e;
    if(u == e){
        return true;
    }
    for(int v:adj[u]){
        if(par[v] == e) continue;
        bool x = go(v,e);
        if(x){
            _swap(u,v);
            return true;
        }
    }
    return false;
}
int main(){
    freopen("input.txt","r",stdin);
    int i,p,q,x,y;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d",&arr[i]);
        par[i] = i;
        loc[arr[i]] = i;
    }
    scanf("%d",&m);
    for(i=1;i<=m;i++){
        scanf("%d %d",&x,&y);
        p = find_par(x);
        q = find_par(y);
        if(p==q)    continue;
        par[p] = q;
        adj[x].eb(y);
        adj[y].eb(x);
    }
    for(i=1;i<=n;i++){
        if(find_par(i) != find_par(arr[i])) return !printf("-1\n");
    }
    for(i=1;i<=n;i++)   par[i] = 0;
    for(i=1;i<=n;i++){
        if(par[i])  continue;
        par[i] = i;
        dfs(i,0);
    }
    for(i=1;i<=n;i++)   par[i] = 0;
    sort(all(lst));
    for(pii u:lst){
        p = loc[u.se];
        q = u.se;
        if(p==q)    continue;
        go(q,p);
    }
    printf("%d\n",(int)ans.size());
    for(pii u:ans){
        printf("%d %d\n",u.fi,u.se);
    }
    return 0;
}