#include<bits/stdc++.h>
#define MAX_N 300005
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
LL n,m,ln,k;
LL loc[MAX_N],base[MAX_N];
priority_queue<pil> pq[MAX_N];
vector<pil> adj[MAX_N],lst;
void merge(LL x,LL y){
	LL p=loc[x],q=loc[y];
	if(pq[q].size()>pq[p].size())	swap(p,q);
	loc[x]=p;base[p]+=base[q];
	while(pq[q].size()){
		pq[p].push(pq[q].top());
		pq[q].pop();
	}
}
void dfs(LL x,LL v){
	loc[x]=ln++;
	for(pil p:adj[x]){
		if(p.fi>n){pq[loc[x]].push({p.se,1});pq[loc[x]].push({p.se,-1});}
		else{
			dfs(p.fi,p.se);
			merge(x,p.fi);
		}
	}
	//line-up
	//base[x]+=v;
	lst.clear();lst.resize(0);
	while(pq[loc[x]].size()){
		lst.pb(pq[loc[x]].top());
		pq[loc[x]].pop();
	}
	LL sz=lst.size();
	pq[loc[x]].push({lst[sz/2].fi+v,-1});
	pq[loc[x]].push({lst[sz/2-1].fi+v,1});
	for(LL i=0;i<sz;i++){
		base[loc[x]]+=max((lst[sz/2].fi-lst[i].fi)*(lst[i].se),0LL);
	}
}
int main(){
	LL i,x,v;
	scanf("%lld %lld",&n,&m);
	for(i=2;i<=n+m;i++){
		scanf("%lld %lld",&x,&v);
		adj[x].pb({i,v});
	}
	dfs(1,0);
	printf("%lld\n",base[loc[1]]);
	return 0;
}
