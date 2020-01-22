#include<bits/stdc++.h>
#include<inttypes.h>//__int64,__int128..
#define MAX_N 505
//vector&pair
#define pb push_back
#define mp make_pair
//math
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))//Regardless of type
//pair
#define fi first
#define se second
//infinit
#define LL_inf (1LL<<60)
#define full_inf 0x7fffffff
#define half_inf 0x3ffffff1
#define inf 0x3ffffff0
//MOD
#define MOD 1000000007LL
using namespace std;
//type
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<int,pii> p_pq;
typedef long double LD;
priority_queue<p_pq> pq;
int n,m,cost[MAX_N][MAX_N],dst[MAX_N][MAX_N];
int dx[4]={1,1,-1,-1},dy[4]={1,-1,1,-1};
int idx[4]={0,0,-1,-1},idy[4]={0,-1,0,-1};
char in_s[MAX_N];
bool out_of(p_pq p){return (p.se.fi>=0 && p.se.fi<=n)&(p.se.se>=0 && p.se.se<=m);}
void dijkstra(){
	pq.push(mp(0,mp(0,0)));
	dst[0][0]=0;
	while(!pq.empty()){
		p_pq p=pq.top();pq.pop();
		if(-p.fi!=dst[p.se.fi][p.se.se])	continue;
//		printf("%d %d : %d\n",p.se.fi,p.se.se,-p.fi);
		for(int i=0;i<4;i++){
			p_pq q=mp(p.fi,mp(p.se.fi+dx[i],p.se.se+dy[i]));
			if(!out_of(q))	continue;
			q.fi-=cost[p.se.fi+idx[i]][p.se.se+idy[i]];
			//printf("%d %d -> %d %d : %d %d : %d : %d\n",p.se.fi,p.se.se,q.se.fi,q.se.se,p.se.fi+idx[i],p.se.se+idy[i],cost[p.se.fi+idx[i]][p.se.se+idy[i]],q.fi);
			if(dst[q.se.fi][q.se.se]<=-q.fi)	continue;
			dst[q.se.fi][q.se.se]=-q.fi;
			pq.push(q);
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	int i,j;
	scanf("%d %d",&n,&m);
	if(abs(n-m)%2)	return !printf("NO SOLUTION\n");
	for(i=0;i<n;i++){
		scanf("%s",in_s);
		for(j=0;j<m;j++)	cost[i][j]=((i+j)&1)^(!(in_s[j]-'/'));
/*		for(j=0;j<m;j++)	printf("%d ",cost[i][j]);
		printf("\n");*/
	}
	for(i=0;i<=n;i++)	for(j=0;j<=m;j++)	dst[i][j]=inf;
	dijkstra();
	printf("%d\n",dst[n][m]);
	return 0;
}
