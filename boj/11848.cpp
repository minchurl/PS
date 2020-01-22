#include<bits/stdc++.h>
#define MAX_N 300005
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
#define inf (1LL<<60)
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
pil arr[MAX_N];
LL n,m,k,ans;
bool chk[MAX_N];
struct cmpp{
	bool operator()(const LL x,const LL y){
		return arr[x].fi<arr[y].fi;
	}
};
struct cmpq{
	bool operator()(const LL x,const LL y){
		return arr[x].se<arr[y].se;
	}
};
priority_queue<LL,vector<LL>,cmpp> p;
priority_queue<LL,vector<LL>,cmpq> q;
priority_queue<LL> r;
priority_queue<LL> s;
void swaping(){
	while(r.size() && s.size() && r.top()>0 && s.top()>0){
		ans+=r.top()+s.top();
		r.pop();s.pop();
		r.push(-inf);s.push(-inf);
	}
}
int main(){
	LL i,x,y,z,l,a,b;
	scanf("%lld %lld %lld",&n,&m,&k);
	for(i=0;i<n;i++)	scanf("%lld %lld",&arr[i].fi,&arr[i].se);
	for(i=0;i<n;i++){p.push(i);q.push(i);}
	while(r.size()<m || s.size()<k){
		swaping();
		while(p.size() && chk[p.top()])	p.pop();
		while(q.size() && chk[q.top()])	q.pop();
		
		x=y=-inf;
		z=l=0;
		
		if(r.size()<m && p.size()){
			a=p.top();
			x=arr[a].fi;
		}
		if(s.size()<k && q.size()){
			b=q.top();
			y=arr[b].se;
		}
		if(s.size() && s.size()<k && s.top()>0 && x<x+s.size()){
			x+=s.size();
			l=1;
		}
		if(r.size() && r.size()<m && r.top()>0 && y<y+r.top()){
			y=y+r.top();
			z=1;
		}		
		if(x>=y){
			p.pop();
			ans+=x;
			chk[a]=true;
			r.push(arr[a].se-arr[a].fi);
			
			if(l){
				s.pop();r.push(-inf);
			}
		}else{
			q.pop();
			ans+=y;
			chk[b]=true;
			s.push(arr[b].fi-arr[b].se);
			if(z){
				r.pop();s.push(-inf);
			}
		}
		
	}
	swaping();
	printf("%lld\n",ans);
	return 0;
}

