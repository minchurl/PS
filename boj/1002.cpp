// #include<stdio.h>
// #define sq(x) ((x)*(x))
// int main(){
// int t,a,b,p,c,d,q;
//     scanf("%d",&t);
//     while(t--){
//         scanf("%d %d %d %d %d %d",&a,&b,&p,&c,&d,&q);
//         if(a==c && b==d){printf("%d\n",(p==q)?-1:0);continue;}
//         int x=sq(a-c)+sq(b-d);
//         int y=sq(p+q);
//         int z=sq(p-q);
//         if(x<z || x>y){
//         	printf("0\n");
//         	continue;
//         }
//         if(x==z || x==y)	printf("1\n");
//         else	printf("2\n");
//     }
//     return 0;
// }


#include<bits/stdc++.h>
#define MAX_N 300005
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end()
#define MOD 1000000007LL
using namespace std;
typedef long long LL;
LL n,k,deg[MAX_N];
LL f[MAX_N];
LL ans;
vector<LL> adj[MAX_N];
vector<LL> arr[2];
int main(){
    LL p;
    LL u,v;
    LL i;
    freopen("input.txt","r",stdin);
    scanf("%lld %lld %lld",&n, &k, &p);
    f[0] = 1LL;
    for(i=1;i<k;i++){
        f[i] = (f[i - 1] * n)%MOD;
    }
    while(p--){
        scanf("%lld %lld",&u, &v);
        adj[u].eb(v);
    }
    for(u=0;u<k;u++){
        arr[0].eb(u);
        arr[1].eb(u);
        sort(all(adj[u]));
    }
    sort(all(arr[0]),[&](const LL x, const LL y){
        if(binary_search(all(adj[y]),x))    return true;
        else if(binary_search(all(adj[x]),y))   return false;
        else    return x > y;        
    });

    sort(all(arr[1]),[&](const LL x, const LL y){
        if(binary_search(all(adj[y]),x))    return true;
        else if(binary_search(all(adj[x]),y))   return false;
        else    return x < y;        
    });

    for(i=0;i<k;i++){
        ans = ((n - k - 1 + i) * f[arr[0][i]] + ans) % MOD;
        ans = (ans - (i * f[arr[1][i]]) % MOD + MOD) % MOD;

    }
    printf("%lld\n",ans);
    return 0;
}