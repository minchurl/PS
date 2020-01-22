#include<bits/stdc++.h>
#define MAX_N 1000005
using namespace std;
int n,d[MAX_N];
struct node{
	int x,cost;
};
deque<node> dq;
int main(){
	freopen("input.txt","r",stdin);
	int i,j,k,Q;
	node p,q;
	scanf("%d",&n);
	for(i=1;i<=n;i++)	scanf("%d",&d[i]);
	scanf("%d",&Q);
	for(i=1;i<=Q;i++){
		while(!dq.empty())	dq.pop_front();
		scanf("%d",&k);
		p.x=1;p.cost=0;
		dq.push_front(p);
		for(j=2;j<=n;j++){
			while(!dq.empty()){
				p=dq.front();
				if(p.x>=j-k)	break;
				dq.pop_front();
			}
			p.cost+=(d[p.x]>d[j]?0:1);
			p.x=j;
			q=dq.front();
			if(q.cost==p.cost && d[q.x]<=d[p.x]){
				dq.push_front(p);
				continue;
			}
			while(!dq.empty()){
				q=dq.back();
				if(q.cost>p.cost || (q.cost==p.cost && d[q.x]<=d[p.x]))	dq.pop_back();
				else	break;
			}
			dq.push_back(p);
		}
		printf("%d\n",p.cost);
	}
	return 0;
}
