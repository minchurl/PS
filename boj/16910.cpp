#include<bits/stdc++.h>
#define MAX_N 100005
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))
#define fi first
#define se second
#define inf 0x3fffffff
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
//#define inf 0x3fffffff
#define MOD 1000000007LL
#define cpx_mod(x) (((LD)(((LL)x.real())%MOD)),((LD)(((LL)x.imag())%MOD)))
#define prev(x) (((x)+n-1)%n)
#define next(x) (((x)+1)%n)
#define mod(x) (((x)%h + h)%h)
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
struct node{
	int v;
	int l,r;
};
vector<node> tree;
void meet(int x,int v){
	if(v == -1)	return;
	if(v < 2){
		tree[x].v = v;
	}else{
		tree[x].v = 1 - tree[x].v;
	}
}
int add(int x,int v){
	if(!x){
		tree.pb({0,0,0});
		x = (int)tree.size() - 1;
	}
	meet(x, v);
	return x;
}
void spread(int x){
	int i;
	i = add(tree[x].l, tree[x].v); tree[x].l = i;
	i = add(tree[x].r, tree[x].v); tree[x].r = i;
	tree[x].v = (tree[tree[x].l].v == tree[tree[x].r].v)?tree[tree[x].l].v:-1;
}
void update(int idx, int x, LL l,LL r, int v){
	if(l > r)	return;
	spread(x);
	if(r - l + 1LL == (1LL<<((LL)idx + 1LL))){
		meet(x,v);
		return;
	}
	LL mid = (l&((1LL<<62LL) - (1LL<<((LL)idx + 1LL))))|(1LL<<(LL)idx);
	update(idx - 1,tree[x].l,l,min(mid-1LL,r),v);
	update(idx - 1,tree[x].r,max(mid,l),r,v);
	tree[x].v = (tree[tree[x].l].v == tree[tree[x].r].v)?tree[tree[x].l].v:-1;
}
LL read(int idx,int x){
	if(idx == -1)	return 0;
	spread(x);
	if(tree[x].v == 0)	return 0;
	if(tree[tree[x].l].v != 1)	return read(idx - 1,tree[x].l);
	return read(idx - 1,tree[x].r)|(1LL<<(LL)idx);
}
int main(){
	freopen("input.txt","r",stdin);
	int q,z;
	LL l,r;
	scanf("%d",&q);
	tree.pb({0,0,0});
	update(60,0,0LL,0LL,1);
	while(q--){
		scanf("%d %lld %lld",&z,&l,&r);
		if(z == 2)	z = 0;
		else if(z == 3)	z = 2;
		update(60,0,l,r,z);
		printf("%d %lld\n",q,read(60,0));
	}
	return 0;
}