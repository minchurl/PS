#include<bits/stdc++.h>
#define MAX_N 100005
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
#define inf 0x3fffffff
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
int n,m,k;
int mx[MAX_N],mn[MAX_N],sum[MAX_N],idx[MAX_N];
bool chk[MAX_N];
vector<pii> lst;
vector<int> ans;
int read(int x){for(;x>0;x-=(x&-x))if(mn[x])return true;return false;}
void update(int x){for(;x<=n;x+=(x&-x)){mn[x]++;}}
int main(){
	int i,x,y,z;
	scanf("%d %d %d",&n,&k,&m);
	for(i=0;i<m;i++){
		scanf("%d %d %d",&x,&y,&z);
		if(z==0)	mx[x]=max(mx[x],y);
		else	lst.pb({x,y});
	}
	x=y=0;
	for(i=1;i<=n;i++){
		x=max(x,mx[i]);
		sum[i]=sum[i-1]+(x>=i?1:0);
		if(x<i)	idx[++y]=i;
	}
	for(pii &p:lst){
		p={p.fi-sum[p.fi-1],p.se-sum[p.se]};
		if(p.fi>p.se)	return !printf("-1\n");
	}
	if(k==n-sum[n]){
		if(k==0)	return !printf("-1\n");
		for(i=1;i<=n;i++)	if(sum[i]-sum[i-1]==0)	printf("%d\n",i);
		return 0;
	}
	sort(all(lst),[&](const pii x,const pii y){return (x.fi==y.fi)?(x.se<y.se):(x.fi>y.fi);});
	m=0;
	int sz=lst.size();
	for(i=0;i<sz;i++){
		if(!read(lst[i].se))	lst[m++]=lst[i];
		update(lst[i].se);
	}
	lst.resize(m);
	sort(all(lst));
	n-=sum[n];
	x=y=0;
	pil s,e;
	for(pii p:lst){
		if(p.fi<=x && p.se>=x){
			e=p;
			continue;
		}
		else{
			if(x && s.se==e.fi)	chk[s.se]=true;
			s=e=p;
			x=p.se;
			y++;
		}
	}
	if(x && s.se==e.fi)	chk[s.se]=true;
	if(y>k)	return !printf("-1\n");
	sort(all(lst),[&](const pii x,const pii y){return x.fi>y.fi;});
	x=n+1;
	for(pii p:lst){
		if(p.fi<=x && p.se>=x){
			e=p;
			continue;
		}
		else{
			if(x!=n+1 && s.fi==e.se)if(chk[s.fi])ans.pb(s.fi);
			x=p.fi;
			s=e=p;
		}
	}
	if(x && s.fi==e.se)	if(chk[s.fi])	ans.pb(x);
	sort(all(ans));
	for(int p:ans)	printf("%d\n",idx[p]);
	if(!ans.size())	printf("-1\n");
	return 0;
}
