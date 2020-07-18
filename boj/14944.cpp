#include<bits/stdc++.h>
#define MAX_N 10005
#define MAX_M 20005
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
#define inf 0x3fffffff
#define MOD 1000000007LL
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
int n,m;
int sum[MAX_N];
int ans;
int main(){
    freopen("input.txt","r",stdin);
    int i,j,x,y,z,k;
    int u,v,val;
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++){
        scanf("%d",&x);
        sum[i] = sum[i-1] + x;
    }
    ans = inf;
    while(m--){
        scanf("%d %d %d",&u,&v,&val);
        if(u>v) swap(u,v);
        x = sum[u];
        y = val;
        z = sum[v]-sum[u];
        k = sum[n] - sum[v];
        i = sum[u+1] - sum[u];
        j = sum[v] - sum[v-1];
        ans = min(ans, x + 2 * k + min(y + z - i, y + z - j + y));
        ans = min(ans, x + k + min(2*y + z,2 * z + y));
    }
    printf("%d\n",ans);
    return 0;
}