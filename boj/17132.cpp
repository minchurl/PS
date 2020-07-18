#include<bits/stdc++.h>
#define MAX_N 100005
#define MAX_M 20005
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
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
struct node{
    LL u,v,val;
    bool operator < (const node d){
        return val > d.val;
    }
};
LL n,par[MAX_N],num[MAX_N];
LL ans;
vector<node> lst;
LL find_par(LL x){
    return (x == par[x]) ? (x) : (par[x] = find_par(par[x]));
}
int main(){
    freopen("input.txt","r",stdin);
    LL u,v,val,i;
    scanf("%lld",&n);

    for(i=1;i<=n;i++){
        par[i] = i;
        num[i] = 1;
    }

    for(i=0;i<n-1;i++){
        scanf("%lld %lld %lld",&u,&v,&val);
        lst.pb({u,v,val});
    }
    sort(all(lst));
    for(node p:lst){
        u = find_par(p.u);
        v = find_par(p.v);
        if(u == v)  continue;

        ans += num[u] * num[v] * p.val;

        par[v] = u;
        num[u] += num[v];
    }

    printf("%lld\n",ans);
    return 0;
}