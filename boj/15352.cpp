#include<bits/stdc++.h>
#define MAX_N 1000005
#define LL long long
using namespace std;
struct node{
	LL l,r,x;
}arr[MAX_N];
LL n,k;
LL num[MAX_N],h[MAX_N],pa[MAX_N],ans;
LL find_pa(LL x){return pa[x]?find_pa(pa[x]):x;}
void delect(LL x){
	arr[arr[x].l].r=arr[x].r;
	arr[arr[x].r].l=arr[x].l;
	num[find_pa(x)]--;
}
void connect(LL x,LL y){
	LL px,py;
	px=find_pa(x);py=find_pa(y);
	if(px==py)	return;
	if(h[px]==h[py])	h[px]++;
	if(h[px]>h[py]){pa[py]=px;num[px]+=num[py];}
	else{pa[px]=py;num[py]+=num[px];}
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,q,a,x;
	scanf("%lld %lld",&k,&n);
	for(i=1;i<=n;i++){
		scanf("%lld",&arr[i].x);
		arr[i].l=i-1;arr[i].r=i+1;
		h[i]=num[i]=1;
	}
	for(i=1;i<n;i++){
		if(arr[i].x==arr[i+1].x)	connect(i,i+1);
	}
	scanf("%lld",&q);
	while(q--){
		scanf("%lld %lld",&a,&x);
		if(a==1){
			delect(x);
			if(arr[arr[x].l].x==arr[arr[x].r].x)	connect(arr[x].l,arr[x].r);
		}else	ans+=num[find_pa(x)];
	}
	printf("%lld\n",ans);
	return 0;
}
