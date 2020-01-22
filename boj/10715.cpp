#include<bits/stdc++.h>
#define MAX_N 100005
#define inf (1LL<<60)
#define LL long long
#define pb push_back
using namespace std;
struct node{
	LL y,cost;
};
struct cmp{
	bool operator()(node x,node y){
		if(x.cost==y.cost)	return x.y>y.y;
		return x.cost>y.cost;
	};
};
priority_queue<node,vector<node>,cmp> Q;
vector<node> net[MAX_N];
node dst[MAX_N];
LL n,m,c,ans,sum;
bool chk[MAX_N];
void dijkstra(){
	LL i,sz;
	node p,q;
	for(i=1;i<=n;i++){dst[i].y=i;dst[i].cost=inf;}
	p.y=1;p.cost=0;
	Q.push(p);
	dst[1].cost=0;
	while(!Q.empty()){
		p=Q.top();Q.pop();
		if(p.cost!=dst[p.y].cost)	continue;
		sz=net[p.y].size();
		while(sz--){
			q=net[p.y][sz];
			if(dst[q.y].cost>dst[p.y].cost+q.cost){
				dst[q.y].cost=dst[p.y].cost+q.cost;
				q.cost=dst[q.y].cost;
				Q.push(q);
			}
		}
	}
}
bool sort_cmp(node x,node y){
	return x.cost<y.cost;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,x,sz;
	node p;
	scanf("%lld %lld %lld",&n,&m,&c);
	for(i=0;i<m;i++){
		scanf("%lld %lld %lld",&x,&p.y,&p.cost);
		net[x].pb(p);
		swap(x,p.y);net[x].pb(p);
		sum+=p.cost;
	}
	dijkstra();
	sort(dst+1,dst+n+1,sort_cmp);
	ans=inf;
	for(i=1;i<=n;i++){
		p=dst[i];
		chk[p.y]=true;
		sz=net[p.y].size();
		while(sz--)	if(chk[net[p.y][sz].y])	sum-=net[p.y][sz].cost;
		ans=min(ans,c*p.cost+sum);
	}
	printf("%lld\n",ans);
	return 0;
}
