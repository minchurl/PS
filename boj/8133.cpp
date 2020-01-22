#include<bits/stdc++.h>
#define MAX_N 2005
#define fi first
#define se second
#define mp make_pair
#define abs(x) ((x)>0?(x):(-(x)))
#define get_val(i,x) (arr[(i)].fi+abs((x)-arr[(i)].se))
#define inf (1LL<<40)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pil;
LL n,m,sum[MAX_N],t[MAX_N][MAX_N],ans,an;
pil arr[MAX_N];
int main(){
	freopen("input.txt","r",stdin);
	LL x,i,j,k,s;
	scanf("%lld %lld",&m,&n);
	m++;
	ans=inf;
	for(i=1;i<=n;i++){
		scanf("%lld",&x);
		sum[i]=sum[i-1]+x+1;
	}
	for(i=1;i<=n;i++){
		if(sum[i]>m)	t[i][0]=inf;
		else{
			t[i][0]=0;
			if(i==n)	ans=min(ans,0LL);
		}
	}
	for(j=1;j<n;j++){
		an=0;
		arr[an++]=mp(t[j][j-1],2*sum[j]-sum[j-1]);
		for(k=j-2;k>=0;k--){
			if(sum[j]-sum[k]>m)	break;
			if(get_val(an-1,2*sum[j]-sum[k])<=t[j][k])	continue;
			arr[an++]=mp(t[j][k],2*sum[j]-sum[k]);
		}
		s=0;
		for(i=j+1;i<=n;i++){
			t[i][j]=inf;
			if(sum[i]-sum[j]>m)	continue;
			while(s<an-1 && get_val(s,sum[i])>=get_val(s+1,sum[i]))	s++;
			t[i][j]=min(t[i][j],get_val(s,sum[i]));
			if(i==n)	ans=min(ans,t[i][j]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
