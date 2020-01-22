#include<bits/stdc++.h>
//#include<inttypes.h>//__int64,__int128..
#define MAX_N 105
#define MAX_K 1005
//vector&pair
#define pb push_back
#define mp make_pair
//math
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))//Regardless of type
//for pair
#define fi first
#define se second
//infinit
#define inf (1LL<<60)
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
//MOD
#define MOD 1000000007LL*/
using namespace std;
//type
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef long double LD;
struct im{
	LL b,s;
}pd[MAX_N][MAX_K];
LL n,m,c;
LL net[MAX_N][MAX_N],dst[MAX_N][MAX_N],rev[MAX_N][MAX_N];
bool is_ok(LL K){
	LL i,j,k;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(net[i][j]==inf)	dst[i][j]=inf;
			else	dst[i][j]=K*net[i][j]-rev[i][j];
		}
	}
	for(k=1;k<=n;k++){
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++){
				dst[i][j]=min(dst[i][j],dst[i][k]+dst[k][j]);
			}
		}
	}
	for(i=1;i<=n;i++){
		if(dst[i][i]<=0)	return true;
	}
	return false;
}
LL bin(){
	LL s,e,mid;
	bool x;
	s=1;
	e=1000000000;
	while(s<=e){
		mid=(s+e)>>1;
		x=is_ok(mid);
		if(x){
			if(!is_ok(mid+1))	return mid;
			s=mid+1;
		}else{
			if(is_ok(mid-1))	return mid-1;
			e=mid-1;
		}
	}
	return 0;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,j,k,s,e;
	scanf("%lld %lld %lld",&n,&m,&c);
	for(i=1;i<=n;i++){
		for(j=1;j<=c;j++){
			scanf("%lld %lld",&pd[i][j].b,&pd[i][j].s);
			if(pd[i][j].b==-1)	pd[i][j].b=inf;
			if(pd[i][j].s==-1)	pd[i][j].s=-inf;
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			net[i][j]=inf;
			for(k=1;k<=c;k++)	rev[i][j]=max(rev[i][j],pd[j][k].s-pd[i][k].b);
		}
	}
	for(i=1;i<=m;i++){scanf("%lld %lld",&s,&e);scanf("%lld",&net[s][e]);}
	//Floyd-Warshall
	for(k=1;k<=n;k++)for(i=1;i<=n;i++)for(j=1;j<=n;j++){
		net[i][j]=min(net[i][j],net[i][k]+net[k][j]);
	}	
	printf("%lld\n",bin());
	return 0;
}
