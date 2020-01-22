#include<bits/stdc++.h>
#define MAX_N 1000000005
#define MAX_M 100005
#define pb push_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))
#define fi first
#define se second
#define LL_inf (1LL<<60)
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
#define inf (1LL<<50)
#define MOD 1000000007LL
#define cpx_mod(x) (((LD)(((LL)x.real())%MOD)),((LD)(((LL)x.imag())%MOD)))
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
typedef long double LD;
struct node{
	LL v;
	int l,r;
};
struct seg_tree{
	node tree[32*MAX_M];
	int tn;
	seg_tree(){
		for(int i=0;i<32*MAX_M;i++)	tree[i]={inf,0,0};
		tn=1;
	}
	void update(int x,int l,int r,int p,LL v){
		tree[x].v=min(tree[x].v,v);
		if(l==r)	return;
		int mid=(l+r)>>1;
		if(p<=mid)	update(tree[x].l?tree[x].l:(tree[x].l=++tn),l,mid,p,v);
		else	update(tree[x].r?tree[x].r:(tree[x].r=++tn),mid+1,r,p,v);
	}
	LL read(int x,int l,int r,int s,int e){
		if(e<l || s>r)	return inf;
		if(s<=l && r<=e)	return tree[x].v;
		int mid=(l+r)>>1;
		LL p,q;p=q=inf;
		if(tree[x].l)	p=read(tree[x].l,l,mid,s,e);
		if(tree[x].r)	q=read(tree[x].r,mid+1,r,s,e);
		return min(p,q);
	}
}L,R;
int n,m;
LL ans;
int main(){
	int i,l,c,r;
	LL p,q,v;
	scanf("%d %d",&m,&n);
	ans=inf;
	for(i=0;i<m;i++){
		scanf("%d %d %d %lld",&l,&r,&c,&v);
		p=L.read(1,1,n,l,r);if(l==1)	p=0;
		q=R.read(1,1,n,l,r);if(r==n)	q=0;
		ans=min(ans,p+q+v);
		L.update(1,1,n,c,p+v);R.update(1,1,n,c,q+v);
	}
	printf("%lld\n",(ans==inf)?-1:ans);
	return 0;
}
