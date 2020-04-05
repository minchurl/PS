#include<bits/stdc++.h>
#define MAX_N 10005
#define MAX_M 105
#define MAX_L 15005
#define fi first
#define se second
#define eb emplace_back
using namespace std;
typedef pair<int,int> pii;
int n,m;
int val[MAX_M],t[MAX_L];
vector<pii> lst[MAX_L];
int main(){
    freopen("input.txt","r",stdin);
    int i,s,e,x;
    scanf("%d %d",&m,&n);
    for(i=1;i<=m;i++){
        scanf("%d",&val[i]);
    }
    for(i=1;i<=n;i++){
        scanf("%d %d %d",&s,&e,&x);
        lst[e].eb(s,val[x] * (e-s));
    }
    for(i=1;i<=15000;i++){
        t[i] = t[i - 1];
        for(pii p:lst[i]){
            t[i] = max(t[i], t[p.fi] + p.se);
        }
    }
    printf("%d\n",t[15000]); 
    return 0;
}
