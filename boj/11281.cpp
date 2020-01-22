#include<bits/stdc++.h>
#define MAX_N 20005
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


#define rev(x) (((x)<=n)?((x)+n):((x)-n))


using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
typedef long double LD;
int n,m,sn;
int dn;
int low[MAX_N],dfn[MAX_N],cmp[MAX_N],deg[MAX_N];
int ans[MAX_N];
vector<int> adj[MAX_N],scc[MAX_N];
queue<int> Q;
stack<int> st;
int make_scc(int u){
	int low;
	low = dfn[u] = ++dn;
	st.push(u);
	for(int v:adj[u]){
		if(dfn[v] && !cmp[v])	low = min(low, dfn[v]);
		else if(!dfn[v])	low = min(low, make_scc(v));
	}
	if(dfn[u] == low){
		++sn;
		while(st.size() && dfn[u] <= dfn[st.top()]){
			cmp[st.top()] = sn;
			st.pop();
		}
		
	}
	return low;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y;
	scanf("%d %d",&n,&m);
	for(i=0;i<m;i++){
		scanf("%d %d",&x,&y);
		if(x < 0)	x = n-x;
		if(y < 0)	y = n-y;
		adj[rev(x)].eb(y);
		adj[rev(y)].eb(x);
	}
	for(i=1;i<=2*n;i++){
		if(!dfn[i]){
			make_scc(i);
		}
	}
	for(i=1;i<=n;i++){
		if(cmp[i] == cmp[i+n])	return !printf("0\n");
		ans[i] = (cmp[i] < cmp[i+n]) ? 1 : 0;
	}
	printf("1\n");
	for(i=1;i<=n;i++)	printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
