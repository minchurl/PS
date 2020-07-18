#include<bits/stdc++.h>
#define MAX_N 50005
#define MAX_M 100005
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
#define rev(x) ((x)^1)
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))
#define fi first
#define se second
#define LL_inf (1LL<<60)
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
#define inf 0x3fffffff
#define MOD 1000000007LL
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
typedef long double LD;
int n,m,dn,cn;
int dfn[MAX_N],low[MAX_N],val[MAX_N];
int ans;
vector<int> adj[MAX_N],bcc[MAX_N],cmp[MAX_N];
stack<int> st;
struct max_pq{
    priority_queue<int> in, out;
    void init(){
        while(in.size())    in.pop();
        while(out.size())    out.pop();
    }
    void udt(){
        while(in.size() && out.size() && in.top() == out.top()){
            in.pop();
            out.pop();
        }
    }
    int get_max(){
        udt();
        if(in.size())   return in.top();
        return -1;
    }
    void add(int x){
        in.push(x);
    }
    void del(int x){
        out.push(x);
    }
}pq;
int make_low(int u,int pa){
    dfn[u] = low[u] = ++dn;
    for(int v:adj[u]){
        if(dfn[v] && v != pa)   low[u] = min(low[u], dfn[v]);
        else if(!dfn[v])   low[u] = min(low[u], make_low(v,u));
    }
    return low[u];
}
void coloring(int u,int c){
    if(c){
        bcc[c].eb(u);
        cmp[u].eb(c);
    }
    for(int v:adj[u]){
        if(cmp[v].size())   continue;
        if(low[v] >= dfn[u]){
            cn++;
            bcc[cn].eb(u);
            cmp[u].eb(cn);
            coloring(v,cn);
        }else{
            coloring(v,c);
        }
    }
}
void calc(int u,int c){
    int mn = 0;
    int i,sz;
    dfn[u] = 0;
    for(int bn:cmp[u]){
        if(bn == c) continue;
        sz = bcc[bn].size();
        int z = 0;
        for(i=0;i<sz;i++){
            int v = bcc[bn][i];
            if(u != v) calc(v,bn);
            else    z = i;
        }

        // maximum value in this cycle
        pq.init();
        for(i=0;i<sz/2;i++){
            pq.add(val[bcc[bn][i]]+i);
        }
        for(i=0;i<sz;i++){
            pq.add(val[bcc[bn][(i + sz / 2)%sz]] + i + sz / 2);
            pq.del(val[bcc[bn][i]] + i);
            ans = max(ans, pq.get_max() - i + val[bcc[bn][i]]);
        }
        
        // get val[u]
        for(i=0;i<sz;i++){
            int v = bcc[bn][i];
            if(u == v)  continue;
            val[u] = max(val[u], val[v] + min(abs(z-i), sz - abs(z-i)));
        }
    }
}
int main(){
    freopen("input.txt","r",stdin);
    int i,j,x,y;
    scanf("%d %d",&n,&m);
    for(i=0;i<m;i++){
        scanf("%d",&j);
        scanf("%d",&x);
        j--;
        while(j--){
            scanf("%d",&y);
            adj[x].eb(y);
            adj[y].eb(x);
            x = y;
        }
    }
    for(i=1;i<=n;i++){
        if(!dfn[i]) make_low(i,0);
    }
    for(i=1;i<=n;i++){
        if(!cmp[i].size()){
            coloring(i,0);
        }
    }

    // // check bcc
    // for(i=1;i<=cn;i++){
    //     for(int v:bcc[i]){
    //         printf("%d ",v);
    //     }
    //     printf("\n");
    // }

    for(i=1;i<=n;i++){
        if(!dfn[i])  continue;
        calc(i,0);
    }
    printf("%d\n",ans);
    return 0;
}