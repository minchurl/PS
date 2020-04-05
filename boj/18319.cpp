#include<bits/stdc++.h>
#define MAX_N 1005
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
int n,k,arr[MAX_N];
int ans;
priority_queue<int> pq;
int main(){
    freopen("input.txt","r",stdin);
    int i,j,p,sum;
    scanf("%d %d",&n,&k);
    for(i=1;i<=n;i++){
        scanf("%d",&arr[i]);
    }
    for(i=1;i<=1000;i++){
        while(pq.size())    pq.pop();
        for(j=1;j<=n;j++){
            pq.push(arr[j]);
        }
        sum=0;
        for(j=1;j<=k;j++){
            p = pq.top();pq.pop();
            if(j>k/2)   sum+=min(i,p);
            p-=min(i,p);
            pq.push(p);
        }
        ans = max(ans,sum);
    }
    printf("%d\n",ans);
    return 0;
}