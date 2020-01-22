#include<bits/stdc++.h>
#define MAX_N 100005
#define MAX_M 200005
#define pb push_back
#define eb emplace_back
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
LL n,m,k,ans;
LL dfn[MAX_N],low[MAX_N],sum[MAX_N];
vector<LL> adj[MAX_N],bcc[MAX_N],cmp[MAX_N];
void make_dfn(LL x,LL p){
	dfn[x]=low[x]=++m;
	for(LL y:adj[x]){
		if(dfn[y]){
			if(y!=p)	low[x]=min(low[x],dfn[y]);
			continue;
		}
		make_dfn(y,x);
		low[x]=min(low[x],low[y]);
	}
}
void add(LL x,LL c){
	bcc[c].eb(x);
	cmp[x].eb(c);
}
void coloring(LL x,LL c){
	if(c)	add(x,c);
	for(LL y:adj[x]){
		if(cmp[y].size())	continue;
		if(dfn[x]<=low[y]){
			k++;add(x,k);
			coloring(y,k);
		}else	coloring(y,c);
	}
}
void get(LL c,LL p){
	printf("%lld %lld\n",c,p);
	sum[c]=bcc[c].size();
	for(LL x:bcc[c]){
		for(LL y:cmp[x]){
			if(y==p || y==c)	continue;
			get(y,c);
			sum[c]+=sum[y]-1;
		}
	}
	for(LL x:bcc[c]){
		LL s=1;
		for(LL y:cmp[x]){
			if(y==c)	continue;
			if(y==p){
				s+=m-sum[c];
				continue;
			}
			s+=sum[y]-1;
		}
		s=m-s;
		printf("%lld %lld : %lld : %lld : %lld\n",c,p,x,s,s*(s-1));
		ans-=s*(s-1);
	}
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,x,y;
	scanf("%lld %lld",&n,&m);
	while(m--){
		scanf("%lld %lld",&x,&y);
		adj[x].eb(y);adj[y].eb(x);
	}
	for(i=1;i<=n;i++){
		if(dfn[i])	continue;
		m=0;x=k+1;
		make_dfn(i,0);ans+=m*(m-1)*(m-2);
		coloring(i,0);
		for(int j=x;j<=k;j++){printf("%lld : ",j);for(int p:bcc[j])	printf("%lld ",p);printf("\n");}
		//return 0;
		get(x,0);
	}
	for(i=1;i<=k;i++)	ans+=(bcc[i].size())*(bcc[i].size()-1)*(bcc[i].size()-2);
	printf("%lld\n",ans);
	return 0;
}
