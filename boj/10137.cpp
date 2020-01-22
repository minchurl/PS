#include<bits/stdc++.h>
#define MAX_N 200005
using namespace std;
typedef long long LL;
int main(){
	LL t,x,cnt=1,s,n,i,y;
	scanf("%lld %lld",&n,&s);
	scanf("%lld",&x);
	t=x;
	for(i=2;i<=n;i++){
		scanf("%lld",&x);
		y=max(t+1,x);
		if(y-t<=2*s-1){
			t=y;
			cnt++;
			continue;
		}
		t+=2*s+cnt-1;
		t=max(t,x);
		cnt=1;
	}
	t+=2*s+cnt-1;
	printf("%lld\n",t);
	return 0;
}
