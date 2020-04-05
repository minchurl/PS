#include<bits/stdc++.h>
#define MAX_N 50005
#define MAX_M 2000005
#define MAX_K 100005
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
struct edge{
    pii s,e;
    bool operator == (edge d){
        return s==d.s && e==d.e;
    }
    bool operator != (edge d){
        return s!=d.s || e!=d.e;
    }
    bool operator < (edge d){
        return (s==d.s)?(e<d.e):(s<d.s);
    }
};
vector<pii> V;
vector<edge> E;
int n;
char s[1005];
int main(){
    freopen("input.txt","r",stdin);
    scanf("%d",&n);
    int i;
    int x = 0, y = 0,xx,yy;
    scanf("%d",&n);
    scanf("%s",s);
    V.eb(x,y);
    for(i=0;i<n;i++){
        if(s[i] == 'N'){
            xx = x;
            yy = y + 1;
        }else if(s[i] == 'S'){
            xx = x;
            yy = y - 1;
        }else if(s[i] == 'E'){
            xx = x + 1;
            yy = y;
        }else{
            xx = x - 1;
            yy = y;
        }
        V.eb(xx,yy);
        E.pb({min(mp(x,y),mp(xx,yy)),max(mp(x,y),mp(xx,yy))});
        x = xx;
        y = yy;
    }
    sort(all(V));V.erase(unique(all(V)),V.end());
    sort(all(E));E.erase(unique(all(E)),E.end());
    printf("%d\n",1 - (int)V.size() + (int)E.size());
    return 0;
}