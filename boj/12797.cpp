#include<bits/stdc++.h>
#define MAX_N 1005
#define MOD 1000000007LL
#define mod(x) ((x)>0?(x)%MOD:(MOD-(((-x))%MOD))%MOD)
#define inv(x) (Pow((x),MOD-2))
using namespace std;
typedef long long LL;
LL n,m,V[MAX_N],ans;
inline LL Pow(LL x,LL y){
	LL z=1;
	while(y){
		if(y%2)	z=mod(z*x);
		y/=2;
		x=mod(x*x);
	}
	return z;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,j,x;
	scanf("%lld %lld",&n,&m);
	for(i=1;i<=m;i++)	scanf("%lld",&V[i]);
	for(i=1;i<=m;i++){
		x=Pow(V[i],n);
		for(j=1;j<=m;j++){
			if(j==i)	continue;
			x=mod(x*inv(V[i]-V[j]));
			x=mod(x*V[i]);
		}
		ans=mod(ans+x);
	}
	printf("%lld\n",ans);
	return 0;
}
