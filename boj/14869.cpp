#include<bits/stdc++.h>
#define MAX_N 3005
#define mp make_pair
#define inf (1LL<<60)
#define fi first
#define se second
#define get_val(x) (t[(x).fi-S][(x).se]-sum[(x).se][(x).fi-S])
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pil;
LL n,m,S,E,T,mn,ans;
LL sum[MAX_N][MAX_N],t[MAX_N][MAX_N],no[MAX_N];
pil minx[MAX_N];
deque<pil> dq[MAX_N];
void add_reset(){mn=0;for(LL i=0;i<3;i++)minx[i]=mp(inf,0);}
void add(pil x){
	minx[mn++]=x;
	for(LL i=mn-2;i>=0;i--){
		if(minx[i+1].fi<minx[i].fi)	swap(minx[i],minx[i+1]);
		else	break;
	}
	mn=min(mn,3LL);
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,j,k,x;
	pil p;
	scanf("%lld %lld %lld %lld %lld",&n,&m,&S,&E,&T);
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			scanf("%lld",&x);
			sum[i][j]=sum[i][j-1]+x;
			t[j][i]=inf;
		}
	}
	ans=inf;
	for(i=1;i<=n;i++)	scanf("%lld",&no[i]);
	for(i=1;i<=m;i++){
		add_reset();
		for(j=1;j<=n;j++){
			if(i-S<0)	break;
			p=mp(i,j);
			while(!dq[j].empty()){
				if(get_val(dq[j].back())<get_val(p))	break;
				dq[j].pop_back();
			}
			dq[j].push_back(p);
			while(!dq[j].empty()){
				if((dq[j].front()).fi>=i-E+S)	break;
				dq[j].pop_front();
			}
			p=dq[j].front();
			p.fi=get_val(p)+sum[j][i];
			add(p);
		}
		if(i<S)	continue;
		if(i==m)	ans=min(ans,minx[0].fi);
		for(j=1;j<=n;j++){
			for(k=0;k<mn;k++){
				if(minx[k].se==j || minx[k].se==no[j])	continue;
				t[i][j]=minx[k].fi+T;
				break;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
