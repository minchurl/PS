#include<bits/stdc++.h>
#define MAX_N 1005
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pii;
priority_queue<int> pq;
pii arr[MAX_N];
int n,m,k,ans;
int main(){
	freopen("input.txt","r",stdin);
	int T,i;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&m);
		for(i=0;i<m;i++)	scanf("%d %d",&arr[i].fi,&arr[i].se);
		sort(arr,arr+m);
		ans=k=0;
		for(i=1;i<=n;i++){
			while(k<m && arr[k].fi<=i)	pq.push(-arr[k++].se);
			while(!pq.empty() && -pq.top()<i)	pq.pop();
			if(!pq.empty()){
				ans++;
				pq.pop();
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
