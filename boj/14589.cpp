#include<bits/stdc++.h>
#define MAX_N 150005
#define fi first
#define se second
using namespace std;
struct node{
	int s,e,idx;
}arr[MAX_N];
int n,q,pa[25][MAX_N];
priority_queue<pair<int,int>> pq;
void make_pa(){
	for(int i=1;i<=20;i++){
		for(int j=1;j<=n;j++)	pa[i][j]=pa[i-1][pa[i-1][j]];
	}
}
int get_ans(int s,int e){
	if(arr[s].s>arr[e].s)	swap(s,e);
	if(arr[pa[20][s]].e<arr[e].s)	return -1;
	int ans=0;
	for(int i=20;i>=0;i--){
		if(arr[pa[i][s]].e<arr[e].s){
			ans+=(1<<i);
			s=pa[i][s];
		}
	}
	return ans+2;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y,e;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d %d",&arr[i].s,&arr[i].e);
		arr[i].idx=i;
	}
	sort(arr+1,arr+n+1,[&](const node x,const node y){
		if(x.s==y.s)	return x.e>y.e;
		return x.s<y.s;
	});
	arr[0].e=-1000005;
	e=1;
	for(i=1;i<=n;i++){
		while(!pq.empty() && arr[i].s>-pq.top().fi){pa[0][arr[pq.top().se].idx]=arr[e].idx;pq.pop();}
		pq.push({-arr[i].e,i});
		if(arr[i].e>arr[e].e)	e=i;
	}
	while(!pq.empty()){pa[0][arr[pq.top().se].idx]=arr[e].idx;pq.pop();}
	sort(arr+1,arr+n+1,[&](const node x,const node y){
		return x.idx<y.idx;
	});
	scanf("%d",&q);
	make_pa();
	while(q--){
		scanf("%d %d",&x,&y);
		if(arr[x].s>arr[y].e || arr[x].e<arr[y].s)	printf("%d\n",get_ans(x,y));
		else	printf("1\n");
	}
	return 0;
}
