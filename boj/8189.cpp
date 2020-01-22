#include<bits/stdc++.h>
#define MAX_N 500005
#define LL long long
using namespace std;
LL n,m,ans;
LL arr[2*MAX_N],t[2*MAX_N],sum[2*MAX_N];
char s[MAX_N];
int main(){
	LL i,p,q,x,y;
	scanf("%lld",&n);
	arr[++m]=1;
	scanf("%s",s);
	for(i=2;i<=n;i++){
		if(s[i-2]!=s[i-1])	m+=2;
		arr[m]++;
		y=x;
	}
	for(i=1;i<=m;i++)	sum[i]=sum[i-1]+arr[i];
	p=q=0;
	for(i=1;i<=m;i++){
		if(i<=q)	t[i]=min(t[2*p-i],q-i);
		else	t[i]=0;
		while(i-t[i]-1>=1 && i+t[i]+1<=m && arr[i-t[i]-1]==arr[i+t[i]+1])	t[i]++;
		if(q<i+t[i]){
			p=i;
			q=i+t[i];
		}
		ans+=(!arr[i])*(min(arr[i-t[i]-1],arr[i+t[i]+1])+(sum[i+t[i]]-sum[i-t[i]-1])/2);
	}
	printf("%lld\n",ans);
	return 0;
}
