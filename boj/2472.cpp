#include<bits/stdc++.h>
#define MAX_N 100005
#define pb push_back
#define all(v) (v).begin(),(v).end()
#define fi first
#define se second
#define inf 0x3fffffff
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pil;
struct node{
	LL a,b,c,i;
}V[MAX_N];
LL n,m,dst[MAX_N],t[MAX_N];
bool ans[MAX_N];
vector<pil> adj[MAX_N];
vector<int> X;
priority_queue<pil> pq;
LL read(LL i){
	LL x=inf;
	for(;i>0;i-=(i&-i))	x=min(x,t[i]);
	return x;
}
void update(LL i,LL x){
	for(;i<=n;i+=(i&-i))	t[i]=min(t[i],x);
}
void dijkstra(LL s){
	for(LL i=1;i<=n;i++)	dst[i]=inf;
	dst[s]=0;
	pq.push({0,s});
	while(pq.size()){
		pil p=pq.top();pq.pop();
		if(-p.fi!=dst[p.se])	continue;
		for(pil y:adj[p.se]){
			if(dst[y.fi]<=dst[p.se]+y.se)	continue;
			dst[y.fi]=dst[p.se]+y.se;
			pq.push({-dst[y.fi],y.fi});
		}
	}
}
int main(){
	LL a,b,c,x,y,v,i;
	scanf("%lld",&n);
	scanf("%lld %lld %lld",&a,&b,&c);
	scanf("%lld",&m);
	for(i=0;i<m;i++){
		scanf("%lld %lld %lld",&x,&y,&v);
		adj[x].pb({y,v});
		adj[y].pb({x,v});
	}
	dijkstra(a);for(i=1;i<=n;i++){V[i].a=dst[i];X.pb(dst[i]);}
	dijkstra(b);for(i=1;i<=n;i++)	V[i].b=dst[i];
	dijkstra(c);for(i=1;i<=n;i++)	V[i].c=dst[i];
	for(i=1;i<=n;i++)	V[i].i=i;
	sort(all(X));X.erase(unique(all(X)),X.end());
	for(i=1;i<=n;i++)	V[i].a=lower_bound(all(X),V[i].a)-X.begin()+1;
	sort(V+1,V+n+1,[&](const node x,const node y){return x.b<y.b;});
	for(i=1;i<=n;i++)	t[i]=inf;
	for(i=1;i<=n;i++){
		if(read(V[i].a-1)<V[i].c)	ans[V[i].i]=1;
		update(V[i].a,V[i].c);
	}
	scanf("%lld",&n);
	while(n--){
		scanf("%lld",&a);
		printf("%s\n",ans[a]?"NO":"YES");
	}
	return 0;
}
