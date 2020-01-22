#include<bits/stdc++.h>
#define MAX_N 3005
#define H1 1000000007LL
#define H2 1000000009LL
#define pb push_back
using namespace std;
typedef long long LL;
LL ans[MAX_N];
char s[MAX_N];
vector<LL> v[MAX_N];
void cap(LL x){
	v[x].pb(1);
	ans[x]=0;
	sort(v[x].begin(),v[x].end());
	for(LL y:v[x])	ans[x]=ans[x]*H2+y;
}
LL get_num(LL x,LL pa){
	LL y=x+1;
	while(s[y]=='0')	y=get_num(y,x)+1;
	cap(x);
	v[pa].pb(ans[x]*H1);
	return y;
}
int main(){
	freopen("input.txt","r",stdin);
	LL T,x,i,len,j;
	scanf("%lld",&T);
	while(T--){
		for(i=0;i<=3004;i++){v[i].clear();v[i].resize(0);}
		scanf("%s",s);
		len=strlen(s);
		for(i=len;i>0;i--)	s[i]=s[i-1];
		x=1;
		while(x<=len)	x=get_num(x,0)+1;
		cap(0);
		j=ans[0];		
		for(i=0;i<=3004;i++){v[i].clear();v[i].resize(0);}
		scanf("%s",s);
		for(i=len;i>0;i--)	s[i]=s[i-1];
		x=1;
		while(x<=len)	x=get_num(x,0)+1;
		cap(0);
		printf("%lld\n",(LL)(j==ans[0]?1:0));
	}
	return 0;
}
