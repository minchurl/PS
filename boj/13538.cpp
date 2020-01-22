#include<bits/stdc++.h>
#define MAX_N 500005
using namespace std;
struct node{
	int x,l,r;
}tree[25*MAX_N];
int n,m=1,root[MAX_N];
void make(int idx,int x,int y,int v){
	tree[y]=tree[x];
	tree[y].x++;
	if(idx<0)	return;
	if(v&(1<<idx)){
		tree[y].r=m;m++;
		make(idx-1,tree[x].r,tree[y].r,v);
	}else{
		tree[y].l=m;m++;
		make(idx-1,tree[x].l,tree[y].l,v);
	}
}
int xorq(int idx,int s,int e,int v){
	if(idx<0)	return 0;
	int lsum=tree[tree[e].l].x-tree[tree[s].l].x;
	int rsum=tree[tree[e].r].x-tree[tree[s].r].x;
	if((lsum && (v&(1<<idx))) || !rsum)	return xorq(idx-1,tree[s].l,tree[e].l,v);
	return (1<<idx)|xorq(idx-1,tree[s].r,tree[e].r,v);
}
int sq(int idx,int s,int e,int p){
	if(idx<0)	return tree[e].x-tree[s].x;
	if(p&(1<<idx))	return tree[tree[e].l].x-tree[tree[s].l].x+sq(idx-1,tree[s].r,tree[e].r,p);
	return sq(idx-1,tree[s].l,tree[e].l,p);
}
int kq(int idx,int s,int e,int v){
	if(idx<0)	return 0;
	int lsum=tree[tree[e].l].x-tree[tree[s].l].x;
	if(lsum<v)	return (1<<idx)|kq(idx-1,tree[s].r,tree[e].r,v-lsum);
	return kq(idx-1,tree[s].l,tree[e].l,v);
}
int main(){
	freopen("input.txt","r",stdin);
	int q,ty,s,e,x,y;
	scanf("%d",&q);
	while(q--){
		scanf("%d",&ty);
		if(ty==1){//add
			scanf("%d",&x);n++;
			root[n]=m;m++;
			make(18,root[n-1],root[n],x);
		}
		if(ty==3){//delect
			scanf("%d",&x);
			n-=x;
		}
		if(ty==2){//xor
			scanf("%d %d %d",&s,&e,&x);s--;
			printf("%d\n",xorq(18,root[s],root[e],x));
		}
		if(ty==4){//smallar than x
			scanf("%d %d %d",&s,&e,&x);s--;
			printf("%d\n",sq(18,root[s],root[e],x));
		}
		if(ty==5){//kth
			scanf("%d %d %d",&s,&e,&x);s--;
			printf("%d\n",kq(18,root[s],root[e],x));
		}
	}
	return 0;
}
