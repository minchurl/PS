#include<bits/stdc++.h>
#define MAX_N 1005
#define inf 0x3fffffff
#define pb push_back
using namespace std;
struct edge{
	int s,e,v,inv,num,cap;
};
int n,m;
int dst[2*MAX_N],from[2*MAX_N];
bool chk[2*MAX_N];
vector<edge> adj[2*MAX_N];
queue<int> Q;
int spfa(){
	while(Q.size())	Q.pop();
	for(int i=1;i<=2*n;i++)	chk[i]=false,dst[i]=inf;
	Q.push(1);
	dst[1]=0;
	while(Q.size()){
		int x=Q.front();Q.pop();chk[x]=false;
		for(edge p:adj[x]){
			if(p.cap && dst[p.e]>dst[x]+p.v){
				dst[p.e]=dst[x]+p.v;
				from[p.e]=p.inv;
				if(!chk[p.e])	Q.push(p.e);
				chk[p.e]=true;
			}
		}
	}
	return dst[2*n];
}
void change(int x){
	edge &p=adj[x][from[x]];
	p.cap++;
	adj[p.e][p.inv].cap--;
	if(p.e!=1)	change(p.e);
}
int main(){
	while(scanf("%d %d",&n,&m)+1){
		int p,q,x,y,v,i;
		while(m--){
			scanf("%d %d %d",&x,&y,&v);
			p=adj[2*x].size();q=adj[2*y-1].size();
			adj[2*x].pb({2*x,2*y-1,v,q,p,1});
			adj[2*y-1].pb({2*y-1,2*x,-v,p,q,0});
		}
		for(i=1;i<=n;i++){
			p=adj[2*i].size();q=adj[2*i-1].size();
			adj[2*i].pb({2*i,2*i-1,0,q,p,0});
			adj[2*i-1].pb({2*i-1,2*i,0,p,q,(i==1 || i==n)?2:1});
		}
		int ans=0;
		while(1){
			x=spfa();
			if(x==inf)	break;
			ans+=x;
			change(2*n);
		}		
		printf("%d\n",ans);		
		for(i=1;i<=2*n;i++)	adj[i].clear(),adj[i].resize(0);
	}
	return 0;
}
