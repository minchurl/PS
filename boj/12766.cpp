#include<bits/stdc++.h>
#define MAX_N 5005
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define LL_inf (1LL<<60)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
priority_queue<pil> pq;
LL n,b;
LL sum[MAX_N],dst[MAX_N],cost[MAX_N],t[MAX_N][MAX_N];
vector<pil> net[2][MAX_N];
void dijkstra(LL z){
	LL i;
	pil p,q;
	for(i=1;i<=n;i++)	dst[i]=LL_inf;
	dst[b+1]=0;
	pq.push(mp(-dst[b+1],b+1));
	while(!pq.empty()){
		p=pq.top();pq.pop();
		if(dst[p.se]!=-p.fi)	continue;
		LL sz=net[z][p.se].size();
		while(sz--){
			q=net[z][p.se][sz];
			if(dst[q.fi]>dst[p.se]+q.se){
				dst[q.fi]=dst[p.se]+q.se;
				pq.push(mp(-dst[q.fi],q.fi));
			}
		}
	}
}
void dnc(LL z,LL l,LL r,LL s,LL e){
	if(s>e)	return;
	LL mid=(s+e)>>1;
	LL i,x,y;
	x=LL_inf;
	y=min(mid,r);
	for(i=min(mid,r);i>=l;i--){
		if(x>t[z-1][i-1]+(sum[mid]-sum[i-1])*(mid-i)){
			x=t[z-1][i-1]+(sum[mid]-sum[i-1])*(mid-i);
			y=i;
		}
	}
	t[z][mid]=x;
	dnc(z,l,y,s,mid-1);
	dnc(z,y,r,mid+1,e);
}
int main(){
	LL i;
	LL u,v,l;
	LL s,r;
	freopen("input.txt","r",stdin);
	scanf("%lld %lld %lld %lld",&n,&b,&s,&r);
	while(r--){
		scanf("%lld %lld %lld",&u,&v,&l);
		net[0][u].pb(mp(v,l));
		net[1][v].pb(mp(u,l));
	}
	dijkstra(0);
	for(i=1;i<=b;i++)	cost[i]=dst[i];
	dijkstra(1);
	for(i=1;i<=b;i++)	cost[i]+=dst[i];
	sort(cost+1,cost+b+1);
	for(i=1;i<=b;i++){
		sum[i]=sum[i-1]+cost[i];
		t[1][i]=sum[i]*(i-1);
	}
	for(i=2;i<=s;i++)	dnc(i,1,b,1,b);
	printf("%lld\n",t[s][b]);
	return 0;
}
