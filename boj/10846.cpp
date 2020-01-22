//omt...
//왜그랬지ㅠㅠ

#include<bits/stdc++.h>
#define MAX_N 2005
#define inf (1LL<<62)
#define LL long long
using namespace std;
LL n,a,b,ans,arr[MAX_N];
LL t[MAX_N];
bool ct[MAX_N][MAX_N];
bool case1(LL x){
	LL i,j,sum,test,y,z,k,l;
	bool p=false;
	y=inf-1;y-=(1LL<<x)-1;
	z=ans&y;
	for(i=0;i<=n;i++)	for(j=0;j<=n;j++)	ct[i][j]=false;
	ct[0][0]=true;
	for(l=1;l<=b;l++){
		for(i=1;i<=n;i++){
			sum=0;
			for(j=i;j>=1;j--){
				sum+=arr[j];
				k=sum&y;
				if((z|k)==z)	ct[l][i]|=ct[l-1][j-1];
			}
			if(l>=a)	p|=ct[l][n];
		}
	}
	return p;
}
bool is_ok(LL x){
	LL i,j,sum,test,y,z,k;
	y=inf-1;y-=(1LL<<x)-1;
	z=ans&y;
	for(i=1;i<=n;i++)	t[i]=inf;
	t[0]=0;
	for(i=1;i<=n;i++){
		sum=0;
		for(j=i;j>=1;j--){
			sum+=arr[j];
			k=sum&y;
			if((z|k)==z)	t[i]=min(t[i],t[j-1]+1);
		}
	}
	return t[n]<=b;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,x;
	scanf("%lld",&n);
	scanf("%lld %lld",&a,&b);
	for(i=1;i<=n;i++)	scanf("%lld",&arr[i]);
	if(n<=100){ans=0;for(i=60;i>=0;i--)	ans|=case1(i)?0LL:(1LL<<i);}
	else{ans=0;for(i=60;i>=0;i--)	ans|=is_ok(i)?0LL:(1LL<<i);}
	printf("%lld\n",ans);
	return 0;
}
