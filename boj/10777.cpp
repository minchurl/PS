#include<bits/stdc++.h>
#define MAX_N 3005
#define MAX_M 105
using namespace std;
int n,m,t[MAX_N][MAX_M][MAX_M];
int a[MAX_N],b[MAX_M];
int ans;
int main(){
	freopen("input.txt","r",stdin);
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++)	scanf("%d",&a[i]);
	scanf("%d",&m);
	for(i=1;i<=m;i++)	scanf("%d",&b[i]);
	sort(b+1,b+m+1);
	for(i=1;i<=n+1;i++){
		for(j=0;j<=m;j++){
			for(k=0;k<=m-j;k++){
				t[i][j][k]=t[i-1][j][k];
				if(k)	t[i][j][k]=max(t[i][j][k],t[i][j][k-1]);
				if(j)	t[i][j][k]=max(t[i][j][k],t[i-1][j-1][k]+b[m-j+1]);
				if(k)	t[i][j][k]=max(t[i][j][k],t[i-1][j][k-1]+a[i]);
				if(j && k)	t[i][j][k]=max(t[i][j][k],t[i][j-1][k-1]+b[m-j+1]);
				if(i>1)	t[i][j][k]=max(t[i][j][k],t[i-2][j][k]+a[i-1]);
				ans=max(ans,t[i][j][k]);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
