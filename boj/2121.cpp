#include<bits/stdc++.h>
#define MAX_N 1005
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
struct node{
	LL x,y,c,i;
}V[MAX_N],L[MAX_N*MAX_N];
struct tree{
	LL x,l,r,m;
}t[4*MAX_N];
LL n,ln,loc[MAX_N],lst[MAX_N],ans;
char in_s[5];
void update(LL x,LL l,LL r,LL p,LL v){
	if(l>p || r<p)	return;
	if(l==r){
		t[x].x=t[x].l=t[x].r=t[x].m=v;
		return;
	}
	LL mid=(l+r)>>1;
	update(2*x,l,mid,p,v);
	update(2*x+1,mid+1,r,p,v);
	if(t[2*x].m+t[2*x+1].m==r-l+1){
		t[x].x=t[x].l=t[x].r=t[x].m=r-l+1;
		return;
	}else	t[x].m=0;
	t[x].x=max({t[2*x].x,t[2*x+1].x,t[2*x].r+t[2*x+1].l});
	t[x].l=max(t[2*x].l,(t[2*x].m?1:0)*(t[2*x].m+t[2*x+1].l));
	t[x].r=max(t[2*x+1].r,(t[2*x+1].m?1:0)*(t[2*x+1].m+t[2*x].r));
	t[x].x=max({t[x].x,t[x].l,t[x].r});
}
LL ccw(node x,node y,node z){return (x.x*y.y+y.x*z.y+z.x*x.y)-(x.y*y.x+y.y*z.x+z.y*x.x);}
int main(){
	LL i,j,x,y;
	scanf("%lld",&n);
	for(i=0;i<n;i++){
		scanf("%lld %lld %s",&V[i].x,&V[i].y,in_s);
		V[i].c=in_s[0]=='R'?1:0;
		V[i].i=i;
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(V[i].x>=V[j].x)	continue;
			L[ln++]={V[j].x-V[i].x,V[j].y-V[i].y,i,j};//change j,i
		}
	}
	sort(L,L+ln,[&](const node x,const node y){
		LL z=ccw(x,{0,0},y);
		if(z<=0)	return false;
		return true;
	});
	
	sort(V,V+n,[&](const node x,const node y){
		return (x.x==y.x)?x.y>y.y:x.x<y.x;
	});
	
	for(i=0;i<n;i++){
		loc[V[i].i]=i;
		lst[i]=V[i].c;
		update(1,0,n-1,i,V[i].c);
		ans=max(ans,t[1].x);
	}
	for(i=0;i<ln;i++){
		i--;
		do{
			i++;
			//change
			x=L[i].c;
			y=L[i].i;
			update(1,0,n-1,loc[x],lst[loc[y]]);
			update(1,0,n-1,loc[y],lst[loc[x]]);
			swap(lst[loc[x]],lst[loc[y]]);
			swap(loc[x],loc[y]);
		}while(i<ln-1 && ccw(L[i],{0,0},L[i+1])==0);
		ans=max(ans,t[1].x);
	}
	printf("%lld\n",ans);
	return 0;
}
