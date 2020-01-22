#include<bits/stdc++.h>
#define prime (2147483647LL)
#define LL long long
#define pb push_back
using namespace std;
struct node{
	LL x,s;
	bool operator < (node d) const{
		return x<d.x;
	};
};
LL n,H[30];
char s[200005];
vector<node> lst;
bool is_ok(LL l){
	LL i,x=0,y=1;
	node p;
	if(!l)	return true;
	lst.resize(0);
	for(i=0;i<l;i++){x=(x*26+H[s[i]-'a'])%prime;y*=26;y%=prime;}
	p.x=x;p.s=0;
	lst.pb(p);
	for(i=1;i<=n-l;i++){
		x*=26;
		x%=prime;
		x-=(y*H[s[i-1]-'a'])%prime;x+=prime;x%=prime;
		x+=H[s[i+l-1]-'a'];x%=prime;
		p.x=x;p.s=i;
		lst.pb(p);
	}
	sort(lst.begin(),lst.end());
	LL sz=lst.size(),j,k,h;
	for(i=0;i<sz;i++){
		x=i;
		while(i!=sz && lst[i].x==lst[i+1].x)	i++;
		if(x==i)	continue;
		for(j=x;j<=i;j++){
			for(k=j+1;k<=i;k++){
				y=0;
				while(y!=l && s[lst[j].s+y]==s[lst[k].s+y]){
					y++;
				}
				if(y==l)	return true;
			}
		}
	}
	return false;
}
LL bin(){
	LL s,e,mid,x;
	s=1;
	e=n;
	while(s<=e){
		mid=(s+e)>>1;
		if(is_ok(mid)){
			if(!is_ok(mid+1))	return mid;
			s=mid+1;
		}else{
			if(is_ok(mid-1))	return mid-1;
			e=mid-1;
		}
	}
	return 0;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i;
	H[0]=1;
	for(i=1;i<26;i++)	H[i]=H[i-1]*26,H[i]%=prime;
	scanf("%lld",&n);
	scanf("%s",s);
	printf("%lld\n",bin());
	return 0;
}
