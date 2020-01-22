#include<bits/stdc++.h>
#define MAX_N 550005
#define pb push_back
#define inf 0x3fffffff
#define LL long long
using namespace std;
struct node{
	LL sx,sy,ex,ey;
	LL si,ei;
};
struct D{
	LL x,y;
	bool operator < (D d) const{return d.x*y<=x*d.y;}
};
node arr[MAX_N];
vector<D> X;
map<LL,LL> getidx;
LL n,m,k,ans;
LL ud[2*MAX_N],num[2*MAX_N],mm[2*MAX_N];
LL E[2*MAX_N];
LL t[2*MAX_N];
LL gcd(LL x,LL y){return y?gcd(y,x%y):x;}
bool sort_si(node x,node y){return x.si<y.si;}
int main(){
	freopen("input.txt","r",stdin);
	LL i,j,x;
	scanf("%lld %lld",&k,&n);
	for(i=1;i<=n;i++){
		scanf("%lld %lld %lld %lld",&arr[i].sx,&arr[i].sy,&arr[i].ex,&arr[i].ey);
		x=gcd(arr[i].sx,arr[i].sy);
		arr[i].sx/=x;arr[i].sy/=x;
		x=gcd(arr[i].ex,arr[i].ey);
		arr[i].ex/=x;arr[i].ey/=x;
		X.pb({arr[i].sx,arr[i].sy});X.pb({arr[i].ex,arr[i].ey});
	}
	sort(X.begin(),X.end());
	m=1;
	x=X.size();
	for(i=1;i<x;i++){
		if((X[i].x-X[i-1].x) || (X[i].y-X[i-1].y))	m++;
		X[m-1]=X[i];
	}
	for(i=0;i<m;i++)	getidx[X[i].x*1000005LL+X[i].y]=i+1;
	for(i=1;i<=n;i++){
		arr[i].si=getidx[arr[i].sx*1000005LL+arr[i].sy];
		arr[i].ei=getidx[arr[i].ex*1000005LL+arr[i].ey];
		if(arr[i].si>arr[i].ei)	swap(arr[i].si,arr[i].ei);
		ud[arr[i].si]++;ud[arr[i].ei+1]--;
		mm[arr[i].ei+1]--;
	}
	
	for(i=1;i<=m;i++)	num[i]=num[i-1]+ud[i];
	sort(arr+1,arr+n+1,sort_si);
	x=1;
	for(i=1;i<=m;i++){
		E[i]=max(E[i-1],i);
		while(arr[x].si<=i && x<=n){
			E[i]=max(E[i],arr[x].ei);
			x++;
		}
	}
	LL pp=0;
	for(i=1;i<=k;i++){
		//꼭짓점
		for(j=m;j>=1;j--){
			t[E[j]]=max(t[E[j]],t[j-1]+num[j]);
			ans=max(ans,t[E[j]]);
			if(j!=1){
				//선분
				t[E[j-1]]=max(t[E[j-1]],t[j-2]+num[j-1]+mm[j]);
				ans=max(ans,t[E[j-1]]);
			}
		}
		for(j=1;j<=m;j++)	t[j]=max(t[j-1],t[j]);
		if(pp==ans)	break;
		pp=ans;
	}
	printf("%lld\n",ans);
	printf("%lf\n",(double)clock()/CLOCKS_PER_SEC);
	return 0;
}
