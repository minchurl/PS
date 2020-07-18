#include<bits/stdc++.h>
#define MAX_N 20005
#define MAX_M 20005
#define MAX_E 205
#define MAX_K 205
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
//#define inf 0x3fffffff
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
#define inf (1LL<<60)
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
LL n,m,k,q;
LL hub[MAX_K];
LL dst[MAX_K][MAX_N];
vector<pil> adj[MAX_N];
vector<LL> ans;
priority_queue<pil> pq;
void dijkstra(LL idx, LL h, LL z){
    LL i;
    for(i=1;i<=n;i++){
        dst[idx][z][i] = inf;
    }
    dst[idx][z][h] = 0LL;
    pq.push({0,h});
    while(pq.size()){
        pil p = pq.top();
        pq.pop();
        if(-p.fi != dst[idx][z][p.se]){
            continue;
        }
        for(pil v:adj[z][p.se]){
            if(-p.fi + v.se >= dst[idx][z][v.fi]){
                continue;
            }
            dst[idx][z][v.fi] = -p.fi + v.se;
            pq.push({-dst[idx][z][v.fi],v.fi});
        }
    }
}
int main(){
    LL i,u,v,val;
    freopen("input.txt","r",stdin);
    scanf("%lld %lld %lld %lld",&n,&m,&k,&q);
    for(i=0;i<m;i++){
        scanf("%lld %lld %lld",&u,&v,&val);
        adj[u].eb(v,val);
    }
    for(i=0;i<k;i++){
        scanf("%lld",&hub[i]);
        dijkstra(i,hub[i]);
    }
    while(q--){
        val = inf;
        scanf("%lld %lld",&u,&v);

        if(val != inf){
            ans.eb(val);
        }
    }
    printf("%d\n",(int)ans.size());
    LL sum = 0;
    for(LL x:ans){
        sum += x;
    }
    printf("%lld\n",sum);
    return 0;
}