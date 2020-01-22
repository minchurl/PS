#include<bits/stdc++.h>
#define MAX_N 250005
#define M (1<<19)
#define pb push_back
using namespace std;
struct range{
	int s,e;
}num[MAX_N];
int n,pa[MAX_N],cnt;
int tree[4*M];
vector<int> net[MAX_N];
void dfs(int x){
	int y,sz=net[x].size();
	num[x].s=num[x].e=M+cnt;cnt++;
	while(sz--){
		y=net[x][sz];
		if(pa[y])	continue;
		pa[y]=x;
		tree[M+cnt]=tree[num[x].s]+1;
		dfs(y);
	}
	num[x].e=M+cnt-1;
}
void update(int x,int s,int e,int l,int r){
	if(s==l && e==r){
		tree[x]--;
		return;
	}
	int mid=(l+r)/2;
	if(e<=mid)	update(x*2,s,e,l,mid);
	else if(s>mid)	update(x*2+1,s,e,mid+1,r);
	else{
		update(x*2,s,mid,l,mid);
		update(x*2+1,mid+1,e,mid+1,r);
	}
}
int read(int x){
	return x?tree[x]+read(x/2):0;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y,q;
	scanf("%d",&n);
	for(i=1;i<n;i++){
		scanf("%d %d",&x,&y);
		net[x].pb(y);net[y].pb(x);
	}
	pa[1]=-1;
	dfs(1);
	scanf("%d",&q);i=n-1;
	char st[5];
	while(q|i){
		scanf("%s",st);
		if(st[0]=='W'){
			scanf("%d",&x);
			printf("%d\n",read(num[x].s));q--;
		}else{
			scanf("%d %d",&x,&y);
			if(pa[y]==x)	swap(x,y);
			update(1,num[x].s-M,num[x].e-M,0,M-1);i--;
		}
	}
	return 0;
}
