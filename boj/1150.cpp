#include<bits/stdc++.h>
#define MAX_N 100005
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
#define inf 0x7fffffffLL
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
	LL x,l,r,c;
}V[MAX_N];
LL n,k,ans;
bool chk[MAX_N];
priority_queue<pil> pq;
void merge(LL x){
	LL l,r;
	l=V[x].l;
	r=V[x].r;
	chk[l]=chk[r]=true;
	V[x].x=V[l].x+V[r].x-V[x].x;
	V[x].l=V[l].l;V[V[l].l].r=x;
	V[x].r=V[r].r;V[V[r].r].l=x;
	V[x].c=V[l].c+V[r].c-V[x].c;
	if(V[x].c==0)	chk[x]=true;
}
int main(){
	LL i,x,y;
	scanf("%lld %lld",&n,&k);
	V[0]={inf,0,1,0};
	V[n]={inf,n-1,n,0};
	scanf("%lld",&x);
	for(i=1;i<n;i++){
		scanf("%lld",&y);
		V[i].x=y-x;
		V[i].l=i-1;V[i].r=i+1;
		V[i].c=1;
		x=y;
		pq.push({-V[i].x,i});
	}
	while(k--){
		while(pq.size() && chk[pq.top().se])	pq.pop();
		pil p=pq.top();pq.pop();
		ans+=-p.fi;
		merge(p.se);
		pq.push({-V[p.se].x,p.se});
	}
	printf("%lld\n",ans);
	return 0;
}
