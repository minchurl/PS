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
int n,m;
int tree[8*MAX_N];
int buffer[8*MAX_N];
vector<int> X;
vector<pii> range;
priority_queue<int> pq;
void spread(int x){
    tree[2*x]+=buffer[x];
    tree[2*x+1]+=buffer[x];
    buffer[2*x]+=buffer[x];
    buffer[2*x+1]+=buffer[x];
    buffer[x] = 0;
}
void update(int x,int l,int r,int s,int e,int v){
    if(l!=r)    spread(x);
    if(r<s || e<l)  return;
    if(s<=l && r<=e){
        tree[x]+=v;
        buffer[x]+=v;
        return;
    }
    int mid=(l+r)>>1;
    update(2*x,l,mid,s,e,v);
    update(2*x+1,mid+1,r,s,e,v);
    tree[x]=max(tree[2*x],tree[2*x+1])+buffer[x];
}
int main(){
    freopen("input.txt","r",stdin);
    int i,s,e;
    int x,y;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d %d %d %d",&x,&e,&y,&s);
        X.eb(s);X.eb(e);
        range.eb(s,e);
    }
    sort(all(X));X.erase(unique(all(X)),X.end());
    m=(int)X.size();
    for(pii &p:range){
        p.fi = lower_bound(all(X),p.fi) - X.begin();
        p.se = lower_bound(all(X),p.se) - X.begin();
        update(1,0,m-1,p.fi,p.se,1);
    }
    sort(all(range));
    int ans=tree[1];
    for(pii &p:range){
        update(1,0,m-1,p.fi,p.se,-1);
        pq.push(-p.se);
        while(pq.top()>-p.fi)   pq.pop();
        ans=max(ans,(int)pq.size()+tree[1]);
    }
    printf("%d\n",ans);
    return 0;
}