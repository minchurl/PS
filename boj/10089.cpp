#include<bits/stdc++.h>
#define MAX_N 200005
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(),(v).end()
using namespace std;
typedef pair<int,int> pii;
struct node{
	int t,s,e,v;
};
int n,m;
int rn,ans;
int ansx,ansy;
int idx[MAX_N];
int buff[4*MAX_N];
int pa[20][MAX_N],dep[MAX_N];
pii tree[4*MAX_N];
vector<node> V;
vector<int>	adj[MAX_N];
pii range[MAX_N];
void dfs(int x){
	range[x].fi=n+1;
	if(adj[x].size()==1){
		range[x].fi=range[x].se=++rn;
		idx[rn]=x;
		return;
	}
	for(int y:adj[x]){
		if(range[y].fi)	continue;
		pa[0][y]=x;
		dep[y]=dep[x]+1;
		dfs(y);
		range[x].fi=min(range[x].fi,range[y].fi);
		range[x].se=max(range[x].se,range[y].se);
	}
}
void add(int sx,int sy,int ex,int ey,int v){
	if(sx>ex || sy>ey)	return;
	V.pb({sx,sy,ey,v});V.pb({ex+1,sy,ey,-v});
}
void spread(int x){
	tree[2*x].fi+=buff[x];tree[2*x+1].fi+=buff[x];
	buff[2*x]+=buff[x];buff[2*x+1]+=buff[x];
	buff[x]=0;
}
void update(int x,int l,int r,int s,int e,int v){
	if(l!=r)	spread(x);
	if(e<l || r<s)	return;
	if(s<=l && r<=e){
		tree[x].fi+=v;
		if(tree[x].se==0)	tree[x].se=l;
		buff[x]+=v;
		return;
	}
	int mid=(l+r)>>1;
	update(2*x,l,mid,s,e,v);
	update(2*x+1,mid+1,r,s,e,v);
	tree[x]=max(tree[2*x],tree[2*x+1]);
	tree[x].fi+=buff[x];
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y,v;
	scanf("%d",&n);
	for(i=1;i<n;i++){
		scanf("%d %d",&x,&y);
		adj[x].eb(y);
		adj[y].eb(x);
	}

	if(n==2){
		int sum=0;
		for(i=0;i<m;i++){
			scanf("%d %d",&x,&y,&v);
			sum+=v;
		}
		return !printf("1 2 %d\n",sum);
	}
	for(i=1;i<=n;i++){
		if(adj[i].size()>1)	break;
	}
	dfs(i);
	for(i=1;i<19;i++){
		for(int j=1;j<=n;j++)	pa[i][j]=pa[i-1][pa[i-1][j]];
	}
	scanf("%d",&m);
	for(i=0;i<m;i++){
		scanf("%d %d %d",&x,&y,&v);
		if(range[x]>range[y])	swap(x,y);
		if(range[x].fi==range[y].fi && range[x].se<range[y].se)	swap(x,y);
		
		
		if(range[x].fi<=range[y].fi && range[y].se<=range[x].se){
			int z=y;
			for(int j=18;j>=0;j--){
				if(dep[pa[j][z]]<=dep[x])	continue;
				z=pa[j][z];
			}
			
			add(1,range[y].fi,range[z].fi-1,range[y].se,v);
			add(range[y].fi,range[z].se+1,range[y].se,rn,v);
			continue;
		}
		
		add(range[x].fi,range[y].fi,range[x].se,range[y].se,v);
		
	}
	sort(all(V),[&](const node x,const node y){return x.t<y.t;});
	x=-10;
	for(node p:V){
		if(x!=p.t){
			if(ans<tree[1].fi){
				ans=tree[1].fi;
				ansx=x;
				ansy=tree[1].se;
			}
		}
		x=p.t;
		update(1,1,rn,p.s,p.e,p.v);
	}
	if(x<=rn && ans<tree[1].fi){
		ans=tree[1].fi;
		ansx=x;
		ansy=tree[1].se;
	}
	if(m==0){
		printf("1 2 0\n");
		return 0;
	}
	printf("%d %d %d\n",idx[ansx],idx[ansy],ans);
	return 0;
}

