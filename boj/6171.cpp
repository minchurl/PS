#include<bits/stdc++.h>
#define MAX_N 50005
#define LL long long
using namespace std;
struct node{
	LL x,y;
	bool operator < (node d) const{
		return x<d.x;
	};
}arr[MAX_N],dq[MAX_N],P;
LL n,s,e,t[MAX_N];
bool is_ok(node x,node y,node z){return (x.x-y.x)*(z.y-x.y)<=(x.x-z.x)*(y.y-x.y);}
int main(){
	freopen("input.txt","r",stdin);
	LL i,x,y;
	node p;
	scanf("%lld",&n);
	x=y=0;
	for(i=1;i<=n;i++){
		scanf("%lld %lld",&arr[i].x,&arr[i].y);
		x=max(x,arr[i].x);
		y=max(y,arr[i].y);
	}
	arr[++n].x=x;arr[n].y=0;
	arr[++n].x=0;arr[n].y=y;
	sort(arr+1,arr+n+1);
	e=1;
	for(i=2;i<=n;i++){
		while(e>1 && arr[e].y<=arr[i].y)	e--;
		arr[++e]=arr[i];
	}
	n=e;
	s=e=0;
	dq[e].x=arr[1].y;
	dq[e++].y=0;
	for(i=2;i<n;i++){
		while(e-s>1 && dq[s].x*arr[i].x+dq[s].y>=dq[s+1].x*arr[i].x+dq[s+1].y)	s++;
		t[i]=dq[s].x*arr[i].x+dq[s].y;
		p.x=arr[i+1].y;
		p.y=t[i];
		while(e-s>1 && is_ok(dq[e-2],dq[e-1],p))	e--;
		dq[e++]=p;
	}
	printf("%lld\n",t[n-1]);
	return 0;
}
