#include<bits/stdc++.h>
#define MAX_N 270000
#define MAX_M 55
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
#define inf 0x3fffffff
#define MOD 1000000007
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
typedef long double LD;
LL n;
LL arr[MAX_N];
LL ans = -LL_inf,val;
void read(LL idx,LL depth,LL l,LL r){
	if(r<depth || idx>n)	return;
	read(idx*2,depth+1,l,r);
	if(l<=depth){
		val=max(val+arr[idx],arr[idx]);
		ans=max(ans,val);
	}
	read(idx*2+1,depth+1,l,r);
}
int main(){
	freopen("input.txt","r",stdin);
	scanf("%lld",&n);
	for(LL i=1;i<=n;i++){
		scanf("%lld",&arr[i]);
	}
	for(LL l=1;l<=18;l++){
		for(LL r=l;r<=18;r++){
			val = -LL_inf;
			read(1,1,l,r);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
