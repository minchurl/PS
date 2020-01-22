#include<bits/stdc++.h>
#define MAX_N 40005
#define LL long long
#define pb push_back
using namespace std;
LL n,m,dst[MAX_N];
LL ma,mb,mc,md;
LL ans;
queue<LL> Q;
vector<LL> net[MAX_N];
void bfs(){
	LL x,y,sz;
	while(!Q.empty()){
		x=Q.front();Q.pop();
		sz=net[x].size();
		while(sz--){
			y=net[x][sz];
			if(dst[y]>dst[x]+1){
				dst[y]=dst[x]+1;
				Q.push(y);
			}
		}
	}
}
LL cost(LL a,LL b,LL c,LL d){
	return (a-1)*a/2+(b-1)*b/2+(c-1)*c/2+(d-1)*d/2+a+a*c+c*d+d*b+b-m;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,x,y;
	scanf("%lld %lld",&n,&m);
	for(i=1;i<=n;i++)	dst[i]=40005;
	for(i=0;i<m;i++){
		scanf("%lld %lld",&x,&y);
		if(x>y)	swap(x,y);
		net[x].pb(y);net[y].pb(x);
	}
	dst[1]=0;
	Q.push(1);
	bfs();
	ma=mc=0;
	for(i=1;i<=n;i++){
		if(dst[i]==1)	ma++;
		if(dst[i]==2)	mc++;
		dst[i]=40005;
	}
	dst[2]=0;
	Q.push(2);
	bfs();
	mb=md=0;
	for(i=1;i<=n;i++){
		if(dst[i]==1)	mb++;
		if(dst[i]==2)	md++;
		dst[i]=40005;
	}
	//a
	x=n-2-mc-mb-md;
	ans=max(ans,cost(x,mb,mc,md));
	//b
	x=n-2-ma-mc-md;
	ans=max(ans,cost(ma,x,mc,md));
	//c
	x=n-2-ma-mb-md;
	ans=max(ans,cost(ma,mb,x,md));
	//d
	x=n-2-ma-mb-mc;
	ans=max(ans,cost(ma,mb,mc,x));
	printf("%lld\n",ans);
	return 0;
}
