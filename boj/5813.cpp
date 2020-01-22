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
#define MOD 1000000000LL
#define cpx_mod(x) (((LD)(((LL)x.real())%MOD)),((LD)(((LL)x.imag())%MOD)))
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
typedef long double LD;
// 1<= N <= 100000
//input N
//input x,y (N)
//output all(x<y)(distance(x,y)) MOD 1000000000
struct node{
	int x,y;
	bool operator < (const node d){
		return (x==d.x)?(y<d.y):(x<d.x);
	};
}V[MAX_N];
int n,ans;
int dx[4]={-1,1},dy[4]={0,0,0,0};
bool vis[MAX_N];
vector<int> net[MAX_N];
int get_cnt(int l){
	int r=l;	
	while(r+1<n && V[r].x==V[r+1].x && V[r].y+1==V[r+1].y)	r++;
	while(l-1>=0 && V[l-1].x==V[l].x && V[l-1].y+1==V[l].y)	l--;
	for(int i=l;i<=r;i++)	vis[i]=true;
	int z=0,k=0;
	for(int j=l;j<=r;j++){
		for(int i=0;i<2;i++){
			node p=V[j];
			p.x+=dx[i];
			p.y+=dy[i];
			int idx=lower_bound(V,V+n,p)-V;
			if(p.x!=V[idx].x || p.y!=V[idx].y || vis[idx])	continue;
			int y=get_cnt(idx);
			z+=y;
		}
	}
	z+=(r-l+1);
	k=n-z;
	ans=(int)(((LL)ans+(LL)(z)*(LL)k)%MOD);
	return z;
}
void rev(){for(int i=0;i<n;i++)	swap(V[i].x,V[i].y),vis[i]=false;}
int main(){
	freopen("md.txt","r",stdin);
	int i;
	scanf("%d",&n);
	for(i=0;i<n;i++)	scanf("%d %d",&V[i].x,&V[i].y);
	V[n]={-1,-1};
	//X
	sort(V,V+n);
	get_cnt(0);
	//Y
	rev();
	sort(V,V+n);
	get_cnt(0);
	//output ans
	printf("%d\n",ans);
	return 0;
}
