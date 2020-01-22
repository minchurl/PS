#include<bits/stdc++.h>
#define MAX_N 200005
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
#define inf (1LL<<60)
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
struct node{
	LL cost,pic,idx;
};
struct cmp{
	bool operator()(const node x,const node y){
		return (x.cost==y.cost)?(x.idx<y.idx):(x.cost<y.cost);
	};
};
LL n,m,k;
LL pic[MAX_N],C[MAX_N],P[MAX_N];
LL bonus[MAX_N],loc[MAX_N],cnt;

map<LL,priority_queue<pil>> pq[MAX_N];
map<LL,pil> lst[MAX_N];
priority_queue<pil> ba;

LL ans[MAX_N];
vector<pil> V[MAX_N];
LL cmp_1(node x,node y){
	if(x.cost==y.cost && x.pic==y.pic && x.idx==y.idx)	return 0;
	return (x.cost==y.cost)?(x.idx<y.idx?1:-1):(x.cost<y.cost?1:-1);
}
void merge(LL p,LL q){//S[p]<--S[q]
	for(auto x:map<LL,pil> lst[q]){
		if(lst[p].find(x.fi)==lst[p].end() || lst[p][x.fi].fi>x.se)	lst[p][x.fi]=x.se;
	}
	set<LL,pil>::iterator it = S[p].end();it--;
	while(S[q].size()){
		pil x=(*S[q].begin());
		x.fi+=bonus[q]-bonus[p];
		if(x.fi>=it->fi){
			add_lst(p,x);
			continue;
		}
		if(pic[it->se] == pic[x.se]){
			while(1){
				pil y=get_val(p);
				if(y.se==0)	break;
				if()
			}
		}else{
			
		}
	}
}
void dfs(LL x){
	loc[x]=cnt++;
	S[loc[x]].insert({C[pic[x]],x});
	for(pil y:V[x]){
		dfs(y.fi);
		spread_L(loc[y.fi],y.se);
		if(S[loc[x]].size()>=S[loc[y.fi]].size()){
			merge(loc[x],loc[y.fi]);
		}else{
			merge(loc[y.fi],loc[x]);
			loc[x]=loc[y.fi];
		}
		
	}
	ans[x]=S[loc[x]].size();
	return;
}
int main(){
	LL i,x,y;
	scanf("%lld %lld %lld",&n,&k,&m);
	for(i=2;i<=n;i++){
		scanf("%lld %lld",&x,&y);
		V[x].pb({i,y});
	}
	for(i=1;i<=n;i++)	scanf("%lld",&pic[i]);
	for(i=1;i<=k;i++)	scanf("%lld",&C[i]);
	for(i=1;i<=k;i++)	scanf("%lld",&P[i]);
	dfs(1);
	for(i=1;i<=n;i++)	printf("%lld\n",ans[i]);
	return 0;
}
