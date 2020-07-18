#include<bits/stdc++.h>
#define MAX_N 100005
#define MAX_M 100005
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
struct node{
    LL a,b;
    LL idx;
};
LL n;
vector<node> ans;
int main(){
    freopen("input.txt","r",stdin);
    LL i;
    LL s,w1,w2,w3;
    scanf("%lld",&n);
    for(i=1;i<=n;i++){
        scanf("%lld %lld %lld %lld",&s,&w1,&w2,&w3);
        ans.pb({2*s*(w1*w2+w2*w3+w3*w1)-(w1+w2)*(w2+w3)*(w3+w1)+2*w1*w2*w3,s,i});
    }
    sort(all(ans),[&](const node x,const node y){
        if(x.a*y.b*y.b*y.b == y.a*x.b*x.b*x.b)  return x.idx<y.idx;
        return x.a*y.b*y.b*y.b < y.a*x.b*x.b*x.b;
    });
    for(i=0;i<n;i++)    printf("%lld ",ans[i].idx);
    printf("\n");
    return 0;
}