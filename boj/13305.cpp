#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n,cost,ans;
LL L[100005];
int main(){
	freopen("input.txt","r",stdin);
	LL x,i;
	scanf("%lld",&n);
	for(i=0;i<n-1;i++)	scanf("%lld",&L[i]);
	scanf("%lld",&cost);
	ans+=cost*L[0];
	for(i=1;i<n-1;i++){
		scanf("%lld",&x);
		cost=min(cost,x);
		ans+=cost*L[i];
	}
	scanf("%*d");
	printf("%lld\n",ans);
	return 0;
}
