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
int lst[2][MAX_N];
int loc[MAX_N];
int l[2], r[2];
bool chk[MAX_N];
vector<int> ans;
int main(){
    freopen("input.txt","r",stdin);
    int i,j,st;
    scanf("%d",&n);
    for(i=0;i<2;i++){
        for(j=0;j<n;j++){
            scanf("%d",&lst[i][j]);
            loc[lst[i][j]] = j;
        }
    }
    for(st=0;st<n;st++){
        if(chk[st]) continue;
        l[0] = r[0] = st;
        l[1] = r[1] = loc[lst[0][st]];
        chk[st] = true;
        ans.eb(lst[0][st]);
        while(next(r[0]) != l[0]){
            if(lst[0][prev(l[0])] == lst[1][prev(l[1])]){
                ans.eb(lst[0][prev(l[0])]);
                chk[prev(l[0])] = true;
                l[0] = prev(l[0]);
                l[1] = prev(l[1]);
            }else if(lst[0][prev(l[0])] == lst[1][next(r[1])]){
                ans.eb(lst[0][prev(l[0])]);
                chk[prev(l[0])] = true;
                l[0] = prev(l[0]);
                r[1] = next(r[1]);
            }else if(lst[0][next(r[0])] == lst[1][prev(l[1])]){
                ans.eb(lst[0][next(r[0])]);
                chk[next(r[0])] = true;
                r[0] = next(r[0]);
                l[1] = prev(l[1]);
            }else if(lst[0][next(r[0])] == lst[1][next(r[1])]){
                ans.eb(lst[0][next(r[0])]);
                chk[next(r[0])] = true;
                r[0] = next(r[0]);
                r[1] = next(r[1]);
            }else{
                break;
            }
        }
        if(ans.size() == n){
            break;
        }

        reset(ans);
    }
    if(ans.size() == n){
        for(int p:ans){
            printf("%d ",p);
        }
        printf("\n");
    }else{
        printf("-1\n");
    }
    return 0;
}