#include<bits/stdc++.h>
#define MAX_N 305
#define MAX_K 262150
#define mod 1000000007
using namespace std;
typedef long long LL;
LL n,m,a[MAX_K],b[MAX_K],F[MAX_N],ans;
void update(LL cn,LL x,LL y,LL j,LL prev){
	if(!cn){
		a[j]=(a[j]+b[x])%mod;
		return;
	}
	if(y%2==0){
		update(cn-1,2*x,y/2,j,0);
		update(cn-1,2*x+1,y/2,j,1);
		return;
	}
	if(prev==0){
		
	}
}
int main(){
	LL i,j,x,k,l;
	scanf("%lld %lld",&n,&m);
	F[0]=1;F[1]=2;
	for(i=2;i<=m;i++)	F[i]=(F[i-1]+F[i-2])%mod;
	if(n<m)	swap(n,m);
	x=m;k=1;
	while(x--)	k*=2;
	start(m,0);
	a[0]=1;
	for(i=1;i<=n;i++){
		for(j=0;j<k;j++){b[j]=0;update(cn,0,j,j,0);}
		for(j=0;j<k;j++)	a[j]=b[j];
	}
	for(j=0;j<k;j++)	ans=(ans+b[j])%mod;
	printf("%lld\n",ans);
	return 0;
}
