#include<bits/stdc++.h>
#define MAX_N 50005
#define MAX_M 2000005
#define MAX_K 1000000005
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
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
struct node{
    int w,x,d;
};
struct Ans{
    int w,t;
};
vector<Ans> ans;
vector<node> lst;
vector<int> B,W;
queue<int> Q;
int n,l;
int main(){
    freopen("input.txt","r",stdin);
    int i,w,x,y,z,d;
    scanf("%d %d",&n,&l);
    for(i=0;i<n;i++){
        scanf("%d %d %d",&w,&x,&d);
        lst.pb({w,x,d});
        if(d == -1){
            B.eb(x);
        }
    }
    sort(all(lst),[&](const node x,const node y){return x.x<y.x;});sort(all(B),[&](const int x,const int y){return x>y;});
    w=0;
    for(node p:lst){
        w+=p.w;
        if(p.d == 1){
            W.push_back(p.x);
        }
        x = (int)W.size();
        y = (int)B.size();
        if(x==y){
            ans.pb({p.w,((p.d == 1)?B[0]:(l-W[0]))});
        }else if(x>y){
            ans.pb({p.w,((p.d == 1)?(l-W[x-y-1]):(l-W[x-y]))});
        }else{
            ans.pb({p.w,((p.d == -1)?(B[y-x-1]):(B[y-x]))});
        }
        if(p.d == -1){
            B.pop_back();
        }
    }
    sort(all(ans),[&](const Ans x,const Ans y){return x.t<y.t;});
    x = inf;
    y = 0;
    for(Ans p:ans){
        y+=p.w;
        if(y>=w/2+w%2){
            x = p.t;
            break;
        }
    }
    y=0;
    for(node p:lst){
        if(p.d == 1){
            Q.push(p.d+x);
        }else{
            while(Q.size() && Q.front()<p.x-x)    Q.pop();
            y+=(int)Q.size();
        }
    }
    printf("%d\n",y);
    return 0;
}