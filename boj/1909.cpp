#include<bits/stdc++.h>
#define sq(x) ((x)*(x))
#define MAX_N 1005
#define inf (1LL<<60)
using namespace std;
typedef long long LL;
struct point{
	LL x,y;
}W,S,E;
struct node{
	LL x,y,dx,dy;
};
bool operator < (const node x,const node y){
	return (sq(x.dx)+sq(x.dy))>(sq(y.dx)+sq(y.dy));
};
LL n;
LL chk[MAX_N][MAX_N],dst[MAX_N][MAX_N];
LL dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
priority_queue<node,vector<node>> pq;
queue<point> Q;
bool is_ok(LL L){
	LL i,j;
	point p,q;
	if(dst[S.x][S.y]<L)	return false;
	for(i=1;i<=W.x;i++){
		for(j=1;j<=W.y;j++)	chk[i][j]=false;
	}
	chk[S.x][S.y]=true;
	Q.push(S);
	while(!Q.empty()){
		p=Q.front();Q.pop();
		for(i=0;i<4;i++){
			q.x=p.x+dx[i];
			q.y=p.y+dy[i];
			if(chk[q.x][q.y] || dst[q.x][q.y]<L || q.x<1 || q.y<1 || q.x>W.x || q.y>W.y)	continue;
			chk[q.x][q.y]=true;
			Q.push(q);
		}
	}
	return chk[E.x][E.y];
}
LL bin(){
	LL st,ed,mid;
	st=1;
	ed=sq(W.x-1)+sq(W.y-1);
	while(st<=ed){
		mid=(st+ed)>>1;
		if(is_ok(mid)){
			if(!is_ok(mid+1))	return mid;
			st=mid+1;
		}else{
			if(is_ok(mid-1))	return mid-1;
			ed=mid-1;
		}
	}
	return 0;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,j,x,y;
	node p;
	scanf("%lld %lld",&W.x,&W.y);
	for(i=1;i<=W.x;i++){
		for(j=1;j<=W.y;j++)	dst[i][j]=inf;
	}
	scanf("%lld %lld %lld %lld",&S.x,&S.y,&E.x,&E.y);
	scanf("%lld",&n);
	for(i=1;i<=n;i++){
		scanf("%lld %lld",&x,&y);
		pq.push({x,y,0,0});
	}
	while(!pq.empty()){
		p=pq.top();pq.pop();
		if(p.x>W.x || p.y>W.y || !p.x || !p.y)	continue;
		//if(sq(p.dx)+sq(p.dy)>dst[p.x][p.y])	continue;
		dst[p.x][p.y]=sq(p.dx)+sq(p.dy);
		for(i=0;i<4;i++)	pq.push({p.x+dx[i],p.y+dy[i],p.dx+(i%2?0:1),p.dy+(i%2?1:0)});
	}
	printf("%lld\n",bin());
	return 0;
}
