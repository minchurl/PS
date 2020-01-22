#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n,num;
LL pn,prime[4005];
LL cnt,Z,ans=1;
LL an,arr[4005];
void f(LL c,LL x,LL y){
	if(c==an){
		cnt+=(y?(-1LL):1LL)*(Z/x);
		while(cnt<0)	cnt+=((LL)(1e9)+7LL);
		cnt%=((LL)(1e9)+7);
		return;
	}
	f(c+1,x,y);
	f(c+1,x*arr[c],!y);
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,j,x,prev,curr;
	prime[pn++]=2;
	for(i=3;i<=32623;i+=2){
		for(j=1;j<pn;j++){
			if(i%prime[j]==0)	break;
		}
		if(j==pn) prime[pn++]=i;
	}
	scanf("%lld %lld",&n,&num);
	scanf("%lld",&prev);
	for(i=2;i<=n;i++){
		scanf("%lld",&curr);
		if(prev<curr)	return !printf("0\n");
		x=prev/curr;
		an=0;
		for(j=0;j<pn;j++){
			if(prime[j]>x)	break;
			if(x%prime[j]==0)	arr[an++]=prime[j];
			while(x%prime[j]==0)	x/=prime[j];
		}
		if(x!=1)	arr[an++]=x;
		Z=num/curr;
		cnt=0;
		f(0,1,0);
		ans*=cnt;
		ans%=((LL)(1e9)+7LL);
		prev=curr;
	}
	printf("%lld\n",ans);
	return 0;
}
