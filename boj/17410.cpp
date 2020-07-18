#include<bits/stdc++.h>
#define MAX_N 100005
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
#define inf 0x3fffffff
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
//#define inf 0x3fffffff
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
int n,e;
int V[MAX_N];
int t[MAX_E][MAX_M];
int get_i(int x){
    return (x-1)/e;
}
void update(int i,int p,int v){
    for(;p<=10000;p+=(p&-p)){
        t[i][p]+=v;
    }
    return;
}
int read(int i,int p){
    int sum = e;
    for(;p>0;p-=(p&-p)){
        sum -= t[i][p];
    }
    return sum;
}
void init(){
    int E = (n%e?e:0)+n/e*e;
    for(int i=1;i<=E;i++){
        update(get_i(i),V[i]?V[i]:1,1);
    }
}
int get_sum(int i,int j,int k){
    int sum = 0;
    if(i>j) return 0;
    if(j-i == e-1 && j%e == 0){
        sum = read(get_i(i),k);
    }else{
        for(;i<=j;i++){
            sum += V[i]>k;
        }
    }
    return sum;
}
int main(){
    freopen("input.txt","r",stdin);
    int i,j,z,v;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d",&v);
        V[i] = v;
    }
    e = sqrt(n);
    init();
    int q;
    scanf("%d",&q);
    while(q--){
        scanf("%d",&z);
        if(z == 1){
            scanf("%d %d",&i,&v);
            update(get_i(i),V[i],-1);
            V[i] = v;
            update(get_i(i),V[i],1);
        }else{
            scanf("%d %d %d",&i,&j,&v);
            int sum = 0;
            for(int k=i/e*e+e;k<=j;k+=e){
                sum += get_sum(i,k,v);
                i=k+1;
            }
            sum += get_sum(i,j,v);
            printf("%d\n",sum);
        }
    }
    return 0;
}
