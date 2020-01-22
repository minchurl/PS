#include<bits/stdc++.h>
#define MAX_N 8005
#define MAX_M 805
#define pb push_back
#define eb emplace_back
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
LL n,m,sum[MAX_N];
LL t[MAX_M][MAX_N];
void do_dp(LL idx,LL l,LL r,LL s,LL e){
	if(l>r)	return;
	LL mid=(l+r)>>1;
	LL x=inf,y=s;
	for(LL i=s;i<=e;i++){
		LL z=t[idx-1][i-1]+(sum[mid]-sum[i-1])*(mid-i+1);
		if(x>z){
			x=z;
			y=i;
		}
	}
	t[idx][mid]=x;
	do_dp(idx,l,mid-1,s,y);
	do_dp(idx,mid+1,r,y,e);
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,x;
	scanf("%lld %lld",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%lld",&x);
		sum[i]=sum[i-1]+x;
		t[0][i]=inf;
	}
	for(i=1;i<=m;i++){
		do_dp(i,1,n,1,n);
	}
	printf("%lld\n",t[m][n]);
	return 0;
}
