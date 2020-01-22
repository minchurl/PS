#include<bits/stdc++.h>
#define MAX_N 505
#define pb push_back
#define inf 0x3fffffff
using namespace std;
int n,sum,C[MAX_N][MAX_N];
int level[MAX_N];
int S[MAX_N];
queue<int> Q;
bool make_level(){
	memset(level,0,sizeof(level));
	level[0]=1;
	Q.push(0);
	while(Q.size()){
		int x=Q.front();Q.pop();
		for(int i=0;i<=n+1;i++){
			if(level[i] || !C[x][i])	continue;
			level[i]=level[x]+1;
			Q.push(i);
		}
	}
	return level[n+1]!=0;
}
int dfs(int h,int cap){
	if(h==n+1)	return cap;
	for(int i=S[h];i<=n+1;i++){
		S[h]=i;
		if(level[h]>=level[i] || !C[h][i])	continue;
		int c=dfs(i,min(cap,C[h][i]));
		if(c){
			C[h][i]-=c;
			C[i][h]+=c;
			return c;
		}
	}
	return 0;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,j,x;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&x);
		if(x==1)	C[0][i]=inf;
		if(x==2)	C[i][n+1]=inf;
	}
	for(i=1;i<=n;i++)	for(j=1;j<=n;j++)	scanf("%d",&C[i][j]);
	while(make_level()){
		int c=0;
		for(i=0;i<=n+1;i++)	S[i]=0;
		do{
			c=dfs(0,inf);
			sum+=c;
		}while(c);
	}
	printf("%d\n",sum);
	for(i=1;i<=n;i++)	if(level[i])	printf("%d ",i);
	printf("\n");
	for(i=1;i<=n;i++)	if(!level[i])	printf("%d ",i);
	printf("\n");
	return 0;
}
