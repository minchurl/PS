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
int dis(int sx,int sy,int ex,int ey){
    return abs(sx-ex) + abs(sy-ey);
}
int main(){
    freopen("input.txt","r",stdin);
    int i;
    int n,x1,x2,x3,y1,y2,y3;
    int ans[MAX_N] = {0,};
    char s[MAX_N][MAX_N];
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%s",s[i]);
    }
    for(x1=0;x1<n;x1++){
        for(y1=0;y1<n;y1++){
            for(x2=0;x2<n;x2++){
               for(y2=0;y2<n;y2++){
                    for(x3=0;x3<n;x3++){
                        for(y3=0;y3<n;y3++){
                            if(dis(x1,y1,x2,y2) == dis(x2,y2,x3,y3) && dis(x1,y1,x2,y2) == dis(x3,y3,x1,y1) && s[x1][y1] == '*' && s[x2][y2] == '*' && s[x3][y3] == '*'){
                                ans[dis(x1,y1,x2,y2)]++;
                            }
                        }
                    }        
                }
            }
        }
    }
    for(i=1;i<=2*n;i++){
        printf("%d : %d\n",i,ans[i]/6);
    }
    return 0;
}