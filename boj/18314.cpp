#include<bits/stdc++.h>
#define MAX_N 50005
#define MAX_M 2000005
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
#define inf 0x3fffffff
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
//#define inf 0x3fffffff
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
struct Lst{
    int s,e;
    int idx;
};
vector<Lst> lst[MAX_Q];
int n,k;
int V[MAX_N];
int lt[MAX_N][MAX_K][MAX_K],rt[MAX_N][MAX_K][MAX_K];
int ans[MAX_Q];
void udt(int l,int r,int s,int e,int idx){
    int mid = (l + r) >> 1;
    if(l==r){
        ans[idx] = 2;
        return;
    }
    if(e<=mid){
        udt(l,mid,s,e,idx);
    }else if(s>mid){
        udt(mid+1,r,s,e,idx);
    }else{
        lst[mid].pb({s,e,idx});
        return;
    }
}
void make_lt(int l,int r){
    for(int e=1;e<=k;e++){
        lt[r+1][e][e] = 1;
    }
    for(int i=r;i>=l;i--){
        for(int e=1;e<=k;e++){
            for(int s=k;s>V[i];s--){
                if(s>e) continue;
                lt[i][s][e] = lt[i+1][s][e];
            }
            for(int s=V[i];s>=1;s--){
                if(s>e) continue;
                lt[i][s][e] = mod(lt[i+1][s][e] + lt[i+1][V[i]][e]);
            }
        }
    }
}
void make_rt(int l,int r){
    for(int s=1;s<=k;s++){
        rt[l-1][s][s] = 1;
    }
    for(int i=l;i<=r;i++){
        for(int s=1;s<=k;s++){
            for(int e=1;e<V[i];e++){
                if(s>e) continue;
                rt[i][s][e] = rt[i-1][s][e];
            }
            for(int e=V[i];e<=k;e++){
                if(s>e) continue;
                rt[i][s][e] = mod(rt[i-1][s][e] + rt[i-1][s][V[i]]);
            }
        }
    }
}
void init(int l,int r){
    for(int i=l;i<=r;i++){
        for(int j=1;j<=k;j++){
            for(int x=j;x<=k;x++){
                lt[i][j][x] = rt[i][j][x] = 0;
            }
        }
    }
}
void solve(int l,int r){
    if(l==r){
        return;
    }
    int mid = (l + r) >> 1;
    make_lt(l,mid);
    make_rt(mid+1,r);

    for(Lst p:lst[mid]){
        ans[p.idx] = 0;
        int sum = 0;
        for(int i=1;i<=k;i++){
            sum = mod(sum + lt[p.s][1][i]);
            ans[p.idx] = mod((LL)ans[p.idx] + (LL)sum * (LL)rt[p.e][i][k]);
        }
    }
    init(l,r);
    
    solve(l,mid);
    solve(mid+1,r);
}
int main(){
    freopen("input.txt","r",stdin);
    int i,s,e;
    scanf("%d %d",&n,&k);
    for(i=1;i<=n;i++){
        scanf("%d",&V[i]);
    }
    int q;
    scanf("%d",&q);
    for(i=1;i<=q;i++){
        scanf("%d %d",&s,&e);
        udt(1,n,s,e,i);
    }
    solve(1,n);
    for(i=1;i<=q;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}