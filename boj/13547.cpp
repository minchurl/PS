#include<bits/stdc++.h>
#define MAX_N 100005
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
	int s,e,idx,ans;
}V[MAX_N];
int n,m,curr_cnt,lst[MAX_N],k;
int cnt[MAX_M];
int add(int x){
	curr_cnt+=(!cnt[lst[x]]);
	cnt[lst[x]]++;
}
int delect(int x){
	cnt[lst[x]]--;
	curr_cnt-=(!cnt[lst[x]]);
}
int main(){
	int i,l,r;
	scanf("%d",&n);
	for(i=1;i<=n;i++)	scanf("%d",&lst[i]);
	scanf("%d",&m);
	for(i=0;i<m;i++){
		scanf("%d %d",&V[i].s,&V[i].e);
		V[i].idx=i;
	}
	k=sqrt(n);
	sort(V,V+m,[&](const node x,const node y){return (x.e/k==y.e/k)?(x.s<y.s):(x.e/k<y.e/k);});
	l=r=0;
	for(i=0;i<m;i++){
		while(V[i].s>l)	delect(l),l++;
		while(V[i].s<l)	l--,add(l);
		while(V[i].e>r)	r++,add(r);
		while(V[i].e<r)	delect(r),r--;
		V[i].ans=curr_cnt;
	}
	sort(V,V+m,[&](const node x,const node y){return x.idx<y.idx;});
	for(i=0;i<m;i++)	printf("%d\n",V[i].ans);
	return 0;	
}
