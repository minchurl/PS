#include<bits/stdc++.h>
#define MAX_N 30005
using namespace std;
int n,arr[MAX_N],tree[4*MAX_N],ans[MAX_N];
void update(int x,int l,int r,int p,int v){
	int mid=(l+r)>>1;
	tree[x]+=v;
	if(l==r)	return;
	if(p<=mid)	update(2*x,l,mid,p,v);
	else	update(2*x+1,mid+1,r,p,v);
}
int read(int x,int l,int r,int v){
	int mid=(l+r)>>1;
	if(l==r)	return l;
	if(tree[2*x+1]<v)	return read(2*x,l,mid,v-tree[2*x+1]);
	return read(2*x+1,mid+1,r,v);
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&arr[i]);
		update(1,1,n,i,1);
	}
	for(i=n;i>=1;i--){
		if(arr[i]+1>i)	return !printf("NIE\n");
		x=read(1,1,n,arr[i]+1);
		update(1,1,n,x,-1);
		ans[i]=x;
	}
	for(i=1;i<=n;i++)	printf("%d\n",ans[i]);
	return 0;
}
