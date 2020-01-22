#include<bits/stdc++.h>
#define MAX_N 505
#define inf 1000000000
int n,TC;
int t[MAX_N][MAX_N],tt[MAX_N][MAX_N],sum[MAX_N];
int main(){
	freopen("input.txt","r",stdin);
	int x,i,j,k,s,e;
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&n);
		for(i=1;i<=n;i++){
			scanf("%d",&x);
			sum[i]=sum[i-1]+x;
		}
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++)	t[i][j]=inf;
			t[i][i]=0;
			tt[i][i]=i;
		}
		for(k=2;k<=n;k++){
			for(s=1;s<=n-k+1;s++){
				e=s+k-1;
				for(i=tt[s][e-1];i<=tt[s+1][e];i++){
					if(t[s][e]>=t[s][i]+t[i+1][e]+sum[e]-sum[s-1]){
						t[s][e]=t[s][i]+t[i+1][e]+sum[e]-sum[s-1];
						tt[s][e]=i;
					}
				}
			}
		}
		printf("%d\n",t[1][n]);
	}
	return 0;
}
