#include<bits/stdc++.h>
#include<inttypes.h>//__int64,__int128..
#define MAX_N 4005
//vector&pair
#define pb push_back
#define mp make_pair
//math
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))//Regardless of type
//for pair
#define fi first
#define se second
//infinit
#define LL_inf (1LL<<60)
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
//MOD
#define MOD 1000000007LL
using namespace std;
//type
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef long double LD;
struct node{
	int sx,sy,ex,ey;
}arr[MAX_N][MAX_N];
int H,W,L,P,ans;
int t[MAX_N][MAX_N];
bool exist[MAX_N][MAX_N];
int read(int x,int y){
	int sum=0;
	for(;x>0;x-=(x&-x))	for(;y>0;y-=(y&-y))	sum+=t[x][y];
	return sum;
}
void update(int x,int y){
	for(;x<=max(W,H);x+=(x&-x))	for(;y<=max(W,H);y+=(y&-y))	t[x][y]++;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,j,x,y;
	scanf("%d %d %d %d",&H,&W,&L,&P);
	for(i=0;i<P;i++){
		scanf("%d %d",&x,&y);
		exist[x][y]=true;
	}
	for(i=1;i<=H;i++){
		arr[i][1].sx=1;
		for(j=2;j<=W;j++)	arr[i][j].sx=exist[i][j]?j:arr[i][j-1].sx;
		arr[i][W].ex=W;
		for(j=W-1;j>=1;j--)	arr[i][j].ex=exist[i][j]?j:arr[i][j+1].ex;
	}
	for(i=1;i<=W;i++){
		arr[1][i].sy=1;
		for(j=2;j<=H;j++)	arr[j][i].sy=exist[j][i]?j:arr[j-1][i].sy;
		arr[i][H].e=H;
		for(j=H-1;j>=1;j--)	arr[j][i].ey=exist[j][i]?j:arr[j+1][i].ey;
	}
	
	for(i=1;i<=H;i++){
		for(j=1;j<=W;j++){
			arr[i][j].sx=min(i-arr[i][j].sx,j-arr[i][j].sy)-1;
			arr[i][j].ex=min(arr[i][j].ex-i,arr[i][j].ey-j)-1;
		}
	}
	L-=2;
	for(k=1;k<=W;k++){
		for(i=1;i<=H;i++){
			for(j=1;j<=W;j++)	t[i][j]=0;
		}
		j=k;
		i=H;
		while(j){
			ans+=read(i,i+arr[i][j].ex);
			if(i+L<=H)	update(i+L-arr[i][j].sx,i+L);
			j--;
		}
	}
	for(k=1;k<H;k++){
		for(i=1;i<=H;i++){
			for(j=1;j<=W;j++)	t[i][j]=0;
		}
		j=W;
		i=k;
		while(i){
			ans+=read(j,j+arr[i][j].ex);
			if(j+L<=W)	update(j+L-arr[i][j].sx,j+L);
			i--;
		}
	}
	printf("%d\n",ans);
	return 0;
}
