#include<bits/stdc++.h>
#define MAX_N 1000005
#define fi first
#define se second
#define sq(x) ((x)*(x))
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pil;
pil fc[MAX_N];
LL n,a,b,c,t[MAX_N],sum[MAX_N],s,e;
bool is_ok(pil x,pil y,pil z){return (x.fi-y.fi)*(z.se-x.se)>(x.fi-z.fi)*(y.se-x.se);}
int main(){
	freopen("input.txt","r",stdin);
	LL i,x;
	pil p;
	scanf("%lld",&n);
	scanf("%lld %lld %lld",&a,&b,&c);
	s=e=0;
	for(i=1;i<=n;i++){
		scanf("%lld",&x);
		sum[i]=sum[i-1]+x;
		while(e-s>1 && fc[s].fi*sum[i]+fc[s].se<=fc[s+1].fi*sum[i]+fc[s+1].se)	s++;
		if(e-s)	t[i]=max(fc[s].fi*sum[i]+fc[s].se,0LL);
		t[i]+=a*sq(sum[i])+b*sum[i]+c;
		p.fi=-2*a*sum[i];
		p.se=a*sq(sum[i])-b*sum[i]+t[i];
		while(e-s>1 && !is_ok(fc[e-2],fc[e-1],p))	e--;
		fc[e++]=p;
	}
	printf("%lld\n",t[n]);
	return 0;
}
