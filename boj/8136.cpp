//g++ -std=c++11 8136.cpp -o a.out
#include<bits/stdc++.h>
#define MAX_N 2000005
#define pb push_back
using namespace std;
struct node{
	int en;
	char x;
	vector<int> Next;
}net[MAX_N];
int n,m,nn,t[2*MAX_N],I;
long long ans;
char na[2*MAX_N];
bool chk[MAX_N];
vector<char> in[MAX_N];
void dfs(int x,int y){
	if(chk[y])	ans+=(long long)net[x].en;
	if(y==m){
		net[x].en++;
		return;
	}
	int sz=net[x].Next.size(),z;
	while(sz--){
		z=net[x].Next[sz];
		if(z && net[z].x==in[I][y]){
			sz=-3;
			break;
		}
	}
	if(sz!=-3){
		z=nn;
		net[nn].x=in[I][y];
		net[x].Next.pb(nn);nn++;
	}
	dfs(z,y+1);
}
bool sort_cmp(vector<char> x,vector<char> y){
	return x.size()<y.size();
}
int main(){
	freopen("input.txt","r",stdin);
	int i,j,x,y;
	scanf("%d",&n);
	nn=1;
	for(i=1;i<=n;i++){
		scanf("%d %s",&m,na);
		for(j=0;j<m;j++)	in[i].pb(na[j]);
	}
	sort(in+1,in+n+1,sort_cmp);
	for(i=1;i<=n;i++){
		m=in[i].size();
		I=i;
		for(j=1;j<=m;j++){
			na[2*j-1]=in[i][j-1];
			na[2*j]='*';
			chk[j]=false;
		}
		x=y=0;
		for(j=1;j<2*m;j++){
			if(j<=x)	t[j]=min(x-j,t[2*y-j]);
			else	t[j]=0;
			while(j-t[j]-1>0 && j+t[j]+1<2*m && na[j-t[j]-1]==na[j+t[j]+1])	t[j]++;
			if(x<j+t[j]){
				x=j+t[j];
				y=j;
			}
			if(j+t[j]>=2*m-1)	chk[(j-t[j])/2]=true;
		}
		chk[m]=true;
		dfs(0,0);
	}
	ans*=2;
	ans+=(long long)n;
	printf("%lld\n",ans);
	return 0;
}
