#include<bits/stdc++.h>
#define MAX_N 605
#define MAX_M 10005
#define inf (1LL<<60)
using namespace std;
typedef long long LL;
struct point{
	LL x,y,c;
}arr[MAX_N+MAX_M],po[MAX_M],ver[MAX_N],pi;
LL n,m,l,sum,t[MAX_N][MAX_N],ans;
LL ccw(point x,point y,point z){return (x.x*y.y+y.x*z.y+z.x*x.y)-(x.y*y.x+y.y*z.x+z.y*x.x);}
bool angle_sort(point x,point y){
	if(ccw(x,pi,y)==0)	return x.c<y.c;
	return ccw(x,pi,y)>0;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,j,k,x;
	scanf("%lld",&n);
	for(i=1;i<=n;i++)	scanf("%lld %lld",&ver[i].x,&ver[i].y);
	scanf("%lld",&m);
	for(i=1;i<=m;i++){
		scanf("%lld %lld %lld",&po[i].x,&po[i].y,&po[i].c);
		sum+=po[i].c;
	}
	for(i=1;i<=n;i++){
		l=0;
		for(j=1;j<=n;j++){
			if(i==j)	continue;
			arr[l]=ver[j];
			arr[l++].c=-100005;
		}
		for(j=1;j<=m;j++)	arr[l++]=po[j];
		pi=ver[i];
		sort(arr,arr+l,angle_sort);
		x=i%n+1;
		for(j=0;j<l;j++){
			if(arr[j].c==-100005){k=t[i][x];x=x%n+1;t[i][x]=k;}
			else	t[i][x]+=arr[j].c;
		}
	}
	ans=inf;
	for(i=1;i<=n;i++){
		for(j=i+1;j<=n;j++){
			for(k=j+1;k<=n;k++)	ans=min(ans,t[i][j]+t[j][k]+t[k][i]);
		}
	}
	printf("%lld\n",sum-ans);
	return 0;
}
