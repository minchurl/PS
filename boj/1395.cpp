#include<bits/stdc++.h>
#define MAX_N 100005
using namespace std;
struct node{
	int f,t,c;
}tree[4*MAX_N];
int n,m;
void init(int x,int l,int r){
	int mid=(l+r)>>1;
	if(l==r){tree[x].f=1;return;}
	init(2*x,l,mid);init(2*x+1,mid+1,r);
	tree[x].f=r-l+1;
}
void update(int x,int l,int r,int s,int e){
	if(l>r)	return;
	int mid=(l+r)>>1;
	if(e<l || s>r)	return;
	if(s<=l && r<=e){
		tree[x].c++;
		swap(tree[x].f,tree[x].t);
		return;
	}
	update(2*x,l,mid,s,e);
	update(2*x+1,mid+1,r,s,e);
	tree[x].f=tree[2*x].f+tree[2*x+1].f;
	tree[x].t=tree[2*x].t+tree[2*x+1].t;
	if(tree[x].c%2)	swap(tree[x].f,tree[x].t);
}
node read(int x,int l,int r,int s,int e){
	if(l>r)	return {0,0};
	int mid=(l+r)>>1;
	if(e<l || s>r)	return {0,0};
	if(s<=l && r<=e)	return tree[x];
	node L=read(2*x,l,mid,s,e);
	node R=read(2*x+1,mid+1,r,s,e);
	if(tree[x].c%2)	return {L.t+R.t,L.f+R.f};
	return {L.f+R.f,L.t+R.t};
}
int main(){
	freopen("input.txt","r",stdin);
	int z,s,e;
	node p;
	scanf("%d",&n);
	scanf("%d",&m);
	init(1,1,n);
	while(m--){
		scanf("%d %d %d",&z,&s,&e);
		if(s>e)	swap(s,e);
		if(z)	printf("%d\n",read(1,1,n,s,e).t);
		else	update(1,1,n,s,e);
	}
	return 0;
}
