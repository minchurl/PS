#include<bits/stdc++.h>
#define MAX_N 20005
#define MAX_M 20005
#define MAX_E 205
#define MAX_K 205
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
int n,k;
int in_s[105][13];
LD a[1005][105][105];
int main(){
    freopen("input.txt","r",stdin);
    int TC;
    int s;
    scanf("%d",&TC);
    while(TC--){
        scanf("%d %d",&n,&k);
        s = 0;
        for(int i=0;i<n;i++){
            scanf("%s",in_s[i]);
            if(in_s[i][0] == 'I' && in_s[i][1] == 'C' && in_s[i][2] == 'N'){
                s = i;
            }
        }
        for(int i=0;i<n;i++){
            int sum = 0;
            for(int j=0;j<n;j++){
                int x;
                scanf("%d",&x);
                sum += x;
                a[1][i][j] = (LD)x;
            }
            for(int j=0;j<n;j++){
                if(a[1][i][j] < (LD)1e-6 || sum == 0){
                    a[1][i][j] = (LD)3;
                }else{
                    a[1][i][j] = log(a[1][i][j] / ((LD)sum));
                }
            }
        }
        for(int t=2;t<=k;t++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    a[t][i][j] = (LD)3;
                }
            }

            for(int i=0;i<n;i++){
                for(int p=0;p<n;p++){
                    if(a[t-1][i][p] > (LD)2)    continue;
                    for(int j=0;j<n;j++){
                        if(a[1][p][j] > (LD)2)    continue;
                        if(a[t][i][j] > (LD)2 || a[t][i][j] < a[1][p][j] + a[t-1][i][p]){
                            a[t][i][j] = a[1][p][j] + a[t-1][i][p];
                        }
                    }
                }
            }
        }
        LD ans = (LD)3;
        int ansn = 0;
        for(int i=0;i<n;i++){
            if(a[k][s][i] > (LD)2)  continue;
            if(ans > (LD)2 || a[k][s][i] > ans){
                ans = a[k][s][i];
                ansn = i;
            }
        }
        printf("%s\n",in_s[ansn]);
    }
    return 0;
}