#include<bits/stdc++.h>
#define MAX_N 100005
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end()
#define fi first
#define se second
using namespace std;
int n;
int val[MAX_N];
vector<int> tree[4*MAX_N];
void update(int x,int l,int r){
	if(l == r){
		tree[x].eb(val[l]);
		return ;
	}
	
	int mid = (l + r) >> 1;
	
	update(2*x,l,mid);
	update(2*x+1,mid+1,r);
	
	int p, q;
	p = q = 0;
	
	while(p < tree[2*x].size() || q < tree[2*x+1].size()){
		if(q == tree[2*x+1].size() || (p != tree[2*x].size() && tree[2*x][p]<tree[2*x+1][q])){
			tree[x].eb(tree[2*x][p]);
			p++;
		}else{
			tree[x].eb(tree[2*x+1][q]);
			q++;
		}
	}
	
	return ;
	
}
int read(int x,int l,int r,int s,int e,int v){
	if(e<l || r<s){
		return 0;
	}
	if(s<=l && r<=e){
		int y = upper_bound(all(tree[x]),v)-tree[x].begin();
		if(tree[x][y] == v)	y++;
		return tree[x].size() - y;
	}
		
	int mid = (l + r) >> 1;
	
	return read(2*x,l,mid,s,e,v) + read(2*x+1,mid+1,r,s,e,v);
}
int main(){
	freopen("input.txt","r",stdin);
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&val[i]);
	}
	update(1,1,n);
	
	int q;
	int x = 0;
	scanf("%d",&q);
	while(q--){
		int s,e,v;
		scanf("%d %d %d",&s,&e,&v);
		x=read(1,1,n,s^x,e^x,v^x);
		printf("%d\n",x);
	}
	
	return 0;
}
