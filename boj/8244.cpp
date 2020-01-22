#include<bits/stdc++.h>
#define MAX_N 5005
#define pb push_back
#define inf 30000
using namespace std;
int n,m,q;
short min_D[MAX_N][MAX_N][2];
short dst[MAX_N];
vector<short> net[MAX_N];
queue<int> Q;
bool chk[MAX_N];
void spfa(){
	int x,y,sz;
	while(!Q.empty()){
		x=Q.front();Q.pop();
		chk[x]=false;
		sz=net[x].size();
		while(sz--){
			y=net[x][sz];
			if(dst[y]>dst[x]+1){
				dst[y]=dst[x]+1;
				if(chk[y])	continue;
				chk[y]=true;
				Q.push(y);
			}
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	int i,j,x,y,sz;
	scanf("%d %d %d",&n,&m,&q);
	for(i=0;i<m;i++){
		scanf("%d %d",&x,&y);
		net[x].pb(y);net[y].pb(x);
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++)	dst[j]=min_D[i][j][0]=min_D[i][j][1]=inf;
		dst[i]=0;
		chk[i]=true;
		Q.push(i);
		spfa();
		for(j=1;j<=n;j++){
			min_D[i][j][dst[j]%2]=dst[j];
			sz=net[j].size();
			while(sz--){
				x=net[j][sz];
				if(dst[x]!=inf && dst[x]==dst[j])	chk[x]=chk[j]=true;
			}
		}
		for(j=1;j<=n;j++){
			if(chk[j]){
				dst[j]++;
				Q.push(j);
			}else	dst[j]=inf;
		}
		spfa();
		for(j=1;j<=n;j++)	min_D[i][j][dst[j]%2]=min(min_D[i][j][dst[j]%2],dst[j]);
	}
	while(q--){
		scanf("%d %d %d",&x,&y,&i);
		if((int)min_D[x][y][i%2]==0 && x==y && net[x].size()==0){
			printf("%s\n",i?"NIE":"TAK");
			continue;
		}
		printf("%s\n",((int)min_D[x][y][i%2]<=i && min_D[x][y][i%2]!=inf)?"TAK":"NIE");
	}
	return 0;
}
