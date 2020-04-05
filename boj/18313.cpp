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
#define mod(x) (((x)%1000000007LL + 1000000007LL)%1000000007LL)
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
int n,m;
int num[MAX_N][MAX_N],k,pa[MAX_N*MAX_N];
char in[MAX_N][MAX_N];
bool chk[MAX_N*MAX_N];
vector<int> adj[MAX_N*MAX_N];
int find_pa(int x){
    return (pa[x] == x)?x:(pa[x] = find_pa(pa[x]));
}
void merge(int x,int y){
    x = find_pa(x);
    y = find_pa(y);
    pa[y] = x;
}
LL dfs(int u){
    LL mul = 1LL;
    for(int v:adj[u]){
        mul = mod(mul*(1LL+dfs(v)));
    }
    return mul;
}
int main(){
    freopen("input.txt","r",stdin);
    int i,j;
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++){
        scanf("%s",in[i]);
        for(j=0;j<m;j++)    pa[m*i+j+1]=m*i+j+1;
    }
    for(i=0;i<m;i++)    in[n][i] = '#';
    for(i=n-1;i>=0;i--){
        int pre = 0;
        for(j=0;j<m;j++){
            if(in[i][j] == '#'){
                pre = 0;
                continue;
            }
            if(pre == 0){
                pre = ++k;
            }
            if(num[i+1][j]){
                merge(pre,num[i+1][j]);
            }
            num[i][j] = pre;
        }
        for(j=0;j<m;j++){
            if(in[i][j] == '#') continue;
            num[i][j] = find_pa(num[i][j]);
            if(num[i+1][j] && !chk[num[i+1][j]]){
                adj[find_pa(num[i+1][j])].eb(num[i+1][j]);
                chk[num[i+1][j]] = true;
            }
        }
    }
    LL ans = 1LL;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(num[i][j] && !chk[num[i][j]]){
                chk[num[i][j]] = true;
                ans = mod((dfs(num[i][j])+1LL)*ans);
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}