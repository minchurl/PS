#include<bits/stdc++.h>
#define MAX_N 605
#define MAX_K 20005
using namespace std;
struct node{
	int x,y,idx;
}arr[MAX_N+MAX_K],po[MAX_N],sh[MAX_K];
int nn,n,k,m,t[MAX_N][MAX_N];
node pi;
bool can_connect[MAX_N][MAX_N];
int ccw(node x,node y,node z){
	int temp=x.x*y.y+y.x*z.y+z.x*x.y-x.y*y.x-y.y*z.x-z.y*x.x;
	if(temp<0)	return -1;
	if(temp>0)	return 1;
	return 0;
}
bool angle_sort(node x,node y){
	if(ccw(x,pi,y)==-1)	return true;
	if(ccw(x,pi,y)==1)	return false;
	if(ccw(x,pi,y)==0)	return x.idx<y.idx;
}
void make_can_connect(int p){
	int i,cnt=0;
	pi=po[p];
	nn=0;
	for(i=1;i<=n;i++){
		if(po[i].idx!=p)	arr[nn++]=po[i];
	}
	for(i=1;i<=k;i++)	arr[nn++]=sh[i];
	sort(arr,arr+nn,angle_sort);
	can_connect[p][arr[0].idx]=true;
	cnt++;
	for(i=1;i<nn;i++){
		if(!arr[i].idx)	continue;
		cnt++;
		if((i-cnt+2)%2==0 || ccw(pi,arr[i-1],arr[i])==0)	continue;
		can_connect[p][arr[i].idx]=true;
	}
}
int main(){
	int i,j,s,e;
	scanf("%d %d %d",&n,&k,&m);
	for(i=1;i<=n;i++){scanf("%d %d",&po[i].x,&po[i].y);po[i].idx=i;}
	for(i=1;i<=k;i++)	scanf("%d %d",&sh[i].x,&sh[i].y);
	for(i=1;i<=n;i++)	make_can_connect(i);
	for(i=1;i<=n;i++){
		j=i%n+1;
		j=j%n+1;
		if(can_connect[i][j])	t[i][j]=1;
	}
	for(i=3;i<n;i++){
		for(s=1;s<=n;s++){
			e=(s+i-1)%n+1;
			if(can_connect[s%n+1][e])	t[s][e]+=t[s%n+1][e];
			if(can_connect[s][(n+e-2)%n+1])	t[s][e]+=t[s][(n+e-2)%n+1];
			t[s][e]%=m;
			k=s%n+1;k=k%n+1;
			while(k!=e){
				t[s][e]+=(can_connect[s][k]&can_connect[k][e])*(t[s][k]*t[k][e]);
				t[s][e]%=m;
				k=k%n+1;
			}
		}
	}
	printf("%d\n",t[2][1]);
	return 0;
}
