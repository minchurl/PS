#include<bits/stdc++.h>
#define MAX_N 100005
#define pb push_back
using namespace std;
struct node{
	int val;
	node *l,*r;
	node(int val,node *l,node *r):val(val),l(l),r(r){}
	node *update(int idx,int p){
		if(idx<0)	return new node(val+1,NULL,NULL);
		if(p>>idx&1)	return new node(val+1,l,r->update(idx-1,p));
		return new node(val+1,l->update(idx-1,p),r);
	}
}*tree[MAX_N];
vector<int> X;
int n,m,arr[MAX_N];
int kthQ(int idx,node *L,node *R,int num){
	if(idx<0)	return 0;
	if(num>(R->l->val-L->l->val))	return (1<<idx)|kthQ(idx-1,L->r,R->r,num-(R->l->val-L->l->val));
	return kthQ(idx-1,L->l,R->l,num);
}
int main(){
	freopen("input.txt","r",stdin);
	int x,i,j,k;
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",&arr[i]);
		X.pb(arr[i]);
	}
	sort(X.begin(),X.end());
	X.erase(unique(X.begin(),X.end()),X.end());
	tree[0]=new node(0,NULL,NULL);
	tree[0]->l=tree[0]->r=tree[0];
	for(i=1;i<=n;i++){
		x=lower_bound(X.begin(),X.end(),arr[i])-X.begin();
		tree[i]=tree[i-1]->update(18,x);
	}
	while(m--){
		scanf("%d %d %d",&i,&j,&k);
		printf("%d\n",X[kthQ(18,tree[i-1],tree[j],k)]);
	}
	return 0;
}
