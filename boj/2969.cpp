#include<bits/stdc++.h>
#define MAX_N 1505
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define fi first
#define se second
using namespace std;
typedef pair<int, int> pii;
struct segment_tree{
    int n;
    pii lst[5];

    void init(int x){
        n = x;
    }
    int get(int p){
        int res = 0;
        for(int i = 0 ; i < 4 ; i++){
            if(p - 1 > lst[i].fi || p + 1 < lst[i].fi){
                res = lst[i].se;
                break;
            }
        }
        return res;
    }
    void update(int p, int v){
        lst[4] = make_pair(p,v);
        for(int i = 3 ; i >= 0 ; i--){
            if(lst[i].se < lst[i + 1].se){
                swap(lst[i], lst[i + 1]);
            }
        }
    }
    
}R[MAX_N],C[MAX_N];
struct node{
    pii loc;
    int v;
    bool operator < (const node d){
        return v > d.v;
    }
};
int n;
vector<node> lst;
int get(pii loc){
    return max(max(R[loc.fi - 1].get(loc.se), R[loc.fi + 1].get(loc.se))
             , max(C[loc.se - 1].get(loc.fi), C[loc.se + 1].get(loc.fi)));
}
void update(pii loc, int v){
    R[loc.fi].update(loc.se, v);
    C[loc.se].update(loc.fi, v);
}
int main(){
    freopen("input.txt","r",stdin);
    int i, j, v, curr, st;
    pii init_loc;
    scanf("%d", &n);
    scanf("%d %d", &init_loc.fi, &init_loc.se);
    for(i = 1 ; i <= n ; i++){
        for(j = 1 ; j <= n ; j++){
            scanf("%d", &v);
            lst.pb({{i,j},v});
            curr = max(curr, v);
        }
        R[i].init(n);
        C[i].init(n);
    }
    curr++;
    sort(all(lst));
    int sz = lst.size();
    st = -1;
    for(i = 0 ; i < sz ; i++){
        node p = lst[i];
        if(p.v < curr){
            for(j = max(0, st) ; j < i ; j++){
                update(lst[j].loc, lst[j].v);
            }
            st = i;
        }
        curr = p.v;
        lst[i].v = get(p.loc) + 1;
        if(p.loc == init_loc){
            printf("%d\n",lst[i].v);
            break;
        }
    }
    return 0;
}