#include<bits/stdc++.h>
#define MAX_N 1505
#define LL long long
using namespace std;
LL t[MAX_N][4*MAX_N],dp[MAX_N][MAX_N],sy[MAX_N],ey[MAX_N];
LL n,ans;
LL read(LL X,LL x){LL y=0;for(;x>0;x-=(x&-x))	y+=t[X][x];return y;}
void update(LL X,LL x,LL y){for(;x<=n;x+=(x&-x))	t[X][x]+=y;}
LL get_val(LL x,LL y){
	if(x==0)	return 0;
	return read(x,y)+dp[x][y];
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,j,x,y,X,d;
	char in[5];
	scanf("%lld",&n);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			scanf("%lld",&x);
			dp[i][j]=max(dp[i-1][j],dp[i][j-1])+x;
			ans+=dp[i][j];
		}
	}
	printf("%lld\n",ans);
	for(i=1;i<=n;i++){
		scanf("%s %lld %lld",in,&x,&y);
		d=(in[0]=='U')?1:-1;
		X=x;
		sy[x]=ey[x]=y;
		for(;x<=n;x++){
			if(X!=x){sy[x]=sy[x-1];ey[x]=ey[x-1];}
			while(X!=x && sy[x]<=ey[x] && max(get_val(x,sy[x]-1),get_val(x-1,sy[x]))+d!=max(get_val(x,sy[x]-1),get_val(x-1,sy[x])+d))	sy[x]++;
			if(sy[x]>ey[x])	break;
			while(ey[x]<n && max(get_val(x,ey[x]),get_val(x-1,ey[x]+1))+d==max(get_val(x,ey[x])+d,get_val(x-1,ey[x]+1)))	ey[x]++;
		}
		for(;X<x;X++){
			update(X,sy[X],d);
			update(X,ey[X]+1,-d);
			ans+=(ey[X]-sy[X]+1)*d;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
