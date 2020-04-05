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
LL n,m,heap[4*MAX_N];
LL sum;
vector<LL> lst;
bool detect(LL u,LL dep){
	if(dep <= m && heap[2*u] == 0 && heap[2*u+1] == 0)	return false;
	if(dep == m)	return true;
	if(heap[2*u] > heap[2*u+1]){
		return detect(2*u,dep+1);
	}else{
		return detect(2*u+1,dep+1);
	}
}
void del(LL u,LL dep){
	heap[u] = 0;
	if(dep == n || (heap[2*u] == 0 && heap[2*u+1] == 0)){
		return;
	}
	if(heap[2*u] > heap[2*u+1]){
		heap[u] = heap[2*u];
		del(2*u,dep+1);
	}else{
		heap[u] = heap[2*u+1];
		del(2*u+1,dep+1);
	}
}
void dfs(LL u,LL dep){
	while(detect(u,dep)){
		lst.eb(u);
		del(u,dep);
	}
	if(dep<m){
		dfs(2*u,dep+1);
		dfs(2*u+1,dep+1);
	}
}
int main(){
	freopen("input.txt","r",stdin);
	LL TC;
	LL i;
	scanf("%lld",&TC);
	while(TC--){
		scanf("%lld %lld",&n,&m);
		int e = (1LL<<n);
		for(i=1;i<e;i++){
			scanf("%lld",&heap[i]);
		}
		sum=0;
		reset(lst);
		dfs(1,1);
		for(i=1;i<e;i++)	sum+=heap[i];
		printf("%lld\n",sum);
		for(LL p:lst)	printf("%lld ",p);
		printf("\n");
	}
	return 0;
}