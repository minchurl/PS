#include<bits/stdc++.h>
#define MAX_N 10005
#define MAX_M 100005
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
#define rev(x) ((x)^1)
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
int n,m,cmp[2*MAX_N];
int sn,dn,dfn[2*MAX_N];
vector<int> adj[2 * MAX_N];
stack<int> st;
int convert(int x){
	if(x < 0)	return -(2 * x + 2);
	else	return 2 * x - 1;
}
int make_scc(int u){
	int low;
	low = dfn[u] = ++dn;
	st.push(u);
	for(int v:adj[u]){
		if(dfn[v] && !cmp[v])	low = min(low, dfn[v]);
		else if(!dfn[v])	low = min(low, make_scc(v));
	}
	if(dfn[u] == low){
		sn++;
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
	if(m==0){
		printf("1\n");
		for(i=0;i<n;i++)	printf("1 ");
		printf("\n");
		return 0;
	}
	for(i=0;i<m;i++){
		scanf("%d %d",&x,&y);
		x = convert(x);
		y = convert(y);
		adj[rev(x)].eb(y);
		adj[rev(y)].eb(x);
	}
	for(i=0;i<2*n;i++){
		if(dfn[i])	continue;
		make_scc(i);
	}
	for(i=0;i<n;i++){
		if(cmp[2 * i] == cmp[2 * i + 1]){
			return !printf("0\n");
		}
	}
	printf("1\n");
	for(i=0;i<n;i++){
		printf("%d ",cmp[2 * i] > cmp[2 * i + 1]);
	}
	printf("\n");
	return 0;
}