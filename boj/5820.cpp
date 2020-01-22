#include<bits/stdc++.h>
#define MAX_N 200005
#define MAX_K 1000005
#define fi first
#define se second
#define inf 0x3fffffff
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define reset(V) (V).clear();(V).resize(0);
using namespace std;
typedef pair<int,int> pii;
int n,m,k,ans,vn;
int num[MAX_N],vis[MAX_N];
pii chk[MAX_K];
vector<pii> adj[MAX_N],lst;
int make_num(int u){
	vis[u] = vn;
	num[u] = 1;
	for(pii v:adj[u]){
		if(vis[v.fi] == -1 || vis[v.fi] == vn)	continue;
		num[u]+=make_num(v.fi);
	}
	return num[u];
}
int find_cen(int u,int x){
	vis[u] = vn;
	for(pii v:adj[u]){
		if(vis[v.fi] == -1 || vis[v.fi] == vn)	continue;
		if(num[v.fi] >= x/2)	return find_cen(v.fi,x);
	}
	return u;
}
void dfs(int u,int l,int cnt){
	if(l > k)	return;
	vis[u] = vn;
	if(chk[k - l].se == vn){
		ans = min(ans, chk[k-l].fi + cnt);
	}
	lst.eb(l,cnt);
	for(pii v:adj[u]){
		if(vis[v.fi] == vn || vis[v.fi] == -1)	continue;
		dfs(v.fi,l+v.se,cnt+1);
	}
}
void solve(int u){
	vn++;make_num(u);
	vn++;int cen = find_cen(u,num[u]);
	vis[cen] = -1;
	vn++;chk[0].se = vn;
	for(pii v:adj[cen]){
		if(vis[v.fi] == -1)	continue;
		dfs(v.fi,v.se,1);
		for(pii x:lst){
			if(chk[x.fi].se != vn)	chk[x.fi].fi = inf;
			chk[x.fi].fi = min(chk[x.fi].fi,x.se);
			chk[x.fi].se = vn;
		}
		reset(lst);
	}
	if(chk[k].se == vn)	ans = min(ans,chk[k].fi);
	for(pii v:adj[cen]){
		if(vis[v.fi] != -1)	solve(v.fi);
	}
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y,v;
	scanf("%d %d",&n,&k);
	for(i=1;i<n;i++){
		scanf("%d %d %d",&x,&y,&v);
		adj[x].eb(y,v);
		adj[y].eb(x,v);
	}
	ans = inf;
	solve(0);
	printf("%d\n",(ans == inf) ? -1 : ans);
	return 0;
}

