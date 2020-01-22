#include<bits/stdc++.h>
#define MAX_N 300005
#define MAX_M 100005
#define pb push_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))
#define fi first
#define se second
#define LL_inf (1LL<<60)
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
#define inf 0x3fffffff
#define MOD 1000000007LL
#define cpx_mod(x) (((LD)(((LL)x.real())%MOD)),((LD)(((LL)x.imag())%MOD)))
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
typedef long double LD;
int n,m,k;
int rep[3][MAX_N],num[3][MAX_N];
int pa[MAX_N],cnt[MAX_N];
vector<int> E[3][MAX_N];
vector<pii> lst;
int find_pa(int x){return (pa[x]==x)?(x):(pa[x]=find_pa(pa[x]));}
int dfs(int c,int x){
	if(x<=k){num[c][x]=1;rep[c][x]=x;return x;}
	for(int y:E[c][x]){
		rep[c][x]=dfs(c,y);
		num[c][x]+=num[c][y];
	}
	if(E[c][x].size()!=1)	lst.pb({c,x});
	return rep[c][x];
}
int main(){
	int i,x,y;
	scanf("%d %d %d",&n,&m,&k);
	for(i=1;i<=n;i++){
		scanf("%d",&x);
		E[0][x].pb(i);
	}
	for(i=1;i<=m;i++){
		scanf("%d",&x);
		E[1][x].pb(i);
	}
	dfs(0,E[0][0][0]);
	dfs(1,E[1][0][0]);
	for(i=1;i<=k;i++){pa[i]=i;cnt[i]=1;}
	sort(all(lst),[&](const pii x,const pii y){return num[x.fi][x.se]<num[y.fi][y.se];});
	
	for(pii p:lst){
		for(int z:E[p.fi][p.se]){
			x=find_pa(rep[p.fi][p.se]);
			y=find_pa(rep[p.fi][z]);
			if(x==y)	continue;
			pa[y]=pa[x];
			cnt[x]+=cnt[y];
		}
		if(cnt[find_pa(rep[p.fi][p.se])]!=num[p.fi][p.se])	return !printf("NO\n");
	}
	printf("YES\n");
	return 0;
}
