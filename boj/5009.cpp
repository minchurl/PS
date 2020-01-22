#include<bits/stdc++.h>
#define MAX_N 205
#define pb push_back
#define add(x) (((x)+n-1)%(3*n)+1)
#define rev(x) (((x)>3*n)?(x)-3*n:(x)+3*n)
using namespace std;
int n,nn,name[6*MAX_N],num[6*MAX_N],cnt,arr[MAX_N][MAX_N],ct[MAX_N];
bool chk[6*MAX_N];
vector<int> net[6*MAX_N];
stack<int> st;
void reset(){
	for(int i=1;i<=6*n;i++){
		net[i].clear();
		net[i].resize(0);
		chk[i]=false;
		num[i]=0;
		name[i]=0;
	}
	cnt=nn=0;
}
void make_net(int x){
	int i,j,y,z;
	for(i=1;i<=n;i++){
		for(j=x+1;j<n;j++){
			y=i+n*ct[i];z=arr[i][j]+n*ct[i];
			y=add(y);z=add(z);
			net[y].pb(rev(z));
			net[z].pb(rev(y));
			y=add(y);z=add(z);
			net[y].pb(rev(z));
			net[z].pb(rev(y));
		}
		y=add(i+n*ct[i]);
		z=add(y);
		net[y].pb(rev(z));net[rev(y)].pb(z);		
		net[z].pb(rev(y));net[rev(z)].pb(y);
	}
}
int dfs(int x){
	int z=name[x]=++cnt,p;
	st.push(x);
	chk[x]=true;
	for(int y:net[x]){
		if(chk[y]){
			if(!num[y])	z=min(z,name[y]);
			continue;
		}
		p=dfs(y);
		z=min(z,p);
	}
	if(z==name[x]){
		nn++;
		while(st.top()!=x){num[st.top()]=nn;st.pop();}
		num[st.top()]=nn;
		st.pop();
	}
	return z;
}
void scc(){
	int i,x;
	for(i=1;i<=6*n;i++){
		if(chk[i])	continue;
		x=dfs(i);
	}
}
bool is_ok(){
	for(int i=1;i<=6*n;i++){
		if(num[i]==num[rev(i)])	return false;
	}
	return true;
}
int main(){
	int i,j,x=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&ct[i]);
		x=0;
		for(j=1;j<=n;j++){
			if(i==j)	continue;
			x++;
			scanf("%d",&arr[i][x]);
		}
	}
	for(i=0;i<=n;i++){
		reset();
		make_net(i);
		scc();
		if(is_ok())	break;
	}
	printf("%d\n",i);
	return 0;
}
