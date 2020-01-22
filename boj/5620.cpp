#include<bits/stdc++.h>
#define MAX_N 500005
#define inf (1LL<<60)
#define sq(x) ((x)*(x))
using namespace std;
typedef long long LL;
struct node{
	LL x,y;
}V[MAX_N],temp[MAX_N];
LL n;
node dnc(LL l,LL r,LL P){
	if(l==r)	return {inf,l};
	LL mid=(l+r)>>1;
	node p=dnc(l,mid,V[mid].x);
	node q=dnc(mid+1,r,V[mid].x);
	LL d=min(p.x,q.x);
	LL x=mid+1,i,j;
	
	for(i=l;i<=p.y;i++){
		while(x>mid+1 && (V[i].y<=V[x-1].y || sq(V[i].y-V[x-1].y)<=d))	x--;
		d=min(d,sq(V[i].x-V[x].x)+sq(V[i].y-V[x].y));
		while(x<q.y && (V[x+1].y<=V[i].y || sq(V[x+1].y-V[i].y)<=d)){
			x++;
			d=min(d,sq(V[i].x-V[x].x)+sq(V[i].y-V[x].y));
		}
	}
	x=0;
	i=l,j=mid+1;
	while(i<=p.y || j<=q.y){
		if(j>q.y || (i<=p.y && V[i].y<=V[j].y)){
			if(sq(V[i].x-P)<=d)	temp[x++]=V[i];
			i++;
		}else if(i>p.y || (j<=q.y && V[i].y>=V[j].y)){
			if(sq(V[j].x-P)<=d)	temp[x++]=V[j];
			j++;
		}
	}
	for(i=l;i<l+x;i++)	V[i]=temp[i-l];
	return {d,l+x-1};
}
int main(){
	LL i;
	scanf("%lld",&n);
	for(i=0;i<n;i++)	scanf("%lld %lld",&V[i].x,&V[i].y);
	sort(V,V+n,[&](const node x,const node y){return x.x<y.x;});
	printf("%lld\n",dnc(0,n-1,0).x);
	return 0;
}
