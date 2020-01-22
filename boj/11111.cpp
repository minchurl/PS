#include<bits/stdc++.h>
#define MAX_N 55
#define get_num(x,y) (M*((x)-1)+(y))
#define pb push_back
#define inf 0x3fffffff
using namespace std;
struct node{
	int e,cap,val,inv;
};
int N,M,sink,ans;
int dst[MAX_N*MAX_N],cap[MAX_N*MAX_N],from[MAX_N*MAX_N];
char in_s[MAX_N][MAX_N];
bool chk[MAX_N*MAX_N];
vector<node> net[MAX_N*MAX_N];
int cost[6][6]={{10,8,7,5,1}
			   ,{8,6,4,3,1}
			   ,{7,4,3,2,1}
			   ,{5,3,2,2,1}
			   ,{1,1,1,1,0}};
int dx[5]={-1,1,0,0},dy[5]={0,0,-1,1};
queue<int> Q;
void SPFA(){
	int i,x;
	for(i=0;i<=sink;i++){
		chk[i]=false;
		cap[i]=0;
		dst[i]=-inf;
	}
	Q.push(0);chk[0]=true;
	cap[0]=1;
	dst[0]=0;
	while(!Q.empty()){
		x=Q.front();Q.pop();
		chk[x]=false;
		for(node y:net[x]){
			if(!y.cap || dst[y.e]>=dst[x]+y.val)	continue;
			dst[y.e]=dst[x]+y.val;
			cap[y.e]=min(cap[x],y.cap);
			from[y.e]=y.inv;
			if(!chk[y.e])	Q.push(y.e);
			chk[y.e]=true;
		}
	}
	if(dst[sink]>0)	ans+=dst[sink];
}
void net_update(){
	int e=sink,sz,szz,x;
	while(e){
		sz=from[e];
		x=net[e][sz].e;
		szz=net[e][sz].inv;
		net[x][szz].cap-=cap[sink];
		net[e][sz].cap+=cap[sink];
		e=x;
	}
}
int main(){	
	freopen("input.txt","r",stdin);
	int i,j,k,x,y,z;
	scanf("%d %d",&N,&M);
	for(i=1;i<=N;i++)	scanf("%s",in_s[i]+1);
	for(i=1;i<=N;i++){
		for(j=1;j<=M;j++)	in_s[i][j]=(in_s[i][j]=='F')?'E':in_s[i][j];
	}
	sink=N*M+1;
	for(i=1;i<=N;i++){
		for(j=1;j<=M;j++){
			x=get_num(i,j);
			if((i+j)%2){
				net[x].pb({sink,1,0,(int)net[sink].size()});
				net[sink].pb({x,0,0,(int)net[x].size()-1});
				continue;
			}
			net[0].pb({x,1,0,(int)net[x].size()});
			net[x].pb({0,0,0,(int)net[0].size()-1});
			for(k=0;k<4;k++){
				x=i+dx[k];
				y=j+dy[k];
				if(x<1 || x>N || y<1 || y>M)	continue;
				z=cost[in_s[i][j]-'A'][in_s[x][y]-'A'];
				y=get_num(x,y);
				x=get_num(i,j);
				net[x].pb({y,1,z,(int)net[y].size()});
				net[y].pb({x,0,-z,(int)net[x].size()-1});
			}
		}
	}
	while(1){
		SPFA();
		if(dst[sink]<0)	break;
		net_update();
	}
	printf("%d\n",ans);
	return 0;
}
