//practice of struct
#include<bits/stdc++.h>
#define MAX_N 50005
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
struct BCC{
	int n,m,cn,ans;
	int dfn[MAX_N],low[MAX_N];
	int dp1[2][MAX_N];
	vector<int> adj[MAX_N],bcc[MAX_N],cmp[MAX_N];
	BCC(){//init
		ans=cn=m=0;
	}
	void init(){
		for(int i=1;i<=n;i++)	dp1[0][i]=dp1[1][i]=0;
	}
	void input(int x){
		n=x;
		init();
	}
	void add_edge(int x,int y){
		adj[x].pb(y);
		adj[y].pb(x);
	}
	void dfs(int x,int p){
		dfn[x]=low[x]=++m;
		for(int y:adj[x]){
			if(y==p)	continue;
			if(dfn[y])	low[x]=min(low[x],dfn[y]);
			else{
				dfs(y,x);
				low[x]=min(low[x],low[y]);
			}
		}
	}
	void coloring(int x,int c){
		if(c){
			bcc[c].pb(x);
			cmp[x].pb(c);
		}
		for(int y:adj[x]){
			if(cmp[y].size())	continue;
			if(low[y]>=dfn[x]){
				m++;
				bcc[m].pb(x);
				cmp[x].pb(m);
				coloring(y,m);
			}else	coloring(y,c);
		}
	}
	void calc(int c,int x){
		dfn[c]=0;
		for(int y:bcc[c]){
			if(x==y)	continue;
			for(int z:cmp[y]){
				if(dfn[z])	calc(z,y);
			}
		}
		int sz=bcc[c].size();
		vector<int> dp[4];
		
		for(int i=0;i<4;i++)	dp[i]=vector<int>(sz,{0});
		
		dp[0][0]=dp[1][0]=dp1[0][bcc[c][0]],
		dp[2][0]=dp[3][0]=dp1[1][bcc[c][0]];
		
		dp[0][1]=dp1[0][bcc[c][0]]+dp1[0][bcc[c][1]],dp[1][1]=max(dp[0][1],dp1[0][bcc[c][0]]+dp1[1][bcc[c][1]]),
		dp[2][1]=dp1[1][bcc[c][0]]+dp1[0][bcc[c][1]],dp[3][1]=max({dp[2][1],dp1[1][bcc[c][0]]+dp1[1][bcc[c][1]],dp[0][1]+1});
		for(int i=2;i<sz;i++){
			int cost=dp1[0][bcc[c][i-1]]+dp1[0][bcc[c][i]];
			dp[0][i]=max(dp[0][i-1],dp[1][i-1])+dp1[0][bcc[c][i]];
			dp[1][i]=max({dp[0][i],dp[1][i-1]+dp1[1][bcc[c][i]],dp[1][i-2]+cost+1});
			dp[2][i]=max(dp[2][i-1],dp[3][i-1])+dp1[0][bcc[c][i]];
			dp[3][i]=max({dp[2][i],dp[3][i-1]+dp1[1][bcc[c][i]],dp[3][i-2]+cost+1});
		}
		dp1[0][x]=max(dp1[0][x],dp[1][sz-1]);
		dp1[1][x]=max({dp1[1][x],dp[3][sz-1],dp[0][sz-1]+1});
		dp1[1][x]=max(dp1[0][x],dp1[1][x]);
		ans=max(ans,dp1[1][x]);
	}
	void solve(){
		for(int i=1;i<=n;i++)	if(!dfn[i])	dfs(i,0);
		m=0;
		for(int i=1;i<=n;i++)	if(!cmp[i].size())	coloring(i,0);
		for(int i=1;i<=m;i++){
			if(dfn[i])	calc(i,bcc[i][0]);
		}
		printf("%d\n",ans);
	}
}bcc;
int main(){
	int n,m,x,y,z;
	scanf("%d %d",&n,&m);
	bcc.input(n);
	while(m--){
		scanf("%d",&z);
		scanf("%d",&x);z--;
		while(z--){
			scanf("%d",&y);
			bcc.add_edge(x,y);
			x=y;
		}
	}
	bcc.solve();
	return 0;
}
