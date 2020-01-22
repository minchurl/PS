#include<bits/stdc++.h>
#define MAX_N 200005
#define all(V) (V).begin(),(V).end()
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define inf 0x3fffffff
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
struct range{
	int l,r;
}ran[MAX_N];
int rn,n,pa[20][MAX_N],dep[MAX_N];
int tree[4*MAX_N];
vector<int> adj[MAX_N];
//dfs ordering
void dfs(int x){
	ran[x].l=ran[x].r=rn++;
	for(int y:adj[x]){
		dep[y]=dep[x]+1;
		dfs(y);
		ran[x].r=ran[y].r;
	}
}
void make_table(){
	for(int i=1;i<=18;i++){
		for(int j=1;j<=n;j++)	pa[i][j]=pa[i-1][pa[i-1][j]];
	}
}
int get_lca(int x,int y){
	if(dep[x]<dep[y])	swap(x,y);
	for(int i=18;i>=0;i--)	if(dep[pa[i][x]]>=dep[y])	x=pa[i][x];
	if(x==y)	return x;
	for(int i=18;i>=0;i--){
		if(pa[i][x]!=pa[i][y]){
			x=pa[i][x];
			y=pa[i][y];
		}
	}
	return pa[0][x];
}
//segtree with lazy propagation
void spread(int x){
	tree[2*x]=max(tree[2*x],tree[x]);
	tree[2*x+1]=max(tree[2*x+1],tree[x]);
}
int read(int x,int l,int r,int p){
	if(l!=r)	spread(x);
	if(p<l || p>r)	return inf;
	if(l==r)	return tree[x];
	int mid=(l+r)>>1;
	int y=read(2*x,l,mid,p);
	int z=read(2*x+1,mid+1,r,p);
	return min(y,z);
}
void update(int x,int l,int r,int s,int e,int v){
	if(l!=r)	spread(x);
	if(e<l || s>r)	return;
	if(s<=l && r<=e){
		tree[x]=max(tree[x],v);
		return;
	}
	int mid=(l+r)>>1;
	update(2*x,l,mid,s,e,v);
	update(2*x+1,mid+1,r,s,e,v);
}
int main(){
	int i,x,y,z,Q;
	scanf("%d %d",&n,&Q);
	for(i=2;i<=n;i++){
		scanf("%d",&x);
		pa[0][i]=x;
		adj[x].eb(i);
		tree[i]=1;
	}
	tree[1]=dep[1]=1;dfs(1);
	make_table();
	while(Q--){
		scanf("%d %d",&x,&y);
		int r=dep[get_lca(x,y)];
		int p=read(1,ran[1].l,ran[1].r,ran[x].l);
		int q=read(1,ran[1].l,ran[1].r,ran[y].l);
		printf("%s\n",r<max(p,q)?"NO":"YES");
		scanf("%d",&z);
		if(z==0)	continue;
		if(r<max(p,q))	update(1,ran[1].l,ran[1].r,ran[y].l,ran[y].r,dep[y]);
		else	update(1,ran[1].l,ran[1].r,ran[x].l,ran[x].r,dep[x]);
	}
	return 0;
}

