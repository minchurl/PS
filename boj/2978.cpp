#include<bits/stdc++.h>
#define MAX_N 1005
#define MAX_M 10005
#define MAX_E 320
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
int n,m;
int A[MAX_N];
int t[MAX_N][5*MAX_N];
pii from[MAX_N][5*MAX_N];
int chk[MAX_N][5*MAX_N];
char s[MAX_N];
int E[7] = {1,10,100,1000,10000,100000};
stack<int> ans;
int main(){
    freopen("input.txt","r",stdin);
    int i,j,k,l;
    scanf("%s",s);
    l = strlen(s);
    for(i=0;i<l;i++){
        if(s[i] == '='){
            break;
        }
        A[i+1] = s[i] - '0';
    }
    n = i;
    i++;
    for(;i<l;i++){
        m = m * 10 + s[i] - '0';
    }
    chk[0][0] = 1;
    for(i=1;i<=n;i++){
        for(j=0;j<=m;j++){
            int sum = 0;
            for(k=i;k>0;k--){
                sum += A[k]*E[i-k];
                if(j + sum > m || i-k > 4) break;
                if(!chk[k-1][j])    continue;
                l = t[k-1][j] + 1;
                if(sum == 0 && chk[k-1][j] == 2){
                    l--;
                }
                if(t[i][j+sum] && (t[i][j+sum] < l || (t[i][j+sum] == l && chk[i][j+sum] == 2))) continue;
                t[i][j+sum] = l;
                chk[i][j + sum] = 1;
                if(sum == 0){
                    chk[i][j+sum] = 2;
                }       
                from[i][j+sum] = mp(k-1,j);
            }
        }
    }
    i = n;
    j = m;
    while(i){
        pii p = from[i][j];
        l = t[i][j];
        i = p.fi;
        j = p.se;
        if(l != t[i][j])    ans.push(i);
    }
    ans.pop();
    for(i=1;i<=n;i++){
        printf("%d",A[i]);
        if(ans.size() && ans.top() == i){
            printf("+");
            ans.pop();
        }
    }
    printf("=%d\n",m);
    return 0;
}