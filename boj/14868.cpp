#include<bits/stdc++.h>
#define MAX_N 2005
#define MAX_M 100005
#define inf 0x3fffffff
using namespace std;
struct node{
	int x,y;
};
int n,k,h[MAX_M],pa[MAX_M];
int t[MAX_N][MAX_N],num[MAX_N][MAX_N],ans;
int Next[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
queue<node> Q;
int find_pa(int x){
	while(pa[x])	x=pa[x];
	return x;
}
void connect(int x,int y,int z){
	int px,py;
	//printf("%d %d : %d\n",x,y,z);
	px=find_pa(x);
	py=find_pa(y);
	if(px==py)	return;
	ans=max(ans,z);
	if(h[px]==h[py])	h[px]++;
	if(h[px]>=h[py])	pa[py]=px;
	else	pa[px]=py;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,j,x,y;
	node p,q,r;
	scanf("%d %d",&n,&k);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++)	t[i][j]=inf;
	}
	for(i=0;i<k;i++){
		scanf("%d %d",&p.x,&p.y);
		Q.push(p);
		t[p.x][p.y]=0;
		h[i+1]=1;pa[i+1]=0;
		if(num[p.x][p.y])	connect(num[p.x][p.y],i+1,0);
		for(j=0;j<4;j++){
			q.x=p.x+Next[j][0];
			q.y=p.y+Next[j][1];
			if(num[q.x][q.y])	connect(i+1,num[q.x][q.y],0);
		}
		num[p.x][p.y]=i+1;
	}
	while(!Q.empty()){
		p=Q.front();Q.pop();
		for(i=0;i<4;i++){
			q.x=p.x+Next[i][0];
			q.y=p.y+Next[i][1];
			if(num[q.x][q.y])	connect(num[p.x][p.y],num[q.x][q.y],t[p.x][p.y]+1);
			if(t[q.x][q.y]>t[p.x][p.y]+1){
				t[q.x][q.y]=t[p.x][p.y]+1;
				num[q.x][q.y]=num[p.x][p.y];
				Q.push(q);
				for(j=0;j<4;j++){
					r.x=q.x+Next[j][0];
					r.y=q.y+Next[j][1];
					if(num[r.x][r.y])	connect(num[q.x][q.y],num[r.x][r.y],t[q.x][q.y]);
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
