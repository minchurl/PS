#include<bits/stdc++.h>
#define H 1000000007
#define all(v) (v).begin(),(v).end()
using namespace std;
typedef long long LL;
struct node{
	LL i,c,l;
};
LL h[27];
vector<node> lst;
void solve(LL idx){
	LL n;
	char s[1505];
	scanf("%s",s);n=strlen(s);
	for(LL i=0;i<n;i++){
		LL x=0;
		for(LL j=i;j<n;j++){
			x+=h[s[j]-'a'];
			lst.push_back({x,idx,j-i+1});
		}
	}
}
int main(){
	LL ans=0;
	h[0]=1;
	for(LL i=1;i<26;i++)	h[i]=h[i-1]*H;
	solve(0);
	solve(1);
	sort(all(lst),[&](const node x,const node y){return (x.i==y.i)?(x.c<y.c):(x.i<y.i);});
	LL sz=lst.size();
	for(LL i=1;i<sz;i++){
		if(lst[i].i==lst[i-1].i && lst[i].c!=lst[i-1].c)	ans=max(ans,lst[i].l);
	}
	printf("%lld\n",ans);
	return 0;
}
