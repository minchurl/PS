#include<bits/stdc++.h>
#define MAX_N 10005
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
int n,X;
vector<int> E[MAX_N];
bool vis[MAX_N];
int dfs(int x){
	if(X==-1)	return 0;
	vis[x]=true;
	vector<int> V;
	int z;
	if(E[x].size()%2)	V.pb(0);
	for(int y:E[x]){
		if(vis[y])	continue;
		z=dfs(y);
		if(X==-1)	return 0;
		if(z)	V.pb(z);
	}
	sort(all(V));
	z=-1;
	int i;
	for(int j=V.size()-1;j>=0;j--){
		if(V[j]==-1)	continue;
		for(i=j-1;i>=0;i--){
			if(V[i]==-1 || V[i]+V[j]>X)	continue;
			break;
		}
		if(i!=-1){
			V[i]=V[j]=-1;
		}
	}
	for(int y:V){
		if(y!=-1){
			if(z!=-1){
				X=-1;
				return 0;
			}
			z=y;
		}
	}
	V.clear();
	V.resize(0);
	return z+1;
}
bool is_ok(int x){
	if(x<=0)	return false;
	for(int i=1;i<=n;i++)	vis[i]=false;
	X=x;
	int y=dfs(1)-1;
	if(X==-1)	y=inf;
	return y<=x;
}
int main(){
	int i,x,y;
	scanf("%d",&n);
	for(i=1;i<n;i++){
		scanf("%d %d",&x,&y);
		E[x].pb(y);
		E[y].pb(x);
	}
	x=0;
	for(i=1;i<=n;i++)	x+=E[i].size()%2;
	printf("%d ",x/2);
	int l,r;
	l=1,r=n-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(is_ok(mid)){
			if(!is_ok(mid-1))	return !printf("%d\n",mid);
			r=mid-1;
		}else{
			if(is_ok(mid+1))	return !printf("%d\n",mid+1);
			l=mid+1;
		}
	}
	return 0;
}
