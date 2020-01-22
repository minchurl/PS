#include<bits/stdc++.h>
#define MAX_N 100005
#define inf (1LL<<60)
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pil;
struct node{
	LL cnt,sum;
	node *l,*r;
	node(LL cnt,LL sum,node *l,node *r):cnt(cnt),sum(sum),l(l),r(r){}
}*R1,*R2;
LL n,k,m;
LL ans,aa;
vector<LL> X;
pil arr[MAX_N];
pil serch(LL idx,node *x,LL cnt,LL p){
	if(idx<0 && p>=X.size())	return {0,0};
	if(idx<0)	return {X[p],X[p]*cnt};
	if(x->l->cnt<cnt){
		pil q=serch(idx-1,x->r,cnt-x->l->cnt,(p|(1LL<<idx)));
		q.se+=x->l->sum;
		return q;
	}
	return serch(idx-1,x->l,cnt,p);
}
LL read(node *RX){
	pil p=serch(17,RX,RX->cnt/2,0);
	return (RX->cnt/2)*p.fi-p.se+(RX->sum-p.se)-(RX->cnt-RX->cnt/2)*p.fi;
}
void make_tree(LL idx,node *RX){
	if(idx<0)	return;
	RX->l=new node(0,0,NULL,NULL);
	RX->r=new node(0,0,NULL,NULL);
	make_tree(idx-1,RX->l);make_tree(idx-1,RX->r);
}
void update(LL idx,node *RX,LL p,LL x){
	RX->cnt+=x;
	RX->sum+=x*X[p];
	if(idx<0)	return;
	if(p>>idx&(1LL))	update(idx-1,RX->r,p,x);
	else	update(idx-1,RX->l,p,x);
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,x;
	char a[5],b[5];
	scanf("%lld %lld",&k,&n);
	for(i=1;i<=n;i++){
		scanf("%s %lld %s %lld",a,&arr[m].fi,b,&arr[m].se);
		if(a[0]==b[0]){
			aa+=abs(arr[m].fi-arr[m].se);
			continue;
		}
		X.pb(arr[m].fi);X.pb(arr[m].se);
		m++;
		aa++;
	}
	sort(X.begin(),X.end());X.erase(unique(X.begin(),X.end()),X.end());
	sort(arr,arr+m,[&](const pil x,const pil y){
		return x.fi+x.se<y.fi+y.se;
	});
	R1=new node(0,0,NULL,NULL);make_tree(17,R1);
	R2=new node(0,0,NULL,NULL);make_tree(17,R2);
	for(i=0;i<m;i++){
		update(17,R2,(lower_bound(X.begin(),X.end(),arr[i].fi)-X.begin()),1);
		update(17,R2,(lower_bound(X.begin(),X.end(),arr[i].se)-X.begin()),1);
	}
	ans=read(R2);
	if(k==1)	return !printf("%lld\n",aa+ans);
	for(i=0;i<m;i++){
		update(17,R1,(lower_bound(X.begin(),X.end(),arr[i].fi)-X.begin()),1);
		update(17,R1,(lower_bound(X.begin(),X.end(),arr[i].se)-X.begin()),1);
		update(17,R2,(lower_bound(X.begin(),X.end(),arr[i].fi)-X.begin()),-1);
		update(17,R2,(lower_bound(X.begin(),X.end(),arr[i].se)-X.begin()),-1);
		x=read(R1)+read(R2);
		ans=min(ans,x);
	}
	printf("%lld\n",aa+ans);
	return 0;
}
