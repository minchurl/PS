#include<bits/stdc++.h>
#include<inttypes.h>//__int64,__int128..
#define MAX_N 25
#define MAX_K 1048580
//vector&pair
#define pb push_back
#define mp make_pair
//math
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))//Regardless of type
//pair
#define fi first
#define se second
//infinit
#define LL_inf (1LL<<60)
#define full_inf 0x7fffffff
#define half_inf 0x3ffffff1
#define inf 0x3ffffff0
//MOD
#define MOD 100000LL
using namespace std;
//type
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<int,pii> p_pq;
typedef long double LD;
LL n,m,I,J,ans,cnt;
char arr[MAX_N][MAX_N];
LL a[MAX_K],b[MAX_K];
LL al(char x){
	if(x=='J')	return 0;
	if(x=='O')	return 1;
	if(x=='I')	return 2;
	return 3;
}
void f(LL c,LL z,LL y){
	if(c==m){
		a[J]=(a[J]+b[y^((1<<m)-1)])%MOD;
		return;
	}
	LL p=al(arr[I][c]);
	if(J&(1<<c)){
		if(p==0 || p==1)	return;
		f(c+1,2,y);
		return;
	}
	if(p==2)	return;
	if(J&(1<<c))	return;
	if(p!=3){
		if(z==0 && p==1)	f(c+1,p,y|(1<<(c-1)));
		else	f(c+1,p,y);
		return;
	}
	f(c+1,0,y);
	if(z==0)	f(c+1,1,y|(1<<(c-1)));
	else	f(c+1,1,y);
}
void g(LL c,LL x){
	if(c==m){
		printf("%lld %lld\n",J,x);
		b[x]+=a[J];
		return;
	}
	if((x&(1<<c))==0)	g(c+1,x|(1<<c));
	g(c+1,x);
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,j;
	scanf("%lld %lld",&n,&m);
	for(i=n-1;i>=0;i--){
		scanf("%s",arr[i]);
		for(j=0;j<m;j++)	if(arr[i][j]=='?')	cnt++;
	}
	for(i=(1<<m)-1;i>=0;i--)	b[i]=1;
	for(I=0;I<n;I++){
		for(J=(1<<m)-1;J>=0;J--){
			a[J]=0;
			f(0,2,0);
		}
		for(J=(1<<m)-1;J>=0;J--)	b[J]=0;
		for(J=(1<<m)-1;J>=0;J--)	g(0,J);
	}
	ans=1;
	while(cnt--)	ans=(ans*3)%MOD;
	ans=(ans+MOD-b[(1<<m)-1])%MOD;
	printf("%lld\n",ans);
	return 0;
}

