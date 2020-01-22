#include<bits/stdc++.h>
#define MAX_N 5005
#define inf (1LL<<60)
using namespace std;
typedef long long LL;
LL n,t[MAX_N][MAX_N],tt[MAX_N][MAX_N],sum[MAX_N];
int main(){
	LL TC,i,j,s,e,x;
	scanf("%lld",&TC);
	while(TC--){
		scanf("%lld",&n);
		for(i=1;i<=n;i++){
			scanf("%lld",&x);
			sum[i]=sum[i-1]+x;
			tt[i][i]=i;
		}
		for(i=2;i<=n;i++){
			for(s=1;s<=n-i+1;s++){
				e=s+i-1;
				t[s][e]=inf;
				for(j=max(s+1,tt[s][e-1]);j<=min(e,tt[s+1][e]);j++){
					if(t[s][e]>t[s][j-1]+t[j][e]){
						t[s][e]=t[s][j-1]+t[j][e];
						tt[s][e]=j;
					}
				}
				t[s][e]+=sum[e]-sum[s-1];
			}
		}
		printf("%lld\n",t[1][n]);
	}
	return 0;
}
