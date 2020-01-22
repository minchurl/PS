#include<bits/stdc++.h>
#define MAX_N 1000005
#define abs(x) ((x)>0?(x):(-(x)))
#define all(v) (v).begin(),(v).end()
#define pb push_back
#define inf (1LL<<60)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pil;
LL n,ans;
priority_queue<LL> pq;
int main(){
	LL TC,i,x,y;
	scanf("%lld",&TC);
	while(TC--){
		scanf("%lld",&n);
		while(pq.size())	pq.pop();
		for(i=1;i<=n;i++){
			scanf("%lld",&x);
			pq.push(-x);
		}
		ans=0;
		while(pq.size()>=2){
			x=pq.top();pq.pop();
			y=pq.top();pq.pop();
			ans+=-x-y;
			pq.push(x+y);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
