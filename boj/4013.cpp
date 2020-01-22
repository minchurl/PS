#include<bits/stdc++.h>
#define pb push_back
#define MAX_N 500005
using namespace std;
int n,m;
int chk[MAX_N],num[MAX_N],cc[MAX_N],rc[MAX_N],degree[MAX_N],cost[MAX_N],dst[MAX_N];
vector<int> net[MAX_N],bnet[MAX_N],nnet[MAX_N];
queue<int> Q;
void dfs(int x){
	int y,sz=net[x].size();
	chk[x]=true;
	while(sz--){
		y=net[x][sz];
		if(chk[y])	continue;
		dfs(y);
	}
	cc[++m]=x;
}
void back_dfs(int x){
	int y,sz=bnet[x].size();
	chk[x]=false;
	num[x]=m;
	while(sz--){
		y=bnet[x][sz];
		if(!chk[y])	continue;
		back_dfs(y);
	}
}
void dfs1(int x){
	int y,sz=nnet[x].size();
	chk[x]=true;
	while(sz--){
		y=nnet[x][sz];
		degree[y]++;
		if(chk[y])	continue;
		dfs1(y);
	}
}
int get_ans(int x){
	int ans=0;
	Q.push(x);
	while(!Q.empty()){
		int p=Q.front();Q.pop();
		int sz=nnet[p].size();
		dst[p]+=cost[p];
		if(rc[p])	ans=max(ans,dst[p]);
		while(sz--){
			int y=nnet[p][sz];
			degree[y]--;
			dst[y]=max(dst[y],dst[p]);
			if(!degree[y])	Q.push(y);
		}
	}
	return ans;
}
void make_scc(){
	int i;
	for(i=1;i<=n;i++){
		if(!chk[i])	dfs(i);
	}
	m=0;
	for(i=n;i>=1;i--){
		if(chk[cc[i]]){
			m++;
			back_dfs(cc[i]);
		}
	}
	for(i=1;i<=n;i++){
		int sz=net[i].size();
		while(sz--){
			int y=net[i][sz];
			if(num[i]==num[y])	continue;
			nnet[num[i]].pb(num[y]);
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y,s,p;
	scanf("%d %d",&n,&m);
	while(m--){
		scanf("%d %d",&x,&y);
		net[x].pb(y);
		bnet[y].pb(x);
	}
	make_scc();
	for(i=1;i<=n;i++){
		scanf("%d",&x);
		cost[num[i]]+=x;
	}
	scanf("%d %d",&s,&p);
	while(p--){
		scanf("%d",&x);
		rc[num[x]]=true;
	}
	dfs1(num[s]);
	printf("%d\n",get_ans(num[s]));
	return 0;
}
