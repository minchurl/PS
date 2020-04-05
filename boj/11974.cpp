#include<bits/stdc++.h>
#define MAX_N 50005
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
#define mod(x) (((x)%998244353LL + 998244353LL)%998244353LL)
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
int n;
vector<int> lst[7];
int main(){
    freopen("input.txt","r",stdin);
    int i,x,sum = 0;
    scanf("%d",&n);
    lst[0].eb(0);
    for(i=1;i<=n;i++){
        scanf("%d",&x);
        sum = (sum+x) % 7;
        lst[sum].eb(i);
    }
    int ans = 0;
    for(i=0;i<7;i++){
        if(!lst[i].size())  continue;
        ans = max(ans,lst[i].back() - lst[i].front());
    }
    printf("%d\n",ans);
	return 0;
}