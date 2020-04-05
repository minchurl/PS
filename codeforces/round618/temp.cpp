#include<bits/stdc++.h>
#define MAX_N 1048676
#define MAX_M 2000005
#define MAX_K 100005
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))
#define fi first
#define se second
#define inf 0x3fffffff
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
//#define inf 0x3fffffff
#define MOD 1000000007LL
#define cpx_mod(x) (((LD)(((LL)x.real())%MOD)),((LD)(((LL)x.imag())%MOD)))
#define prev(x) (((x)+n-1)%n)
#define next(x) (((x)+1)%n)
#define mod(x) (((x)%m + m)%m)
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
LL n,m,val[MAX_N],mx[MAX_N];
priority_queue<pil> pq1[MAX_N],pq2[MAX_N];
vector<LL> lst;
void merge(LL u,LL v){
	while(pq1[v].size()){
		pq1[u].push(pq1[v].top());
		pq1[v].pop();
	}
	while(pq2[v].size()){
		pq2[u].push(pq2[v].top());
		pq2[v].pop();
	}
}
LL dfs(LL u,LL dep){
	while(pq1[u].size())	pq1[u].pop();
	while(pq2[u].size())	pq2[u].pop();
	mx[u] = 0;
	LL sum=0;
	pq2[u].push({-val[u],u});
	if(dep<=m)	sum++;
	if(dep!=n){
		sum+=dfs(2*u,dep+1);
		sum+=dfs(2*u+1,dep+1);
	}
	if(dep<=m){
		if()
	}
	return sum;
}
int main(){
	freopen("input.txt","r",stdin);
	LL TC;
	LL i,sum;
	scanf("%lld",&TC);
	while(TC--){
		scanf("%lld %lld",&n,&m);
		int e = (1LL<<n);
		for(i=1;i<e;i++){
			scanf("%lld",&val[i]);
		}
		
		printf("\n");
	}
	return 0;
}