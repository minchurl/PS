#include<bits/stdc++.h>
#define pb push_back
#define MAX_N 100005
#define all(v) (v).begin(),(v).end()
using namespace std;
typedef long long LL;
LL n,ans;
vector<LL> lst[MAX_N];
int main(){
	LL i,j,x,y;
	scanf("%lld",&n);
	for(i=0;i<n;i++){
		scanf("%lld %lld",&x,&y);
		lst[y].pb(x);
	}
	for(i=1;i<=n;i++){
		sort(all(lst[i]));
		LL sz=lst[i].size();
		if(sz<2)	continue;
		ans+=lst[i][1]-lst[i][0]+lst[i][sz-1]-lst[i][sz-2];
		for(j=1;j<sz-1;j++)	ans+=min(lst[i][j]-lst[i][j-1],lst[i][j+1]-lst[i][j]);
	}
	printf("%lld\n",ans);
	return 0;
}
