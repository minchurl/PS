#include<bits/stdc++.h>
#define MAX_N 100005
#define inf 0x3fffffff
using namespace std;
struct node{
	int x,l,r;
}lst[MAX_N];
int n,m,k,arr[MAX_N],fix[MAX_N];
int net[3*MAX_N][5],pa;
int t[3*MAX_N];
void delect(int x){
	lst[lst[x].l].r=lst[x].r;
	lst[lst[x].r].l=lst[x].l;
	k--;
}
void do_dp(int x){
	if(x<n)	return;
	int p=net[x][0],q=net[x][1],r=net[x][2];
	do_dp(p);do_dp(q);do_dp(r);
	t[x]=min(t[x],min(t[p]+t[q],min(t[q]+t[r],t[r]+t[p])));
}
bool is_ok(int lim){
	int i,j;
	for(i=0;i<=pa;i++)	t[i]=inf;
	for(i=0;i<n;i++){
		if(fix[i]>=lim)	t[i]=0;
		else if(!fix[i])	t[i]=1;
	}
	do_dp(pa);
	for(i=0;i<n-m;i++){
		if(arr[i]>=lim)	t[pa]--;
	}
	return t[pa]<=0;
}
int bin(){
	int s,e,mid;
	s=1;
	e=1000000000;
	while(s<=e){
		mid=(s+e)/2;
		if(is_ok(mid)){
			if(!is_ok(mid+1))	return mid;
			s=mid+1;
		}else{
			if(is_ok(mid-1))	return mid-1;
			e=mid-1;
		}
	}
	return -1;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y;
	scanf("%d %d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d %d",&x,&y);y--;
		fix[y]=x;
	}
	for(i=0;i<n-m;i++)	scanf("%d",&arr[i]);
	int z;
	k=n;
	x=0;
	for(i=0;i<n;i++){
		lst[i].x=i;
		lst[i].l=(i-1+n)%n;
		lst[i].r=(i+1)%n;
	}
	pa=n;
	while(k!=1){
		y=lst[x].r;
		z=lst[y].r;
		delect(y);delect(z);
		net[pa][0]=lst[x].x;net[pa][1]=lst[y].x;net[pa][2]=lst[z].x;
		lst[x].x=pa;
		if(k==1)	break;
		x=lst[x].r;
		pa++;
	}
	printf("%d\n",bin());
	return 0;
}
