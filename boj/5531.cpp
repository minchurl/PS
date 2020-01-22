P97AwSJ9

#include<bits/stdc++.h>
#define MAX_N 100005
using namespace std;
struct point{
	int x,y;
}a[MAX_N],b[MAX_N],arr[MAX_N],carr[MAX_N];
struct tree{
	int m,v;
}t[MAX_N];
int n,an,bn,ans;
int ax[MAX_N],ay[MAX_N];
bool chk[MAX_N];
void update(int x,int l,int r,int s,int e,int z){
	int mid=(l+r)/2;
	if(l>r)	return;
	if(s>e)	return;
	if(r<s)	return;
	if(e<l)	return;
	if(s<=l && r<=e){
		t[x].v+=z;
		t[x].m+=z;
		return;
	}
	update(2*x,l,mid,s,e,z);
	update(2*x+1,mid+1,r,s,e,z);
	t[x].m=t[x].v+max(t[2*x].m,t[2*x+1].m);
}
void vair(point p,int z){
	int l=(lower_bound(ay+1,ay+an+1,p.y)-ay);
	int r=(lower_bound(ax+1,ax+an+1,p.x)-ax);
	if(r>an) r=an;
	update(1,1,an,l,r,z);
	return;
}
void _copy(){for(int i=1;i<=n;i++)carr[i]=arr[i];}
bool sort_cmpx(point x,point y){
	if(x.x==y.x)	return x.y<y.y;
	return x.x<y.x;
}
bool sort_cmpy(point x,point y){
	if(x.y==y.y)	return x.x<y.x;
	return x.y<y.y;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,j,k,p=0;
	scanf("%d",&n);
	scanf("%d",&arr[1].y);
	arr[1].x=1;
	an++;bn++;
	a[an]=b[bn]=arr[1];
	ay[an]=arr[1].y;
	ax[an]=1;
	for(i=2;i<=n;i++){
		//A & B
		scanf("%d",&arr[i].y);
		arr[i].x=i;
		
		if(a[an].y<arr[i].y){
			a[++an]=arr[i];
			ax[an]=i;
			ay[an]=arr[i].y;
		}
		while(bn>0 && b[bn].y>=arr[i].y)	bn--;
		b[++bn]=arr[i];
	}
	for(i=1;i<=an;i++)	chk[a[i].x]=true;
	for(i=1;i<=bn;i++)	chk[b[i].x]=true;
	sort(arr+1,arr+n+1,sort_cmpy);
	for(i=1;i<=n;i++)	p+=abs(arr[i].x-i);
	j=0;
	for(i=1;i<=n;i++){
		if(!chk[i])	arr[++j]=arr[i];
	}
	n=j;
	_copy();
	sort(arr+1,arr+n+1,sort_cmpx);
	sort(carr+1,carr+n+1,sort_cmpy);	
	j=1;
	k=1;
	for(i=1;i<=bn;i++){
		while(arr[j].x<b[i].x && j<=n){
			vair(arr[j],1);
			j++;
		}
		ans=max(ans,t[1].m);
		while(carr[k].y<=b[i].y && k<=n){
			vair(carr[k],-1);
			k++;
		}
	}
	p/=2;p--;
	printf("%d\n",p-ans);
	return 0;
}
