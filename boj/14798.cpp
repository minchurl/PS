#include<bits/stdc++.h>
#define MAX_N 100005
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
#define mod(x) (((x)%h + h)%h)
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
int r,c;
int ans[30][30];
char s[30];
int main(){
    freopen("input.txt","r",stdin);
    int TC,i,j,k;
    scanf("%d",&TC);
    for(int tt = 1; tt<=TC;tt++){
        printf("Case #%d:\n",tt);
        scanf("%d %d",&r,&c);
        for(i=0;i<r;i++){
            scanf("%s",s);
            char x = 0;
            for(j=0;j<c;j++){
                if(s[j] != '?') x = s[j];
                ans[i][j] = x;
            }
            for(j=0;j<c;j++){
                if(ans[i][j] != 0) break;
            }
            if(j != c){
                while(j--)  ans[i][j] = ans[i][j + 1];
            }
        }
        for(i=0;i<r;i++){
            if(ans[i][0] != 0)  continue;
            for(j=i-1;j>=0;j--){
                if(ans[j][0] != 0)  break;
            }
            if(j != -1){
                for(k=0;k<c;k++){
                    ans[i][k] = ans[j][k];
                }
                continue;
            }
            for(j=i+1;j<r;j++){
                if(ans[j][0] != 0)  break;
            }
            for(k=0;k<c;k++){
                ans[i][k] = ans[j][k];
            }
        }
        for(i=0;i<r;i++){
            for(j=0;j<c;j++)    printf("%c",ans[i][j]);
            printf("\n");
        }
    }
    return 0;
}