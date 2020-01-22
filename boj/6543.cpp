#include<bits/stdc++.h>
#define MAX_N 5005
#define pb push_back
using namespace std;
int n,m,nn,dep[MAX_N],num[MAX_N],cnt;
bool chk[MAX_N];
vector<int> net[MAX_N];
stack<int> st;
int dfs(int x){
	int z=dep[x],p;
	chk[x]=true;
	st.push(x);
	for(auto y:net[x]){
		if(chk[y]){
			if(!num[y])	z=min(z,dep[y]);
			continue;
		}
		dep[y]=++cnt;
		p=dfs(y);
		z=min(p,z);
	}
	if(dep[x]==z){
		nn++;
		while(st.top()!=x){num[st.top()]=nn;st.pop();}
		st.pop();
		num[x]=nn;
	}
	return z;
}
void reset(){for(int i=1;i<=n;i++){num[i]=0;net[i].clear();net[i].resize(0);chk[i]=false;}}
int main(){
	int i,x,y;
	while(1){
		scanf("%d",&n);
		if(!n)	break;
		scanf("%d",&m);
		for(i=0;i<m;i++){
			scanf("%d %d",&x,&y);
			net[x].pb(y);
		}
		nn=0;
		cnt=0;
		for(i=1;i<=n;i++){
			if(chk[i])	continue;
			dep[i]=++cnt;
			x=dfs(i);
		}
		for(x=1;x<=n;x++){
			for(auto y:net[x]){
				if(num[x]!=num[y])	chk[num[x]]=false;
			}
		}
		for(i=1;i<=n;i++)	if(chk[num[i]])	printf("%d ",i);
		printf("\n");
		reset();
	}
	return 0;
}
