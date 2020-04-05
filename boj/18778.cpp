#include<bits/stdc++.h>
#define MAX_N 305
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
struct co_sys{
    int n;
    int sum1[2*MAX_N][2*MAX_N],sum2[2*MAX_N][2*MAX_N];
    bool arr[2*MAX_N][2*MAX_N];
    void set_n(int v){
        n=v;
        return;
    }
    void set_arr(int x,int y,char v){
        arr[x+y][x-y+n] = (v == '*');
    }
    bool get_arr(int x,int y){
        if(x<1 || y<1 || x>n || y>n)    return false;
        return arr[x+y][x-y+n];
    }
    void init(){
        int i,j;
        for(i=1;i<=2*n;i++){
            for(j=1;j<=2*n;j++) sum1[i][j] = sum1[i][j-1] + arr[i][j];
        }
        for(i=1;i<=2*n;i++){
            for(j=1;j<=2*n;j++) sum2[i][j] = sum2[i][j-1] + arr[j][i];
        }
    }
    pii get_co(int x,int y){
        return mp(x+y,x-y+n);
    }
    int sum_case1(pii s,pii e){
        if(s.fi<0 || s.fi > 2*n || s.se>2*n || e.se<0)  return 0;
        return sum1[s.fi][min(e.se,2*n)] - sum1[s.fi][max(s.se-1,0)];
    }
    int sum_case2(pii s,pii e){
        if(s.se<0 || s.se > 2*n || s.fi>2*n || e.fi<0)  return 0;
        return sum2[s.se][min(e.fi,2*n)] - sum2[s.se][max(s.fi-1,0)];
    }
    int get_sum(int sx,int sy,int ex,int ey){
        pii s = get_co(sx,sy);
        pii e = get_co(ex,ey);
        if(s>e) return 0;
        if(s.se != e.se)    return sum_case1(s,e);
        else    return sum_case2(s,e); 
    }
}co;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,i,j,r;
    int ans = 0;
    char s[MAX_N];
    scanf("%d",&n);
    co.set_n(n);
    for(i=1;i<=n;i++){
        scanf("%s",s);
        for(j=1;j<=n;j++)   co.set_arr(i,j,s[j-1]);
    }
    co.init();
    for(r=1;r<=n;r++){
        for(i=1;i<=n;i++){
            for(j=1;j<=n;j++){
                if(!co.get_arr(i,j))    continue;
                if(co.get_arr(i+r,j+r)){
                    ans+=co.get_sum(i-r,j+r,i,j+2*r);
                    ans+=co.get_sum(i+r,j-r,i+2*r,j);
                }
                if(co.get_arr(i+r,j-r)){
                    ans += co.get_sum(i+r+1,j+r-1,i+2*r-1,j+1);
                    ans += co.get_sum(i-r+1,j-r-1,i-1,j-2*r+1);
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}