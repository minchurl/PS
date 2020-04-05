#include<bits/stdc++.h>
#define MAX_N 2005
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
int n;
int c[MAX_N],ans[MAX_N],loc[MAX_N];
vector<int> adj[MAX_N];
int chk(int x,int i){
    int sum = (loc[x]<i)?1:0;
    for(int y:adj[x])   sum += chk(y,i);
    return sum;
}
void solve(int x){
    int i,y = 0;
    for(i=0;i<n;i++){
        if(!ans[i])  y++;
        if(y>c[x])  break;
    }
    if(y<=c[x]){
        printf("NO\n");
        exit(0);
    }
    ans[i] = x;
    loc[x] = i;
    for(int v:adj[x])   solve(v);
    if(chk(x,loc[x])!=c[x]){
        printf("NO\n");
        exit(0);
    }
}
int main(){
    freopen("input.txt","r",stdin);
    int i,x;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d %d",&x,&c[i]);
        adj[x].eb(i);
    }
    solve(adj[0][0]);
    printf("YES\n");
    for(i=1;i<=n;i++)    printf("%d ",loc[i]+1);
    printf("\n");
    return 0;
}