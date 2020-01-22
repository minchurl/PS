#include<bits/stdc++.h>
#define MAX_N 1000005
using namespace std;
typedef long long LL;
LL arr[MAX_N],sum[1005],n,m,k,ans;
LL add(LL x,LL y){
	LL z=0;
	for(LL i=x;i<=y;i++)	z+=arr[i];
	return z;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,x,y,z,p,q;
	scanf("%lld %lld %lld",&n,&m,&k);
	m+=k;
	k=sqrt(n);
	for(i=1;i<=n;i++){
		scanf("%lld",&arr[i]);
		sum[i/k]+=arr[i];
	}
	while(m--){
		scanf("%lld",&z);
		if(z==1){
			scanf("%lld %lld",&x,&y);
			sum[x/k]+=y-arr[x];
			arr[x]=y;
		}else{
			scanf("%lld %lld",&x,&y);
			p=x/k;
			q=y/k;
			ans=0;
			if(p==q)	ans=add(x,y);
			else{
				for(i=p+1;i<q;i++)	ans+=sum[i];
				ans+=add(x,(p+1)*k-1)+add(q*k,y);
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
