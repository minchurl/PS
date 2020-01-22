#include<bits/stdc++.h>
#define MAX_N 100005
#define inf (1LL<<60)
#define pb push_back
using namespace std;
typedef long long LL;
LL n,vc;
LL num[MAX_N],chk[MAX_N],cpa[MAX_N],pa[20][MAX_N],dep[MAX_N],dst[MAX_N];
vector<LL> net[MAX_N];
void make_num(LL x){
	num[x]=1;
	chk[x]=vc;
	for(LL y:net[x]){
		if(chk[y]==-1 || chk[y]==vc)	continue;
		make_num(y);
		num[x]+=num[y];
	}
}
LL find_cen(LL x,LL z){
	chk[x]=vc;
	for(LL y:net[x]){
		if(chk[y]==-1 || chk[y]==vc || num[y]<=z/2)	continue;
		return find_cen(y,z);
	}
	return x;
}
LL make_cen(LL x){
	vc++;make_num(x);
	vc++;LL cen=find_cen(x,num[x]);
	chk[cen]=-1;
	for(LL y:net[cen]){
		if(chk[y]==-1)	continue;
		cpa[make_cen(y)]=cen;
	}
	return cen;
}
void dfs(LL x){
	chk[x]=vc;
	for(LL y:net[x]){
		if(chk[y]==vc)	continue;
		pa[0][y]=x;
		dep[y]=dep[x]+1;
		dfs(y);
	}
}
void make_pa(){for(LL i=1;i<=16;i++)for(LL j=1;j<=n;j++)pa[i][j]=pa[i-1][pa[i-1][j]];}
LL lca(LL x,LL y){
	LL i;
	if(dep[x]>dep[y])	swap(x,y);
	for(i=16;i>=0;i--){
		if(dep[x]<=dep[pa[i][y]])	y=pa[i][y];
	}
	if(x==y)	return x;
	for(i=16;i>=0;i--){
		if(pa[i][x]==pa[i][y])	continue;
		x=pa[i][x];y=pa[i][y];
	}
	return pa[0][x];
}
void update(LL x){
	LL y=x;
	while(y){
		dst[y]=min(dst[y],dep[x]+dep[y]-2*dep[lca(x,y)]);
		y=cpa[y];
	}
}
LL read(LL x){
	LL y=x,minx=inf;
	while(y){
		minx=min(minx,dst[y]+dep[x]+dep[y]-2*dep[lca(x,y)]);
		y=cpa[y];
	}
	return (minx==inf)?-1:minx;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,x,q;
	scanf("%lld %lld",&n,&q);
	dst[1]=inf;
	for(i=2;i<=n;i++){
		scanf("%lld",&x);
		net[x].pb(i);net[i].pb(x);
		dst[i]=inf;
	}
	dep[1]=1;
	vc++;dfs(1);
	make_pa();
	x=make_cen(1);
	while(q--){
		scanf("%lld %lld",&i,&x);
		if(i==1)	update(x);
		else	printf("%lld\n",read(x));
	}
	return 0;
}
