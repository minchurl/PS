#include<bits/stdc++.h>
#define MAX_N 2005
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define rev(x) ((x)>(n+m)?((x)-(n+m)):((x)+(n+m)))
using namespace std;
typedef long long LL;
int n,m;
int sn,dn;
int dfn[4*MAX_N],scc[4*MAX_N];
stack<int> st;
vector<int> adj[4*MAX_N];
void add(int a,int b,int c,int d){
	adj[rev(a)].eb(b);adj[rev(d)].eb(b);
	adj[rev(a)].eb(c);adj[rev(d)].eb(c);
	adj[rev(b)].eb(a);adj[rev(c)].eb(a);
	adj[rev(b)].eb(d);adj[rev(c)].eb(d);
}
int dfs(int x){
	int z;
	z=dfn[x]=++dn;
	st.push(x);
	for(int y:adj[x]){
		if(!dfn[y])	z=min(z,dfs(y));
		else if(!scc[y])	z=min(z,dfn[y]);
	}
	if(z>=dfn[x]){
		sn++;
		while(1){
			scc[st.top()]=sn;
			if(st.top()==x)	break;
			st.pop();
		}st.pop();
	}
	return z;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,T,k;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d",&n,&m,&k);
		sn=0;
		dn=0;
		while(k--){
			int sx,sy,ex,ey;
			int a,b,c,d;
			scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
			a=sx+(ey>sy?0:n+m);
			b=sy+n+(ex>sx?0:n+m);
			c=ex+(ey>sy?0:n+m);
			d=ey+n+(ex>sx?0:n+m);
			if(sx==ex && sy==ey)	continue;
			if(sx==ex)	adj[rev(a)].eb(a);
			else if(sy==ey)	adj[rev(b)].eb(b);
			else	add(a,b,c,d);
		}
		for(i=1;i<=2*(n+m);i++){
			if(!dfn[i])	dfs(i);
		}
		bool Z=true;
		for(i=1;i<=(n+m);i++){
			dfn[i]=dfn[i+n+m]=0;
			adj[i].clear();adj[i+n+m].clear();
			if(scc[i]==scc[i+n+m])	Z=false;
			scc[i]=scc[i+n+m]=0;
		}
		
		printf("%s\n",Z?"Yes":"No");
	}
	return 0;
}
