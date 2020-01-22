#include<bits/stdc++.h>
#define MAX_N 50005
#define MAX_M 200005
#define fi first
#define se second
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
int n,m,k,cnt;
int S[MAX_M],E[MAX_M],Rear[MAX_M],Front[MAX_M];
int in_degree[MAX_N],out_degree[MAX_N];
bool chk[MAX_M];
vector<pii> net[MAX_N],lst[MAX_N];
vector<pii> ans[MAX_N];
bool dfs(int x){
	pii y;
	bool z;
	int l;
	while(net[x].size()){
		y=net[x].back();net[x].pop_back();
		cnt--;
		ans[x].pb(y);
		if(chk[x]){
			l=ans[x].size();
			swap(ans[x][l-2],ans[x][l-1]);
		}
		z=dfs(y.fi);
		if(!z)	chk[x]=true;
	}
	return false;
}
void ans_dfs(int x){
	pii y;
	int z;
	while(ans[x].size()){
		y=ans[x].back();ans[x].pop_back();
		if(y.se){
			z=y.se;
			printf("%d\n",S[z]);
			while(Rear[z]){
				printf("%d\n",E[z]);
				z=Rear[z];
			}
		}else	printf("%d\n",x);
		ans_dfs(y.fi);
	}
}
int main(){
	freopen("input.txt","r",stdin);
	int i,j,x,y,z,l;
	scanf("%d %d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d %d",&S[i],&E[i]);
		in_degree[E[i]]++;out_degree[S[i]]++;
		lst[S[i]].pb(mp(E[i],i));
	}
	for(i=1;i<=n;i++){
		sort(lst[i].begin(),lst[i].end());
		lst[i].erase(unique(lst[i].begin(),lst[i].end()),lst[i].end());
		if(in_degree[i]!=out_degree[i])	return !printf("NIE\n");
		in_degree[i]=out_degree[i]=0;
	}
	scanf("%d",&k);
	for(i=1;i<=k;i++){
		scanf("%d %d",&j,&x);j--;
		l=0;
		while(j--){
			scanf("%d",&y);
			z=lower_bound(lst[x].begin(),lst[x].end(),mp(y,0))-lst[x].begin();
			if(lst[x][z].fi!=y)	return !printf("NIE\n");
			if(l){
				if(Rear[l] && Rear[l]!=lst[x][z].se)	return !printf("NIE\n");
				Rear[l]=lst[x][z].se;
				Front[lst[x][z].se]=l;
			}
			l=lst[x][z].se;
			x=y;
		}
	}
	for(i=1;i<=m;i++){
		if(!Rear[i] && !Front[i]){
			net[S[i]].pb(mp(E[i],0));
			cnt++;
			continue;
		}
		if(chk[i])	continue;
		x=i;
		while(Front[x]){
			if(chk[x])	return !printf("NIE\n");
			chk[x]=true;
			x=Front[x];
		}
		y=x;
		while(Rear[y]){
			chk[y]=true;
			y=Rear[y];
		}
		chk[y]=true;
		net[S[x]].pb(mp(E[y],x));
		cnt++;
	}
	for(i=1;i<=m;i++)	chk[i]=false;
	x=dfs(1);
	for(i=1;i<=n;i++){
		x=ans[i].size();
		for(j=0;j<(x+1)/2;j++)	swap(ans[i][j],ans[i][x-j-1]);
	}
	if(cnt)	return !printf("NIE\n");
	printf("TAK\n");
	ans_dfs(1);
	printf("1\n");
	return 0;
}
