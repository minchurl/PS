#include<bits/stdc++.h>
#define MAX_N 2505
#define MAX_M 4005
#define eb emplace_back
#define fi first
#define se second
#define inf (1LL<<60)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pil;
LL n,m,dst[MAX_N][MAX_N];
pil V[MAX_N];
priority_queue<pil> pq;
vector<pil> adj[MAX_N];
void dijkstra(LL s,LL k){
	pq.push({-dst[s][s],s});
	while(pq.size()){
		pil p=pq.top();pq.pop();
		if(dst[s][p.se]!=-p.fi)	continue;
		for(pil y:adj[p.se]){
			if(dst[s][y.fi]<=dst[s][p.se]+y.se*k)	continue;
			dst[s][y.fi]=dst[s][p.se]+y.se*k;
			pq.push({-dst[s][y.fi],y.fi});
		}
	}
}
int main(){
	LL i,j,x,y,v;
	scanf("%lld %lld",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%lld",&V[i].fi);
		V[i].se=i;
		for(j=1;j<=n;j++)	dst[i][j]=inf;
	}
	for(j=1;j<=n;j++)	dst[0][j]=inf;
	sort(V+1,V+n+1);
	while(m--){
		scanf("%lld %lld %lld",&x,&y,&v);
		adj[x].eb(y,v);
		adj[y].eb(x,v);
	}
	dst[0][1]=0;
	for(i=n;i>=1;i--){
		dst[V[i].se][V[i].se]=dst[0][V[i].se];
		dijkstra(V[i].se,V[i].fi);
		for(j=1;j<=n;j++)	dst[0][j]=min(dst[0][j],dst[V[i].se][j]);
	}
	printf("%lld\n",dst[0][n]);
	return 0;
}
