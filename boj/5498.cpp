#include<bits/stdc++.h>
#define MAX_N 10005
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define LL_inf (1LL<<60)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
LL n,S,ans=0;
LL sum_F[MAX_N],sum_T[MAX_N];
LL t[1005][MAX_N];
void do_dp(LL z,LL l,LL r,LL s,LL e){
	if(s>e)	return;
	LL mid=(s+e)/2;
	LL i,x,y;
	x=LL_inf;
	y=min(r,mid);
	for(i=min(r,mid);i>=l;i--){
		if(x>t[z-1][i-1]+(z*S+sum_T[mid])*(sum_F[mid]-sum_F[i-1])){
			x=t[z-1][i-1]+(z*S+sum_T[mid])*(sum_F[mid]-sum_F[i-1]);
			y=i;
		}
	}
	t[z][mid]=x;
	do_dp(z,l,y,s,mid-1);
	do_dp(z,y,r,mid+1,e);
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,j;
	scanf("%lld",&n);
	scanf("%lld",&S);
	for(i=1;i<=n;i++){
		scanf("%lld",&j);
		sum_T[i]=sum_T[i-1]+j;
		scanf("%lld",&j);
		sum_F[i]=sum_F[i-1]+j;
		t[0][i]=LL_inf;
	}
	ans=LL_inf;
	for(i=1;i<=n;i++){
		do_dp(i,1,n,1,n);
		for(j=1;j<=n;j++){
			if(t[i][j]<t[i-1][j])	break;
		}
		ans=min(ans,t[i][n]);
		if(j==n+1)	break;
	}
	printf("%lld\n",ans);
	return 0;
}
