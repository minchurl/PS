#include<bits/stdc++.h>
#define MAX_N 10005
#define MAX_M 55
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
#define MOD 1000000007
#define cpx_mod(x) (((LD)(((LL)x.real())%MOD)),((LD)(((LL)x.imag())%MOD)))
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
typedef long double LD;
int n,m;
int sn,scc[MAX_N],dn,dfn[MAX_N];
vector<int> adj[MAX_N],lst[MAX_N];
stack<int> st;
int make_scc(int x){
	int z;
	z=dfn[x]=++dn;
	st.push(x);
	for(int y:adj[x]){
		if(!dfn[y])	z=min(z,make_scc(y));
		else if(!scc[y])	z=min(z,dfn[y]);
	}
	if(z==dfn[x]){
		while(st.size()){
			scc[st.top()]=sn+1;
			lst[sn].eb(st.top());
			if(st.top()==x)	break;
			st.pop();
		}st.pop();
		sort(all(lst[sn]));sn++;
	}
	return z;
}
queue<int> Q;
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y;
	scanf("%d %d",&n,&m);
	for(i=0;i<m;i++){
		scanf("%d %d",&x,&y);
		adj[x].eb(y);
	}
	for(i=1;i<=n;i++){
		if(!dfn[i])	make_scc(i);
	}
	printf("%d\n",sn);
	sort(lst,lst+sn,[&](const auto x,const auto y){return x.front()<y.front();});
	for(i=0;i<sn;i++){
		for(int z:lst[i])	printf("%d ",z);
		printf("-1\n");
	}
	return 0;
}
