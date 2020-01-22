#include<bits/stdc++.h>
#define MAX_N 505
#define mod 1000000007LL
#define pb push_back
typedef long long LL;
using namespace std;
struct node{
	LL s,e;
}arr[MAX_N];
LL n,ans,inv[10*MAX_N];
LL t[MAX_N],sum[MAX_N],ss[MAX_N];
vector<LL> X,lst;
LL Pow(LL x,LL y){
	if(y==0)	return 1;
	if(y==1)	return x;
	LL z=Pow(x,y/2);
	z*=z;z%=mod;
	if(y%2)	z*=x;
	z%=mod;
	return z;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,j,k,s,e,x,y,S,E,cnt,p;
	scanf("%lld",&n);
	for(i=1;i<=n;i++){
		scanf("%lld %lld",&arr[i].s,&arr[i].e);
		arr[i].e++;
		X.pb(arr[i].s);X.pb(arr[i].e);
	}
	for(i=1;i<=2000;i++)	inv[i]=Pow(i,mod-2);
	sort(X.begin(),X.end());X.erase(unique(X.begin(),X.end()),X.end());
	LL sz=X.size();
	ss[0]=1;
	for(i=0;i<=n;i++)	sum[i]=1;
	for(i=1;i<sz;i++){
		s=X[i-1];
		e=X[i];
		lst.resize(0);
		sum[0]=1;
		for(j=1;j<=n;j++){
			if(arr[j].e>=e && arr[j].s<=s)	lst.pb(j);
		}
		p=e-s;
		y=lst.size();
		for(j=0;j<y;j++)	t[j]=(p*sum[lst[j]-1]+(j?t[j-1]:0))%mod;
		for(k=0;k<y;k++)	ss[lst[k]]=(ss[lst[k]]+t[k]-(k?t[k-1]:0)+mod)%mod;
		for(j=2;j<=y && j<=p;j++){
			for(k=y-1;k>=j-1;k--)	t[k]=((t[k-1]*(p-j+1))%mod*inv[j])%mod;
			for(k=0;k<j-1;k++)	t[k]=0;
			for(k=0;k<y;k++)	t[k]=(t[k]+(j?t[k-1]:0))%mod;
			for(k=0;k<y;k++)	ss[lst[k]]=(ss[lst[k]]+t[k]-(k?t[k-1]:0)+mod)%mod;
		}
		x=0;
		sum[0]=1;
		for(j=1;j<=n;j++){
			sum[j]=(sum[j-1]+ss[j])%mod;
		}
	}
	printf("%lld\n",(sum[n]-1+mod)%mod);
	return 0;
}
