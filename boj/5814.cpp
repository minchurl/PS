#include<bits/stdc++.h>
#include<inttypes.h>//__int64,__int128..
#define MAX_N 100005
//vector&pair
#define pb push_back
#define mp make_pair
//math
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))//Regardless of type
//for pair
#define fi first
#define se second
//infinit
#define LL_inf (1LL<<60)
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
//MOD
#define MOD 1000000007LL
using namespace std;
//type
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef long double LD;
struct node{
	int s,e,dep,can;
}arr[MAX_N];
int n,c,R,tree[4*MAX_N],idx_tree[4*MAX_N],ans,ansn;
void update(int x,int l,int r,int p,int ch){
	int mid=(l+r)/2;
	tree[x]=max(tree[x],ch);
	if(l==r)	return;
	if(p<=mid)	update(x*2,l,mid,p,ch);
	else	update(x*2+1,mid+1,r,p,ch);
}
void idx_update(int x,int l,int r,int p,int ch){
	int mid=(l+r)/2;
	idx_tree[x]+=ch;
	if(l==r)	return;
	if(p<=mid)	idx_update(x*2,l,mid,p,ch);
	else	idx_update(x*2+1,mid+1,r,p,ch);
}
int read(int x,int l,int r,int s,int e){
	if(r<s || l>e)	return 0;
	if(l>=s && r<=e)	return tree[x];
	int mid=(l+r)/2;
	int u=read(x*2,l,mid,s,e),t=read(x*2+1,mid+1,r,s,e);
	return max(u,t);
}
int idx_read(int x,int l,int r,int p){
	if(l==r)	return l;
	int mid=(l+r)/2;
	if(idx_tree[x*2]<p)	return idx_read(x*2+1,mid+1,r,p-idx_tree[x*2]);
	else	return idx_read(x*2,l,mid,p);
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,s,e,idx;
	scanf("%d %d %d",&n,&c,&R);
	for(i=1;i<n;i++){
		scanf("%d",&x);
		update(1,1,n-1,i,x);
	}
	for(i=0;i<n;i++){
		arr[i].s=arr[i].e=arr[i].can=i;
		arr[i].dep=0;
		idx_update(1,0,n-1,i,1);
	}
	ansn=0;
	while(c--){
		scanf("%d %d",&s,&e);
		idx=idx_read(1,0,n-1,s+1);
		x=arr[idx].e+1;
		while(s-e){
			if(arr[idx].dep<arr[x].dep){
				arr[idx].dep=arr[x].dep;
				arr[idx].can=arr[x].can;
			}
			arr[idx].e=arr[x].e;
			idx_update(1,0,n-1,x,-1);
			x=arr[x].e+1;
			s++;
		}
		arr[idx].dep++;
		x=read(1,1,n-1,arr[idx].s+1,arr[idx].e);
		if(x<R){
			if(ans==arr[idx].dep)	ansn=min(ansn,arr[idx].can);
			else if(ans<arr[idx].dep){
				ans=arr[idx].dep;
				ansn=arr[idx].can;
			}
		}
	}
	printf("%d\n",ansn);
	return 0;
}
