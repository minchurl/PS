#include<bits/stdc++.h>
#define MAX_N 305
#define MAX_M 2000005
#define MAX_K 1000000005
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
#define mod(x) (((x)%998244353LL + 998244353LL)%998244353LL)
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
int n,m,ans;
char s[105][105];
int chk[105];
int main(){
    freopen("input.txt","r",stdin);
    int i,j;
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++){
        scanf("%s",s[i]);
        for(j=0;j<m;j++){
            if(s[i][j] == '.'){
                chk[j] = 0;
                continue;
            }
            if(chk[j] == 0) ans++;
            chk[j] = 1;
            while(j+1<m && s[i][j+1] == '*'){
                j++;
                chk[j] = 1;
            } 
        }
    }
    printf("%d\n",ans);
    return 0;
}