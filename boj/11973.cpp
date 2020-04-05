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
int n,k;
vector<int> lst;
bool is_ok(int R){
    int i, cnt = 1, x = lst[0];
    for(i=1;i<n;i++){
        if(x + 2 * R < lst[i]){
             x = lst[i];
             cnt++;
        }
    }
    return cnt <= k;
}
int main(){
    freopen("input.txt","r",stdin);
    scanf("%d %d",&n,&k);
    for(int i=0;i<n;i++){
        int x;
        scanf("%d",&x);
        lst.eb(x);
    }
    sort(all(lst));
    int l = 0;
    int r = 1000000000;
    while(l < r){
        int mid = (l + r) >> 1;
        if(!is_ok(mid)){
            l = mid + 1;
        }else
        {
            r = mid;
        }
    }
    printf("%d\n",l);
	return 0;
}