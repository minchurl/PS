#include<bits/stdc++.h>
#define MAX_N 100005
#define pb push_back
using namespace std;
struct node{
	int x,y,color,idx;
}arr[2*MAX_N];
int n,ans,t[2*MAX_N],val[MAX_N];
vector<int> X;
bool arr_cmp(node x,node y){
	if(x.y==y.y && x.color==y.color)	return x.x<y.x;
	if(x.y==y.y)	return x.color<y.color;
	return x.y<y.y;	
}
int read(int x){int y=0;for(;x>0;x-=(x&-x))	y=max(y,t[x]);return y;}
void update(int x,int y){for(;x<=2*n;x+=(x&-x))	t[x]=max(t[x],y);}
int main(){
	freopen("input.txt","r",stdin);
	int i;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d %d %d %d",&arr[2*i].x,&arr[2*i].y,&arr[2*i+1].x,&arr[2*i+1].y);
		arr[2*i].color=0;arr[2*i+1].color=1;
		arr[2*i].idx=arr[2*i+1].idx=i;
		X.pb(arr[2*i].x);X.pb(arr[2*i+1].x);
	}
	sort(X.begin(),X.end());X.erase(unique(X.begin(),X.end()),X.end());
	for(i=0;i<2*n;i++)	arr[i].x=(lower_bound(X.begin(),X.end(),arr[i].x)-X.begin())+1;
	sort(arr,arr+2*n,arr_cmp);
	for(i=0;i<2*n;i++){
		if(arr[i].color)	update(arr[i].x,val[arr[i].idx]);
		else{
			val[arr[i].idx]=read(arr[i].x-1)+1;
			ans=max(ans,val[arr[i].idx]);
		}
	}
	printf("%d\n",ans);
	return 0;
}

