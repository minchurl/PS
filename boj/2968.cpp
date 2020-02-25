#include<bits/stdc++.h>
#define MAX_N 1000005
#define MAX_M 1000005
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))
#define fi first
#define se second
#define LL_inf 40000000000000000LL
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
LL n,m;
LL k;
LL sum[25];
LL ans;
int main(){
	freopen("input.txt","r",stdin);
    LL i,j,x,y;
    scanf("%lld %lld",&n,&m);
    scanf("%lld",&k);
    LL s,r = k;
    for(s=0;s<n+m-1;s++){
        if(r<min(s,n-1LL)-max(0LL,s-m+1LL)+1LL){
            s--;
            break;
        }
        r-=min(s,n-1LL)-max(0LL,s-m+1LL)+1LL;
    }
    for(i=0;i<n;i++){
        LL e = min(s-i,m-1LL);
        if(e<0) break;
        x = i;
        sum[0] = x%2;
        x/=2;
        for(j=1;j<=20;j++){
            sum[j] = sum[j-1] + x%2;
            x/=2;
        }
        for(j=20;j>=0;j--){
            if(((e>>j)&1) == 0) continue;
            if(j){
                ans+=(1LL<<j)-(1LL<<(j-sum[j-1]));
            }
            if((i>>j)&1){
                ans+=e%(1LL<<j)+1LL;
                break;
            }
            
        }
    }
    if(s%2){
        x=min(s+1,n-1);
        y=s+1-x;
    }else{
        y=min(s+1,m-1);
        x=s+1-y;
    }
    while(r--){
        if(x&y) ans++;
        if(s%2){
            x--;
            y++;
        }else{
            x++;
            y--;
        }
    }
    printf("%lld\n",k - ans);
	return 0;
}
