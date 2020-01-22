#include<bits/stdc++.h>
#define MAX_N 2005
using namespace std;
int n,m,k,ans;
int ls[MAX_N][MAX_N],cs[MAX_N][MAX_N],temp[MAX_N][MAX_N],arr[MAX_N][MAX_N];
void make_sum(){
	int i,j;
	for(i=1;i<=n;i++)	for(j=1;j<=m;j++)	ls[i][j]=ls[i][j-1]+arr[i][j];
	for(i=1;i<=m;i++)	for(j=1;j<=n;j++)	cs[i][j]=cs[i][j-1]+arr[j][i];
}
bool is_ok(int sx,int sy,int ex,int ey,int s,int e){
	while(sx<=ex && sy<=ey){
		if(cs[sy][ex]-cs[sy][sx-1]<=k)	sy++;
		else if(cs[ey][ex]-cs[ey][sx-1]<=k)	ey--;
		else if(sx<s && ls[sx][ey]-ls[sx][sy-1]<=k)	sx++;
		else if(ex>e && ls[ex][ey]-ls[ex][sy-1]<=k)	ex--;
		else return false;
	}
	return true;
}
void make_ans(){
	int s,e=0;
	for(s=1;s<=n;s++){
		e=max(e,s);
		while(e<=n && is_ok(1,1,n,m,s,e)){	
			ans=max(ans,e-s+1);
			e++;
		}
	}
}
void rotating(){
	int i,j;
	for(i=1;i<=n;i++)	for(j=1;j<=m;j++)	temp[j][i]=arr[i][j];
	swap(n,m);
	for(i=1;i<=n;i++)	for(j=1;j<=m;j++)	arr[i][j]=temp[i][j];
}
int main(){
	freopen("input.txt","r",stdin);
	int i,j;
	scanf("%d %d %d",&k,&m,&n);
	for(i=1;i<=n;i++)	for(j=1;j<=m;j++)	scanf("%d",&arr[i][j]);
	make_sum();
	make_ans();
	rotating();
	make_sum();
	make_ans();
	printf("%d\n",ans?n+m-ans:-1);
	return 0;
}
