#include<bits/stdc++.h>
#define MAX_N 1005
#define MAX_M 1000005
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
struct node{
	int c,x,y;
}arr[MAX_N],P[MAX_M];
int n,m;
int t[1000005];
bool ans[MAX_M];
vector<int> X,lst[MAX_N];
int main(){
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d %d %d",&arr[i].c,&arr[i].x,&arr[i].y);
		X.pb(arr[i].x);
	}
	sort(all(X));X.erase(unique(all(X)),X.end());
	for(i=1;i<=n;i++)	arr[i].x=lower_bound(all(X),arr[i].x)-X.begin()+1;
	scanf("%d",&m);
	for(i=1;i<=m;i++){
		scanf("%d %d %d",&P[i].x,&P[i].c,&P[i].y);
		P[i].y+=P[i].x;
		P[i].x=lower_bound(all(X),P[i].x+1)-X.begin();
		lst[P[i].x].pb(i);
	}
	sort(arr+1,arr+n+1,[&](const node x,const node y){return x.x<y.x;});
	t[0]=2*inf;
	for(i=1;i<=100000;i++)	t[i]=-1;
	for(i=1;i<=n;i++){
		for(j=100000;j>=arr[i].c;j--)	t[j]=max(t[j],min(t[j-arr[i].c],arr[i].y));
		for(int idx:lst[arr[i].x]){
			ans[idx]=t[P[idx].c]>P[idx].y;
		}
	}
	for(i=1;i<=m;i++)	printf("%s\n",ans[i]?"TAK":"NIE");
	return 0;
}
