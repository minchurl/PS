#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
#define inf (1LL<<60)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pil;
struct lichao_tree{
	struct node{
		LL l,r;
		pil L;
	};
	vector<node> tree;
	LL get_val(pil L,LL x){return L.fi*x+L.se;}
	inline LL get_idx(LL x){
		if(x!=-1)	return x;
		tree.pb({-1,-1,{0,-inf}});
		return tree.size()-1;
	}
	void update(LL x,pil llow,LL s,LL e){
		pil lhigh = tree[x].L;
		LL mid = (s+e)>>1,y;
		if(get_val(lhigh,s)<=get_val(llow,s))	swap(llow,lhigh);
		tree[x].L=(get_val(lhigh,mid)>=get_val(llow,mid))?lhigh:llow;
		if(s==e || get_val(lhigh,e)>=get_val(llow,e))	return;
		y=get_idx(tree[x].l);tree[x].l=y;
		y=get_idx(tree[x].r);tree[x].r=y;
		if(get_val(lhigh,mid)>=get_val(llow,mid))	update(tree[x].r,llow,mid+1,e);
		else	update(tree[x].l,lhigh,s,mid);
		
	}
	LL get_mx(LL x,LL p,LL s,LL e){
		if(x==-1)	return -inf;
		if(s==e)	return get_val(tree[x].L,p);
		LL mid=(s+e)>>1;
		LL y=(p<=mid)?get_mx(tree[x].l,p,s,mid):get_mx(tree[x].r,p,mid+1,e);
		return max(get_val(tree[x].L,p),y);
	}
}litree;
int main(){
	LL q,x,y,z;
	litree.get_idx(-1);
	scanf("%lld",&q);
	while(q--){
		scanf("%lld",&z);
		if(z==1){
			scanf("%lld %lld",&x,&y);
			litree.update(0,{x,y},-1e12,1e12);
		}else{
			scanf("%lld",&x);
			printf("%lld\n",litree.get_mx(0,x,-1e12,1e12));
		}
	}
	return 0;
}
