//fefe
#include<bits/stdc++.h>
//#include<inttypes.h>//__int64,__int128(?)
#define MAX_N 5005
#define MAX_M 105
//vector&pair
#define pb push_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
//math
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))//Regardless of type
//for pair
#define fi first
#define se second
//infinit
#define LL_inf (1LL<<60)
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
#define inf 0x3fffffff
//MOD
#define MOD 1000000007LL
#define mod(x,m) (((x)%(m)+(m))%(m)) //-+-+
//operator(such as complex)
#define cpx_mod(x) (((LD)(((LL)x.real())%MOD)),((LD)(((LL)x.imag())%MOD)))

using namespace std;
//type
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef long double LD;
typedef complex<LD> Complex;
LL n,a[MAX_N];
pil arr[MAX_N],p,q;
LL ccw(pil x,pil y,pil z){return (x.fi*y.se+y.fi*z.se+z.fi*x.se)-(x.se*y.fi+y.se*z.fi+z.se*x.fi);}
int main(){
	freopen("input.txt","r",stdin);
	LL s,e,i,ans,x,Q;
	scanf("%lld",&n);
	for(i=0;i<n;i++)	scanf("%lld %lld",&arr[i].fi,&arr[i].se);
	scanf("%lld",&Q);
	while(Q--){
		scanf("%lld %lld",&p.fi,&p.se);
		scanf("%lld %lld",&q.fi,&q.se);
		e=1;x=0;
		for(s=0;s<n;s++){
			while(ccw(arr[s],arr[e],p)>0){e=(e+1)%n;x++;}
			a[s]=x;printf("%lld %lld %lld\n",s,e,x);x--;
			if(x<0){e=(s+1)%n;x=0;}
		}
		
		ans=0;
		
		e=1;x=0;
		for(s=0;s<n;s++){
			while(ccw(arr[s],arr[e],q)>0){e=(e+1)%n;x++;}
			ans+=abs(a[s]-x);printf("  %lld %lld %lld\n",s,e,x);x--;
			if(x<0){e=(s+1)%n;x=0;}
		}
		printf("%lld\n",ans);		
	}
	return 0;
}
//end
