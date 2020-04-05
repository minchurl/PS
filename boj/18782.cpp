#include<bits/stdc++.h>
#define MAX_N 100005
#define MAX_M 2000005
#define MAX_K 1000000005
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
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
#define mod(x) (((x)%998244353LL + 998244353LL)%998244353LL)
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
int n,k,cnt[MAX_N];
bool ans[MAX_N];
vector<int> adj[MAX_N];
int dfs(int u,int pa){
    vector<int> lst;
    for(int v:adj[u]){
        if(v == pa) continue;
        int x = dfs(v,u);
        if(x == -1){
            return -1;
        }
        if(x+1 != k){
            lst.eb(x+1);
        }
    }
    for(int u:lst)  cnt[u]++;
    for(int u:lst){
        if(u == k-u){
            cnt[u]%=2;
        }else{
            int x = min(cnt[u],cnt[k-u]);
            cnt[u] -= x;
            cnt[k-u] -= x;
        }
    }
    int res = 0;
    for(int u:lst){
        if(cnt[u]>1){
            return -1;
        }else if(cnt[u] == 1){
            if(res) return -1;
            cnt[u] = 0;
            res = u;
        }
    }
    return res;
}
int main(){
    freopen("input.txt","r",stdin);
    int i,x,y;
    scanf("%d",&n);
    for(i=1;i<n;i++){
        scanf("%d %d",&x,&y);
        adj[x].eb(y);
        adj[y].eb(x);
    }
    int E = sqrt(n-1);
    for(i=1;i<=E;i++){
        if((n-1)%i) continue;
        k=i;if(!dfs(1,0))   ans[i] = true;
        for(int j=1;j<=n;j++)   cnt[j]=0;
        k=(n-1)/i;if(!dfs(1,0))   ans[(n-1)/i] = true;
        for(int j=1;j<=n;j++)   cnt[j]=0;
    }
    for(i=1;i<n;i++)    printf("%d",ans[i]);
    printf("\n");
    return 0;
}