#include<bits/stdc++.h>
#define MAX_N 100005
#define pb push_back
using namespace std;
struct node{
	int c;
	node *l,*r;
	node(int c,node *l,node *r):c(c),l(l),r(r){}
	node *update(int idx,int p){
		if(idx<0)	return new node(c+1,NULL,NULL);
		if(p>>idx&1)	return new node(c+1,l,r->update(idx-1,p));
		return new node(c+1,l->update(idx-1,p),r);
	}
}*tree[MAX_N];
int n,m,arr[MAX_N],dep[MAX_N],pa[20][MAX_N];
bool chk[MAX_N];
vector<int> X,net[MAX_N];
void make(int x){
	int y,sz=net[x].size();
	chk[x]=true;
	while(sz--){
		y=net[x][sz];
		if(chk[y])	continue;
		tree[y]=tree[x]->update(16,arr[y]);
		pa[0][y]=x;
		dep[y]=dep[x]+1;
		make(y);
	}
}
void make_pa(){for(int i=1;i<=16;i++)	for(int j=1;j<=n;j++)	pa[i][j]=pa[i-1][pa[i-1][j]];}
int lca(int x,int y){
	int i;
	if(dep[x]>dep[y])	swap(x,y);
	for(i=16;i>=0;i--){
		if(dep[x]<=dep[pa[i][y]])	y=pa[i][y];
	}
	if(x==y)	return x;
	for(i=16;i>=0;i--){
		if(pa[i][x]==pa[i][y])	continue;
		x=pa[i][x];
		y=pa[i][y];
	}
	return pa[0][x];
}
int kQ(int idx,node *x,node *y,node *z,node *k,int p){
	if(idx<0)	return 0;
	int c=x->l->c+y->l->c-z->l->c-k->l->c,d=x->r->c+y->r->c-z->r->c-k->r->c;
	if(c>=p || d==0)	return kQ(idx-1,x->l,y->l,z->l,k->l,p);
	return (1<<idx)|kQ(idx-1,x->r,y->r,z->r,k->r,p-c);
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y,z,q;
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++){scanf("%d",&arr[i]);X.pb(arr[i]);}
	sort(X.begin(),X.end());X.erase(unique(X.begin(),X.end()),X.end());
	for(i=1;i<=n;i++)	arr[i]=lower_bound(X.begin(),X.end(),arr[i])-X.begin();
	for(i=1;i<n;i++){
		scanf("%d %d",&x,&y);
		net[x].pb(y);net[y].pb(x);
	}
	tree[0]=new node(0,NULL,NULL);
	tree[0]->l=tree[0]->r=tree[0];
	tree[1]=tree[0]->update(16,arr[1]);
	dep[1]=1;
	make(1);
	make_pa();
	while(m--){
		scanf("%d %d %d",&x,&y,&i);
		q=lca(x,y);
		printf("%d\n",X[kQ(16,tree[x],tree[y],tree[q],tree[pa[0][q]],i)]);
	}
	return 0;
}
