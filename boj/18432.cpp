#include<bits/stdc++.h>
#define MAX_N 200005
#define MAX_M 2000005
#define MAX_K 1000000005
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).rezsize(0);
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
int n,k;
int J[MAX_N],O[MAX_N],I[MAX_N];
char s[MAX_N];
int main(){
    freopen("input.txt","r",stdin);
    int i;
    scanf("%d %d",&n,&k);
    scanf("%s",s);
    for(i=1;i<=n;i++){
        J[i]=J[i-1];
        O[i]=O[i-1];
        I[i]=I[i-1];
        if(s[i-1] == 'J')   J[i]++;
        if(s[i-1] == 'O')   O[i]++;
        if(s[i-1] == 'I')   I[i]++;
    }
    int x,y,z;
    int ans = n+1;
    for(i=1;i<=n;i++){
        x = lower_bound(J+1,J+n+1,J[i-1]+k)-J;
        if(x>n) continue;
        y = lower_bound(O+1,O+n+1,O[x]+k)-O;
        if(y>n) continue;
        z = lower_bound(I+1,I+n+1,I[y]+k)-I;
        if(z>n) continue;
        ans = min(ans,z-i+1-3*k);
    }
    printf("%d\n",(ans == n+1)?(-1):ans);
    return 0;
}