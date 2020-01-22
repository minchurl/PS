#include<bits/stdc++.h>
#define MAX_N 2005
#define LL long long
#define abs(x) ((x)>0?(x):(-(x)))
using namespace std;
struct node{
	LL x,y,idx,cost;
}arr[2*MAX_N],point[2*MAX_N],pi;
LL n,m,k,ans;
bool chk[MAX_N];
LL ccw(node x,node y,node z){
	LL temp=x.x*y.y+y.x*z.y+z.x*x.y-x.y*y.x-y.y*z.x-z.y*x.x;
	if(temp==0)	return 0;
	return temp>0?1:-1;
}
bool angle_sort(node x,node y){
	if(ccw(x,pi,y)==0)	return x.cost>y.cost;
	if(ccw(x,pi,y)==-1)	return true;
	if(ccw(x,pi,y)==1)	return false;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,j,x,y;
	node p;
	scanf("%lld",&n);
	m=0;
	for(i=1;i<=n;i++){
		scanf("%lld %lld %lld",&arr[m+1].x,&arr[m+2].x,&arr[m+1].y);
		arr[m+2].y=arr[m+1].y;
		arr[m+1].cost=arr[m+2].cost=abs(arr[m+1].x-arr[m+2].x);
		arr[m+1].idx=arr[m+2].idx=i;
		m+=2;
	}
	for(i=1;i<=m;i++){
		k=0;
		pi=arr[i];
		for(j=1;j<=n;j++)	chk[j]=false;
		for(j=1;j<=m;j++){
			if(arr[i].y==arr[j].y)	continue;
			p=arr[j];
			if(arr[j].y>pi.y){
				p.x=2LL*pi.x-p.x;
				p.y=2LL*pi.y-p.y;
			}
			point[k++]=p;
		}
		sort(point,point+k,angle_sort);
		for(j=0;j<k;j++){
			point[j].cost*=chk[point[j].idx]?-1LL:1LL;
			chk[point[j].idx]=true;
		}
		sort(point,point+k,angle_sort);
		x=pi.cost;
		ans=max(ans,x);
		if(k)	x+=point[0].cost;
		ans=max(ans,x);
		j=0;
		for(j=1;j<k;j++){
			x+=point[j].cost;
			ans=max(ans,x);
		}
		ans=max(ans,x);
	}
	printf("%lld\n",ans);
	return 0;
}
