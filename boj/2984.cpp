#include<bits/stdc++.h>
#define MAX_N 100005
#define MAX_M 10005
#define MAX_E 320
#define MAX_K 25
#define MAX_Q 200005
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).rezsize(0);
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))
#define fi first
#define se second
//#define inf 0x3fffffff
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
#define inf (1LL<<60)
#define MOD 1000000007LL
#define cpx_mod(x) (((LD)(((LL)x.real())%MOD)),((LD)(((LL)x.imag())%MOD)))
#define prev(x) (((x)+n-1)%n)
#define next(x) (((x)+1)%n)
#define mod(x) ((int)((((LL)x)%1000000007LL + 1000000007LL)%1000000007LL))
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls; 
typedef complex<LD> Complex;
LL n;
LL t[MAX_N];
LL A[MAX_N],B[MAX_N];
int main(){
    freopen("input.txt","r",stdin);
    LL i;
    scanf("%lld",&n);
    for(i=1;i<=n;i++){
        scanf("%lld %lld",&A[i],&B[i]);
        t[i] = inf;
    }
    sort(A+1,A+n+1);
    sort(B+1,B+n+1);
    for(i=1;i<=n;i++){
        if(A[i] != B[i]){
            t[i] = min(t[i], t[i-1] + abs(A[i] - B[i]));
        }
        if(i > 1){
            t[i] = min(t[i], t[i-2] + abs(A[i] - B[i-1]) + abs(B[i] - A[i-1]));
        }
        if(i > 2){
            t[i] = min(t[i], t[i-3] + min(abs(A[i] - B[i-1]) + abs(A[i-1] - B[i-2]) + abs(A[i-2] - B[i]),abs(B[i] - A[i-1]) + abs(B[i-1] - A[i-2]) + abs(B[i-2] - A[i])));
        }
    }
    printf("%lld\n",t[n]);
    return 0;
}