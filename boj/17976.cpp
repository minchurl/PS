#include<bits/stdc++.h>
#define MAX_N 100005
#define eb emplace_back
#define all(V) (V).begin(), (V).end()
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL,LL> pil;
LL n;
vector<pil> V;
bool is_ok(LL l){
    LL x = V[0].fi;
    LL sz = V.size();
    for(LL i = 1 ; i < sz ; i++){
        if(x + l > V[i].fi + V[i].se)   return false;
        x = max(x + l, V[i].fi);
    }
    return true;
}
int main(){
    freopen("input.txt","r",stdin);
    LL x,l,r;
    scanf("%lld",&n);
    for(LL i=0;i<n;i++){
        scanf("%lld %lld",&x,&l);
        V.eb(x,l);
    }
    sort(all(V));
    l = 0LL;
    r = 2000000000LL;
    while(l < r){
        LL mid = ((l + r) >> 1) + 1;
        if(is_ok(mid)){
            l = mid;
        }else{
            r = mid - 1;
        }
    }
    printf("%lld\n",l);
    return 0;
}