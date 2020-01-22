#include<bits/stdc++.h>
#include<inttypes.h>
#define MAX_N 100005
#define abs(x) ((x)>0?(x):(-(x)))
#define sq(x) ((x)*(x))
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
int n,k,ans;
int max_x,max_depth;
int from[MAX_N],depth[MAX_N];
vector<pii> net[MAX_N];
void find_far(int x){
	int sz=net[x].size();
	pii p;
	if(max_depth<depth[x]){
		max_depth=depth[x];
		max_x=x;
	}
	while(sz--){
		p=net[x][sz];
		if(p.fi==from[x])	continue;
		depth[p.fi]=depth[x]+p.se;
		from[p.fi]=x;
		find_far(p.fi);
	}
	return;
}
void update_route(int x){
	int y=from[x];
	if(x==y)	return;
	int sz=net[x].size();
	pii p;
	while(sz--){
		p=net[x][sz];
		if(p.fi==y){
			net[x][sz].se=-1;
			break;
		}
	}
	while(sz--){
		p=net[y][sz];
		if(p.fi==x){
			net[y][sz].se=-1;
			break;
		}
	}
	update_route(y);
	return;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y;
	scanf("%d %d",&n,&k);
	for(i=1;i<n;i++){
		scanf("%d %d",&x,&y);
		net[x].pb(make_pair(y,1));
		net[y].pb(make_pair(x,1));
	}
	ans=2*(n-1)+k;
	max_x=1;
	max_depth=-100005;
	from[1]=1;
	depth[1]=0;
	find_far(1);
	x=max_x;
	max_x=1;
	max_depth=-100005;
	from[x]=x;
	depth[x]=0;
	find_far(x);
	printf("%d\n",max_depth);
	ans-=max_depth;
	if(k==1)	return !printf("%d\n",ans);
	update_route(max_x);
	
	max_x=1;
	max_depth=-100005;
	from[1]=1;
	depth[1]=0;
	find_far(1);
	x=max_x;
	max_x=1;
	max_depth=-100005;
	from[x]=x;
	depth[x]=0;
	find_far(x);
	ans-=max_depth;
	printf("%d\n",max_depth);
	return !printf("%d\n",ans);
}
