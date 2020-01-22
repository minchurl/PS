#include<bits/stdc++.h>
#define MAX_N 200005
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
struct HLD{
	vector<pii> dp[2],color;
	vector<int> chain;
	int num;
	HLD(int x){num=x;}
	pii add_node(int x){
		chain.pb(x);
		return {num,chain.size()-1};
	}
	pil get_node(int x){return chain[x];}
	void init(){
		color.resize(4*chain.size(),{0,0});
		dp[0].resize(4*chain.size(),{0,0});
		dp[1].resize(4*chain.size(),);
	}
	void color_spread(int x){
		color[2*x].se+=color[x].se;
		color[2*x+1].se+=color[x].se;
	}
	void color_udt(int x,int l,int r,int p,int v){
		if(l!=r)	color_spread(x);
		if(l==r){
			color[x].x+=v;color[x].y+=v;
			return;
		}
		int mid=(l+r)>>1;
		color_udt(2*x,l,mid,p,v);
		color_udt(2*x+1,mid+1,r,p,v);
		color[x].x=color[2*x].x+color[2*x+1].x+(r-l+1)*color[x].y;
	}
	void highest_node(int x,int l,int r,int s,int e,int c){
		if(l==r)	return c==color[x].x?l:l-1;
		int mid=(l+r)>>1;
		if()
	}
};
vector<HLD> lst;
void make_HLD(int x,int p){
	cnt[x]=1;
	if(p && adj[x].size()==1){
		lst.pb(HLD(lst.size()-1));
		where[x]=lst.add_node(x);
		return;
	}
	int mx=0;
	for(int y:adj[x]){
		if(y==p)	continue;
		make_HLD(y,x);cnt[x]+=cnt[y];
		if(cnt[mx]<cnt[y])	mx=y;
	}
	
}
int main(){
	int ;
	scanf("%d",&n);
	for(i=1;i<n;i++){
		scanf("%d %d",&x,&y);
		adj[x].pb(y);adj[y].pb(x);
	}
	dfs0(1,0);
	make_HLD(1,0);
	scanf("%d",&q);
	while(q--){
		scanf("%d %d",&x,&y);
		if(x==1){
		}else{
		}
	}
	return 0;
}
