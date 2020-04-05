#include<bits/stdc++.h>
#define MAX_N 10005
#define MAX_M 105
#define MAX_L 15005
#define fi first
#define se second
#define eb emplace_back
using namespace std;
typedef pair<int,int> pii;
int n;
int main(){
    freopen("input.txt","r",stdin);
    scanf("%d",&n);
    n -= 2;
    int ans = 0;
    for(int dep = 0, sum = 1;sum < n ; sum += 3 * (1<<dep), dep ++){
        ans = 2 * dep + 1;
        if(sum + (1<<dep) < n)  ans++;
    }
    printf("%d\n",ans);
    return 0;
}
