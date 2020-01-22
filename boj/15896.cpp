#include<bits/stdc++.h>
#define MAX_N 1000005
#define inf (1LL<<60)
using namespace std;
typedef long long LL;
struct node{
	LL x,idx;
	bool operator < (const node d){
		return x<d.x;
	};
}a[MAX_N],b[MAX_N],temp[MAX_N];
LL n,A[MAX_N],B[MAX_N],ans;
int main(){
	freopen("input.txt","r",stdin);
	LL i,j,x,y,z,k,num;
	scanf("%lld",&n);
	for(i=1;i<=n;i++)	scanf("%lld",&A[i]);
	for(i=1;i<=n;i++)	scanf("%lld",&B[i]);
	for(i=1;i<=n;i++){
		for(j=0;j<=28;j++){
			a[j].x+=(A[i]&(1LL<<j))/(1LL<<j);
			b[j].x+=(B[i]&(1LL<<j))/(1LL<<j);
		}
	}
	for(j=0;j<=28;j++)	ans=(ans+(a[j].x%1999)*(b[j].x%1999)*((1LL<<j)%1999))%1999;
	printf("%lld ",ans);
	ans=0;
	x=y=0;
	for(i=1;i<=n;i++){a[i].idx=b[i].idx=i;a[i].x=b[i].x=0;}
	for(i=0;i<=29;i++){
		x=y=0;
		for(j=1;j<=n;j++){
			if(A[a[j].idx]&(1LL<<i)){
				temp[++y]=a[j];
				temp[y].x|=(1LL<<i);
			}else	a[++x]=a[j];
		}
		for(j=x+1;j<=n;j++)	a[j]=temp[j-x];
		
		
		x=y=0;
		for(j=1;j<=n;j++){
			if(B[b[j].idx]&(1LL<<i)){
				temp[++y]=b[j];
				temp[y].x|=(1LL<<i);
			}else	b[++x]=b[j];
		}
		for(j=x+1;j<=n;j++)	b[j]=temp[j-x];
		
		x=y=z=k=0;
		for(j=n;j>=1;j--){
			while(x<n && (1LL<<i)-a[j].x>b[x+1].x)	x++;
			while(y<n && 2*(1LL<<i)-a[j].x>b[y+1].x)	y++;
			while(z<n && 3*(1LL<<i)-a[j].x>b[z+1].x)	z++;
			while(k<n && 4*(1LL<<i)-a[j].x>b[k+1].x)	k++;
			if(y-x+k-z!=n)	break;
		}
		if(j)	continue;
		ans+=(1LL<<i);
	}
	printf("%lld\n",ans);	
	return 0;
}
