#include<bits/stdc++.h>
#define MAX_N 500005
#define MAX_M 100005
#define pb push_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))
#define fi first
#define se second
#define LL_inf (1LL<<60)
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
#define inf 0x3fffffff
#define MOD 1000000007LL
#define cpx_mod(x) (((LD)(((LL)x.real())%MOD)),((LD)(((LL)x.imag())%MOD)))
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
typedef long double LD;
struct node{
	LL cnt,mx;
};
LL n,T[MAX_N];
vector<LL> E[MAX_N];
bool vis[MAX_N];
node dfs(LL x){
	vis[x]=true;
	vector<node> V;
	V.pb({0,0});
	for(LL y:E[x]){
		if(vis[y])	continue;
		V.pb(dfs(y));
	}
	LL c=0;
	sort(all(V),[&](const node x,const node y){
		if(max(x.mx,2*x.cnt+y.mx)==max(y.mx,2*y.cnt+x.mx))	return x.cnt<y.cnt;
		return max(x.mx,2*x.cnt+y.mx)<max(y.mx,2*y.cnt+x.mx);
	});
	for(node y:V){
		V[0].mx=max(V[0].mx,y.mx+2*c);
		c+=y.cnt;
	}
	x=max(T[x],V[0].mx)+1;
	c++;
	return {c,x};
}
int main(){
	LL i,x,y;
	scanf("%lld",&n);
	for(i=1;i<=n;i++)	scanf("%lld",&T[i]);
	for(i=1;i<n;i++){
		scanf("%lld %lld",&x,&y);
		E[x].pb(y);E[y].pb(x);
	}
	node p=dfs(1);
	printf("%lld\n",max(p.mx-1,2*(n-1)+T[1]));
	return 0;
}
