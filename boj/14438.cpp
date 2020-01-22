#include<bits/stdc++.h>
#define MAX_N 100005
#define fi first
#define se second
#define inf 0x3fffffff
using namespace std;
typedef pair<int,int> pii;
int n;
pii tree[4*MAX_N];
void update(int x,int l,int r,int p,int v){
	if(p<l || p>r){
		return ;
	}
	
	if(l==r){
	
		tree[x].fi=v;
		tree[x].se=l;	
		
		return ;
	}
	int mid = (l + r) >> 1;
	
	update(2*x,l,mid,p,v);
	update(2*x+1,mid+1,r,p,v);
	
	tree[x]=min(tree[2*x],tree[2*x+1]);
	
}
pii read(int x,int l,int r,int s,int e){
	if(r<s || e<l){
		return {inf,0};
	}
	if(s<=l && r<=e){
		return tree[x];
	}
	
	int mid = (l + r) >> 1;
	
	return min(read(2*x,l,mid,s,e),read(2*x+1,mid+1,r,s,e));
}

int main(){
	freopen("input.txt","r",stdin);
	int i,j,v,x;
	
	scanf("%d",&n);
	
	for(i=1;i<4*MAX_N;i++)	tree[i].fi=inf;
	
	
	for(i=1;i<=n;i++){
		scanf("%d",&v);
		update(1,1,n,i,v);
	}
	int q;
	scanf("%d",&q);
	while(q--){
		scanf("%d",&x);
		if(x==1){
			scanf("%d %d",&i,&v);
			update(1,1,n,i,v);
		}else{
			scanf("%d %d",&i,&j);
			printf("%d\n",read(1,1,n,i,j).fi);
		}
	}
	return 0;
}
