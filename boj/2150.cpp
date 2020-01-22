#include<bits/stdc++.h>
#define MAX_N 10005
#define MAX_M 100005
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
int n,m,dfn[MAX_N];
int dn;
int sn,cmp[MAX_N];
vector<int> adj[MAX_N],scc[MAX_N];
stack<int> st;
int dfs(int u){
	int low;
	low = dfn[u] = ++dn;
	st.push(u);
	for(int v:adj[u]){
		if(dfn[v] && !cmp[v])	low = min(low, dfn[v]);
		else if(!dfn[v])	low = min(low, dfs(v));
	}
	if(dfn[u] == low){
		++sn;
		while(st.size() && dfn[st.top()] >= dfn[u]){
			cmp[st.top()] = sn;
			scc[sn].eb(st.top());
			st.pop();
		}
		sort(all(scc[sn]));
	}
	return low;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y;
	scanf("%d %d",&n,&m);
	for(i=0;i<m;i++){
		scanf("%d %d",&x,&y);
		adj[x].eb(y);
	}
	for(i=1;i<=n;i++){
		if(!dfn[i])	dfs(i);
	}
	sort(scc+1,scc+sn+1,[&](const vector<int> x,const vector<int> y){return x.front() < y.front();});
	printf("%d\n",sn);
	for(i=1;i<=sn;i++){
		for(int p:scc[i])	printf("%d ",p);
		printf("-1\n");
	}
	return 0;
}
