#include<bits/stdc++.h>
#define MAX_N 100005
using namespace std;
struct node{
	int x,idx,l,r;
}arr[MAX_N],X[MAX_N];
int n,m,k,ans[MAX_N],in[MAX_N],cc[MAX_N];
bool chk[MAX_N];
bool sort_cmp(node x,node y){return x.x<y.x;}
void Delect(int x){
	chk[x]=true;
	arr[arr[x].l].r=arr[x].r;
	arr[arr[x].r].l=arr[x].l;
}
void solve(int n,int s){
	int i,x,y,z,a;
	for(i=1;i<=n;i++){
		arr[i].idx=i;
		arr[i].l=i-1;
		arr[i].r=i+1;
		chk[i]=false;
	}
	arr[n+1].l=n;
	arr[n+1].r=n+1;
	x=arr[n].x+1;
	m=0;
	for(i=n;i>=1;i--){
		if(arr[i].x<x){
			x=arr[i].x;
			Delect(i);
			ans[s+i]=1;
		}else	X[m++]=arr[i];
	}
	sort(X,X+m,sort_cmp);
	ans[s+arr[n+1].l]=1;
	for(i=0;i<m;i++){
		x=X[i].idx;
		printf("%d : %d\n",x,X[i].x);
		if(chk[x])	continue;
		y=arr[x].r;
		while(arr[y].r!=n+1 && arr[y].x>arr[arr[y].r].x){y=arr[y].r;}
		if(arr[y].r!=n+1)	break;
		y=arr[x].r;
		if(x==arr[n+1].l)	a=3-ans[s+x];
		else	a=ans[s+arr[n+1].l];
		if(y!=n+1){
			ans[s+y]=a;
			z=arr[y].r;
			while(z!=n+1){ans[s+z]=a;Delect(z);z=arr[z].r;}
		}else	ans[s+arr[x].l]=a;
		Delect(x);
		ans[s+x]=3-a;
	}
	if(i!=m){printf("NIE\n");exit(0);}
}
int main(){
	freopen("input.txt","r",stdin);
	scanf("%d",&k);
	int i,s,x,j;
	x=0;
	s=1;
	for(i=1;i<=k;i++){
		scanf("%d",&in[i]);
		cc[in[i]]=1;
		x+=cc[i];
		if(in[i]<i)	x++;
		if(x==i){
			printf("%d\n",i);
			for(j=s;j<=i;j++)	arr[j-s+1].x=in[j];
			solve(i-s+1,s-1);
			s=i+1;
		}
	}
	printf("TAK\n");
	for(i=1;i<=k;i++)	printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
