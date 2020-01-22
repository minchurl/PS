#include<bits/stdc++.h>
#define MAX_N 100005
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
LL n,m,a[MAX_N],b[MAX_N],d[MAX_N],idx[MAX_N];
bool vis[MAX_N];
vector<pil> E[MAX_N];
pil lst[MAX_N],temp[MAX_N];
inline LL get_val(LL p,LL x){return lst[p].fi*x+lst[p].se;}
bool is_pass(LL p,LL x){
	if(p==-1)	return true;
	if(m<=p+1)	return false;
	return get_val(p,x)>=get_val(p+1,x);
}
bool is_delect(pil x,pil y,pil z){return (x.se-y.se)*(x.fi-z.fi)<=(x.se-z.se)*(x.fi-y.fi);}
LL bin(LL x){
	LL l=0,r=m-1;
	while(l<r){
		LL mid=(l+r)>>1;
		if(is_pass(mid,x)){
			l=mid+1;
		}else{
			r=mid;
		}
	}
	return l;
}
void update(LL x,LL s){
	LL l=1,r=m-1;
	if(m<=1 || !is_delect(lst[m-2],lst[m-1],{-s,d[x]})){
		idx[x]=m;
		temp[x]=lst[m];
		lst[m]={-s,d[x]};
		m++;
		return;
	}
	while(l<r){
		LL mid=(l+r)>>1;
		if(is_delect(lst[mid-1],lst[mid],{-s,d[x]}))	r=mid;
		else	l=mid+1;
	}
	idx[x]=r;
	temp[x]=lst[r];
	lst[r]={-s,d[x]};
	m=r+1;
}
void dfs(LL x,LL s){
	LL temp_m=m;
	vis[x]=true;
	if(m)	d[x]=get_val(bin(a[x]),a[x])+a[x]*s+b[x];
	update(x,s);
	for(pil p:E[x]){
		if(vis[p.fi])	continue;
		dfs(p.fi,s+p.se);
	}
	lst[idx[x]]=temp[x];
	m=temp_m;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,x,y,v;
	scanf("%lld",&n);
	for(i=1;i<n;i++){
		scanf("%lld %lld %lld",&x,&y,&v);
		E[x].pb({y,v});E[y].pb({x,v});
	}
	for(i=2;i<=n;i++)	scanf("%lld %lld",&b[i],&a[i]);
	dfs(1,0);
	for(i=2;i<=n;i++)	printf("%lld ",d[i]);
	printf("\n");
	return 0;
}
