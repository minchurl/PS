#include<bits/stdc++.h>
#define MAX_N 105
#define MAX_M 1000005
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))
#define fi first
#define se second
#define LL_inf 40000000000000000LL
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
#define inf 0x3fffffff
#define MOD 1000000007LL
#define cpx_mod(x) (((LD)(((LL)x.real())%MOD)),((LD)(((LL)x.imag())%MOD)))
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
typedef long double LD;
int n;
int a,b,cnt;
int ans;
int arr[MAX_N];
int t[MAX_N][MAX_N][MAX_N][3];
void solve1(int i){
    for(int x = 0 ; x <= cnt ; x++){
        int y = cnt - x;
        t[i][x][y][arr[i]%2] = min(t[i-1][x][y][arr[i]%2],t[i-1][x][y][1-arr[i]%2]+1);
        //printf("%d : %d %d : %d : %d\n",i,x,y,arr[i]%2,t[i][x][y][arr[i]%2]);
    }
}
void solve2(int i){
    cnt ++;
    for(int x = 0 ; x <= cnt ; x++){
        int y = cnt - x;
        //printf("%d %d\n",x,y);
        if(x > a || y > b)  continue;
        if(x){
            t[i][x][y][0] = min(t[i][x][y][0],min(t[i-1][x-1][y][0],t[i-1][x-1][y][1]+1));
        }
        if(y){
            t[i][x][y][1] = min(t[i][x][y][1],min(t[i-1][x][y-1][0]+1,t[i-1][x][y-1][1]));
        }
        //printf("%d : %d %d : 01 : %d %d\n",i,x,y,arr[i]%2,t[i][x][y][0],t[i][x][y][1]);
    }
}
int main(){
	freopen("input.txt","r",stdin);
    int i,j,k;
    scanf("%d",&n);
    a = n / 2;
    b = n / 2 + n % 2;
    cnt = 0;
    ans = inf;
    for(i=1;i<=n;i++){
        scanf("%d",&arr[i]);
        if(arr[i]){
            if(arr[i]%2)    b--;
            else    a--;
        }
    }
    for(i=0;i<=n;i++){
        for(j=0;j<=n;j++){
            for(k=0;k<=n;k++){
                t[i][j][k][0] = t[i][j][k][1] = inf;
            }
        }
    }
    t[0][0][0][0] = t[0][0][0][1] = 0;
    for(i=1;i<=n;i++){
        if(arr[i]) solve1(i);
        else    solve2(i);
        //printf("%d : %d\n",i,cnt);
    }

    for(i=0;i<=n;i++){
        for(j=0;j<=n;j++){
            ans = min(ans, min(t[n][i][j][0],t[n][i][j][1]));
        }
    }
    printf("%d\n",ans);
	return 0;
}
