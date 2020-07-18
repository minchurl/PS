#include<bits/stdc++.h>
#define MAX_N 100005
#define MAX_M 20005
#define MAX_E 205
#define MAX_K 205
#define MAX_Q 200005
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
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
int n;
vector<pii> lst;
bool is_ok(int k){
    int i,c;
    for(i=0;i<n;i++){
        if(lst[i].se > k / 2){
            break;
        }
    }
    c = 0;
    while(i != n){
        c++;
        int mx, mn;
        mx = mn = lst[i].se;
        i++;
        for(;i<n;i++){
            if(mx < lst[i].se){
                if(lst[i].se - mn > k)    break;
                mx = lst[i].se;
            }else if(mn > lst[i].se){
                if(mx - lst[i].se > k)    return false;
                mn = lst[i].se;
            }
        }
    }
    return c < 3;
}
int main(){
    freopen("input.txt","r",stdin);
    int i;
    scanf("%d",&n);
    lst.resize(n);
    for(i=0;i<n;i++){
        scanf("%d %d",&lst[i].fi,&lst[i].se);
    }
    sort(all(lst));
    int l = 0, r = 1e9;
    if(lst[0].fi == 0){
        l = lst[0].se * 2;
    }
    while(l < r){
        int mid = (l + r) >> 1;
        if(is_ok(mid)){
            r = mid;
        }else{
            l = mid + 1;
        }
    }
    printf("%.1f\n",(double)l / 2);
    return 0;
}