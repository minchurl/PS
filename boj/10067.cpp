#include<bits/stdc++.h>
#define MAX_N 100005
#define sq(x) ((x)*(x))
using namespace std;
typedef long long LL;
struct node{
	LL a,b,idx;
}fc[MAX_N],nfc[MAX_N];
LL n,k,sum[MAX_N],dp[MAX_N];
LL s,e,ns,ne,ans,anss[MAX_N],ansn;
int from[205][MAX_N];
bool is_ok(node x,node y,node z){return (x.a-y.a)*(z.b-x.b)>(x.a-z.a)*(y.b-x.b);}
int main(){
	freopen("input.txt","r",stdin);
	LL i,j,x,F;
	node p;
	scanf("%lld %lld",&n,&k);
	for(i=1;i<=n;i++){
		scanf("%lld",&x);
		sum[i]=sum[i-1]+x;
	}
	s=e=0;
	ans=-1;
	for(i=1;i<=n;i++){
		dp[i]=(sum[i])*(sum[n]-sum[i]);
		if(1==k && ans<dp[i] && i!=n){
			ans=dp[i];
			F=i;
		}
		p.a=sum[i];
		p.b=dp[i]-sum[n]*sum[i];
		p.idx=i;
		from[1][i]=0;
		while(e-s>1 && !is_ok(fc[e-2],fc[e-1],p))	e--;
		fc[e++]=p;
	}
	for(i=2;i<=k;i++){	
		ns=ne=0;
		for(j=1;j<=n;j++)	dp[j]=0;
		for(j=i;j<=n;j++){
			while(e-s>1 && fc[s+1].idx<j && fc[s].a*sum[j]+fc[s].b<=fc[s+1].a*sum[j]+fc[s+1].b)	s++;
			dp[j]=fc[s].a*sum[j]+fc[s].b-sq(sum[j])+sum[n]*sum[j];
			if(i==k && ans<dp[j] && j!=n){
				ans=dp[j];
				F=j;
			}
			from[i][j]=fc[s].idx;
			p.a=sum[j];
			p.b=dp[j]-sum[n]*sum[j];
			p.idx=j;
			while(ne-ns>1 && !is_ok(nfc[ne-2],nfc[ne-1],p))	ne--;
			nfc[ne++]=p;
		}
		s=ns;
		e=ne;
		for(j=ns;j<ne;j++)	fc[j]=nfc[j];
	}
	while(F){
		anss[ansn++]=F;
		F=from[k--][F];
	}
	printf("%lld\n",ans);
	for(i=ansn-1;i>=0;i--)	printf("%lld ",anss[i]);
	printf("\n");
	return 0;
}
