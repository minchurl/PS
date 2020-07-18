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
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
typedef long double LD;
int n,m,sn,dn,dfn[MAX_N],cmp[MAX_N];
vector<int> adj[MAX_N];
vector<int> scc[MAX_N];
stack<int> st;
int dfs(int u){
	dfn[u] = ++dn;
	int low = dn;
	st.push(u);
	for(int v:adj[u]){
		if(dfn[v] && !cmp[v])	low = min(low, dfn[v]);
		else if(!dfn[v])	low = min(low, dfs(v));
	}
	if(dfn[u] == low){
		sn++;
		while(st.size() && st.top() != u){
			int x = st.top();
			scc[sn].eb(x);
			cmp[x] = sn;
			st.pop();
		}
		scc[sn].eb(u);
		cmp[u] = sn;
		sort(all(scc[sn]));
		st.pop();
	}
	return low;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,u,v;
	scanf("%d %d",&n,&m);
	while(m--){
		scanf("%d %d",&u,&v);
		adj[u].eb(v);
	}
	for(i=1;i<=n;i++){
		if(dfn[i])	continue;
		dfs(i);
	}
	sort(scc+1, scc+1+sn, [&](const vector<int> x, const vector<int> y){
		return x[0] < y[0];
	});
	printf("%d\n",sn);
	for(i=1;i<=sn;i++){
		for(int p:scc[i]){
			printf("%d ",p);
		}
		printf("-1\n");
	}
	return 0;
}