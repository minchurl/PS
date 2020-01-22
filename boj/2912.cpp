#include<bits/stdc++.h>
#define MAX_N 300005
#define MAX_M 10005
#define pb push_back
using namespace std;
struct node{
	int x,c;
}tree[4*MAX_N];
int n,c,q,ans[MAX_M];
vector<int> loc[MAX_M];
void update(int x,int l,int r,int p,int c){
	if(l==r){
		tree[x].x=c;
		tree[x].c=1;
		return;
	}
	int mid=(l+r)>>1;
	if(p<=mid)	update(2*x,l,mid,p,c);
	else	update(2*x+1,mid+1,r,p,c);
	if(tree[2*x].x==tree[2*x+1].x){
		tree[x].x=tree[2*x].x;
		tree[x].c=tree[2*x].c+tree[2*x+1].c;
		return;
	}
	if(tree[2*x].c>tree[2*x+1].c)	tree[x]=tree[2*x];
	else	tree[x]=tree[2*x+1];
}
int is_ok(int x,int s,int e){
	int l=lower_bound(loc[x].begin(),loc[x].end(),s)-loc[x].begin();
	int r=lower_bound(loc[x].begin(),loc[x].end(),e+1)-loc[x].begin()-1;
	return ((e-s+1)/2)<(r-l+1)?x:0;
}
int read(int x,int l,int r,int s,int e){
	if(r<s || e<l)	return 0;
	if(s<=l && r<=e)	return is_ok(tree[x].x,s,e);
	int mid=(l+r)/2;
	int p=read(2*x,l,mid,s,e),q=read(2*x+1,mid+1,r,s,e);
	return max(p,q);
}
int main(){
	freopen("input.txt","r",stdin);
	int i,j,x,s,e;
	scanf("%d %d",&n,&c);
	for(i=1;i<=n;i++){
		scanf("%d",&x);
		update(1,1,n,i,x);
		loc[x].pb(i);
	}
	scanf("%d",&q);
	for(i=1;i<=q;i++){
		scanf("%d %d",&s,&e);
		x=read(1,1,n,s,e);
		if(x)	printf("yes %d\n",x);
		else	printf("no\n");
	}
	return 0;
}
