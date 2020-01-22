#include<bits/stdc++.h>
#define MAX_N 100005
using namespace std;
typedef long long LL;
LL d,n,ans,T[MAX_N],V[MAX_N];
void dnc(LL s,LL e,LL l,LL r){
	LL mid=(l+r)/2;
	LL maxx=0,maxi=s;
	LL i,x;
	if(l>r)	return;
	for(i=s;i<=e;i++){
		if(i>mid || mid-i>d)	continue;
		x=V[i]+T[mid]*(mid-i);
		if(maxx<x){
			maxx=x;
			maxi=i;
		}
	}
	ans=max(ans,maxx);
	dnc(s,maxi,l,mid-1);
	dnc(maxi,e,mid+1,r);
}
int main(){
	freopen("input.txt","r",stdin);
	LL i;
	scanf("%lld %lld",&n,&d);
	for(i=1;i<=n;i++)	scanf("%lld",&T[i]);
	for(i=1;i<=n;i++)	scanf("%lld",&V[i]);
	dnc(1,n,1,n);
	printf("%lld\n",ans);
	return 0;
}
