#include<bits/stdc++.h>
#define MAX_N 300005
#define pb push_back
typedef long long LL;
using namespace std;
struct node{
	LL l,r,c;
}con[MAX_N];
vector<int> loc[MAX_N],lst[MAX_N];
LL n,m,k,qut[MAX_N],st[MAX_N],en[MAX_N],t[MAX_N];
void init(){
	for(LL i=1;i<=m;i++)	t[i]=0;
	for(LL i=1;i<=k;i++)	lst[i].resize(0);
}
void update(LL x,LL y){for(;x<=m;x+=(x&-x))t[x]+=y;}
LL get_val(LL x){LL sum=0;for(;x>0;x-=(x&-x))sum+=t[x];return sum;}
void add(LL l,LL r,LL val){update(l,val);update(r+1,-val);}
LL get_sum(LL x,LL lim){
	LL sz=loc[x].size(),sum=0;
	while(sz--){
		sum+=get_val(loc[x][sz]);
		if(sum>=lim)	return true;
	}
	return false;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,idx,x;
	scanf("%lld %lld",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%lld",&x);
		loc[x].pb(i);
	}
	for(i=1;i<=n;i++)	scanf("%lld",&qut[i]);
	scanf("%lld",&k);
	for(i=1;i<=k;i++)	scanf("%lld %lld %lld",&con[i].l,&con[i].r,&con[i].c);
	for(i=1;i<=n;i++){st[i]=1;en[i]=k+1;}
	bool z=true;
	while(z){
		z=false;
		init();
		for(i=1;i<=n;i++){
			if(st[i]<en[i])	lst[(st[i]+en[i])>>1].pb(i);
		}
		for(i=1;i<=k;i++){
			if(con[i].l<=con[i].r)	add(con[i].l,con[i].r,con[i].c);
			else{add(con[i].l,m,con[i].c);add(1,con[i].r,con[i].c);}
			while(lst[i].size()){
				z=true;
				idx=lst[i].back();lst[i].pop_back();
				if(get_sum(idx,qut[idx]))	en[idx]=i;
				else	st[idx]=i+1;
			}
		}
	}
	for(i=1;i<=n;i++){
		if(st[i]==k+1)	printf("NIE\n");
		else	printf("%lld\n",st[i]);
	}
	return 0;
}
