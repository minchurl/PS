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
LL n,m,ans,C[MAX_N];
LL cnt[MAX_N][35];
vector<LL> E[MAX_N];
bool chk[MAX_N][35];
queue<pil> Q;
int main(){
	LL i,j,x,z;
	scanf("%lld %lld %lld",&n,&m,&x);
	for(i=1;i<=n;i++){
		scanf("%lld",&C[i]);
		C[i]--;
		cnt[i][(1<<C[i])]++;
		if(!chk[i][(1<<C[i])])	Q.push({i,(1<<C[i])});
		chk[i][(1<<C[i])]=true;
	}
	while(m--){
		scanf("%lld %lld",&x,&z);
		E[x].pb(z);
		E[z].pb(x);
	}
	while(Q.size()){
		x=Q.front().fi;j=Q.front().se;
		Q.pop();
		for(LL y:E[x]){
			if(j&(1<<C[y]))	continue;
			cnt[y][j|(1<<C[y])]+=cnt[x][j];
			if(!chk[y][j|(1<<C[y])])	Q.push({y,j|(1<<C[y])});
			chk[y][j|(1<<C[y])]=true;
			ans+=cnt[x][j];
		}
	}
	printf("%lld\n",ans);
	return 0;
	
}
