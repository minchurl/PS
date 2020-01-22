#include<bits/stdc++.h>
#define MAX_N 30005
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

#define next(x) (((x)+1)%m)
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
typedef long double LD;

//plz write LL
// 2 <= N <= 3*(1e4) (sp N == 2)
// 0 <= T <= 1e7
//input : N,T
//input : x,y,dx,dy
// -1e7 <= x,y <= 1e7
//  -1e2 <= dx,dy <= 1e2
LL n;
LL X[MAX_N],Y[MAX_N],dx[MAX_N],dy[MAX_N];
pil V[MAX_N];
LL ccw(LL xx,LL xy,LL yx,LL yy,LL zx,LL zy){return (xx*yy+yx*zy+zx*xy)-(xy*yx+yy*zx+zy*xx);}
LL get_val(LL t){//return max_distance
	LL i;
	for(i=0;i<n;i++)	V[i] = {X[i]+dx[i]*t,Y[i]+dy[i]*t};
	for(i=1;i<n;i++){
		if(V[0]>V[i])	swap(V[0],V[i]);
	}
	sort(V+1,V+n,[&](const pil x,const pil y){
		if(ccw(x.fi,x.se,V[0].fi,V[0].se,y.fi,y.se)==0)	return sq(x.fi-V[0].fi)+sq(x.se-V[0].se)<sq(y.fi-V[0].fi)+sq(y.se-V[0].se);
		return (ccw(x.fi,x.se,V[0].fi,V[0].se,y.fi,y.se)>0);
	});
	LL m=2;
	for(i=2;i<n;i++){
		while(m>1 && ccw(V[m-2].fi,V[m-2].se,V[m-1].fi,V[m-1].se,V[i].fi,V[i].se)>=0)	m--;
		V[m++]=V[i];
	}
	if(m==2)	return sq(V[0].fi-V[1].fi)+sq(V[0].se-V[1].se);
	LL x=1,mx=0;
	for(i=0;i<m;i++){
		while(ccw(V[next(i)].fi,V[next(i)].se,V[i].fi,V[i].se,V[i].fi+V[x].fi-V[next(x)].fi,V[i].se+V[x].se-V[next(x)].se)<0)	x=next(x);
		mx=max(mx,sq(V[i].fi-V[x].fi)+sq(V[i].se-V[x].se));
	}
	return mx;
}
int main(){
	LL i,l,r;
	scanf("%lld %lld",&n,&r);
	for(i=0;i<n;i++)	scanf("%lld %lld %lld %lld",&X[i],&Y[i],&dx[i],&dy[i]);
	l=0;
	while(l+1<r){
		LL m1=(2*l+r)/3,m2=(l+2*r)/3;
		LL x=get_val(m1),y=get_val(m2);
		if(x>y)	l=m1+1;	
		else	r=m2-1;
	}
	LL x=get_val(l),y=get_val(r);
	if(y<x)	printf("%lld\n%lld\n",r,y);
	else	printf("%lld\n%lld\n",l,x);
	return 0;
}
