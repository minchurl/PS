#include<bits/stdc++.h>
#define MAX_N 100005
using namespace std;
typedef long long LL;
struct pst{
	LL cnt,sum;
	pst *l,*r;
	pst(LL cnt,LL sum,pst *l,pst *r):cnt(cnt),sum(sum),l(l),r(r){}
}*tree;
LL n,st,d,dx,ans;
LL s_t[3*MAX_N],s_tt[3*MAX_N],e_t[3*MAX_N],e_tt[3*MAX_N],arr[MAX_N];
vector<LL> X;
void add(pst *a,LL x,LL v){
	a->cnt+=v;
	a->sum+=x*v;
}
void update(LL idx,pst *a,LL p,LL x,LL v){
	add(a,x,v);
	if(idx<0)	return;
	if(p>>idx&1)	update(idx-1,a->r,p,x,v);
	else	update(idx-1,a->l,p,x,v);
	return;
}
LL get_sum(LL idx,pst *a,LL x,LL p){
	if(x<=0)	return 0;
	if(idx<0)	return min(x,a->cnt)*X[p];
	if(a->cnt==p)	return a->sum;
	return get_sum(idx-1,a->r,min(x,a->r->cnt),p|(1LL<<idx))+get_sum(idx-1,a->l,x-min(x,a->r->cnt),p);
}
void dnc(LL s,LL e,LL l,LL r,bool p,bool q){
	LL mid=(l+r)>>1;
	LL i,di=s,dix=-1;
	LL x,y;
	if(l>r)	return;
	i=p?s:e;
	while(s<=i && i<=e){
		update(16,tree,arr[i],X[arr[i]],1);
		y=q?2*abs(st-i):abs(st-i);
		if(mid-y<0){
			i+=p?1:-1;
			continue;
		}
		x=get_sum(16,tree,mid-y,0);
		if(x>dix){
			dix=x;
			di=i;
		}
		i+=p?1:-1;
	}
	if(q){
		if(p)	e_tt[mid]=max(e_tt[mid],dix);
		else	s_tt[mid]=max(s_tt[mid],dix);
	}else{
		if(p)	e_t[mid]=max(e_t[mid],dix);
		else	s_t[mid]=max(s_t[mid],dix);
	}
	if(p){
		for(i=di;i<=e;i++)	update(16,tree,arr[i],X[arr[i]],-1);
		dnc(di,e,mid+1,r,p,q);
		for(i=s;i<di;i++)	update(16,tree,arr[i],X[arr[i]],-1);
		dnc(s,di,l,mid-1,p,q);
	}
	else{
		for(i=s;i<=di;i++)	update(16,tree,arr[i],X[arr[i]],-1);
		dnc(s,di,l,mid-1,p,q);
		for(i=di+1;i<=e;i++)	update(16,tree,arr[i],X[arr[i]],-1);
		dnc(di,e,mid+1,r,p,q);
	}
}
void make_tree(LL idx,pst *a){	
	if(idx<0)	return;
	a->l=new pst(0,0,NULL,NULL);
	a->r=new pst(0,0,NULL,NULL);
	make_tree(idx-1,a->l);make_tree(idx-1,a->r);
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,x;
	scanf("%lld %lld %lld",&n,&st,&d);
	tree=new pst(0,0,NULL,NULL);
	make_tree(16,tree);
	for(i=1;i<=n;i++){
		scanf("%lld",&arr[i]);
		X.push_back(arr[i]);
		if(i==st)	dx=arr[i];
	}
	sort(X.begin(),X.end());X.erase(unique(X.begin(),X.end()),X.end());
	for(i=1;i<=n;i++){
		x=lower_bound(X.begin(),X.end(),arr[i])-X.begin();
		arr[i]=x;
	}
	dnc(1,st-1,0,d,false,true);
	dnc(st+1,n,0,d,true,true);
	dnc(1,st-1,0,d,false,false);
	dnc(st+1,n,0,d,true,false);
	ans=max(max(s_t[d-1]+dx,s_t[d]),max(e_t[d-1]+dx,e_t[d]));
	for(i=0;i<=d;i++){
		ans=max(ans,max(s_t[i]+e_tt[d-i],s_tt[i]+e_t[d-i]));
		if(i!=d)	ans=max(ans,max(s_t[i]+e_tt[d-i-1],s_tt[i]+e_t[d-i-1])+dx);
	}
	printf("%lld\n",ans);
	return 0;
}
