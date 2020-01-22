#include<bits/stdc++.h>
#define MAX_N 1005
#define pb push_back
using namespace std;
int n,m;
int wh_idx[MAX_N][MAX_N];
int visited[MAX_N],vc;
vector<int> net[MAX_N];
stack<int> st;
bool dfs(int x,int e){
	int y,sz=net[x].size();
	visited[x]=vc;
	st.push(x);
	if(x==e)	return true;
	while(sz--){
		y=net[x][sz];
		if(!y || visited[y]==vc)	continue;
		if(dfs(y,e))	return true;
	}
	st.pop();
	return false;
}
void tree_dp(int x,int z){
	int y,sz=net[x].size();
	visited[x]=vc;
	while(sz--){
		y=net[x][sz];
		if(!y || visited[y]==vc)	continue;
		if(z==-1){printf("%d %d\n",x,y);tree_dp(y,-1);z++;}
		else{printf("%d %d\n",y,x);tree_dp(y,0);z--;}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y,z;
	printf("Yes\n");
	scanf("%d %d",&n,&m);
	for(i=0;i<m;i++){
		scanf("%d %d",&x,&y);
		vc++;
		while(!st.empty())	st.pop();
		z=dfs(x,y);
		if(z){
			printf("%d %d\n",x,y);
			x=y;
			st.pop();
			while(!st.empty()){
				y=st.top();
				printf("%d %d\n",x,y);
				net[x][wh_idx[x][y]]=0;
				net[y][wh_idx[y][x]]=0;
				st.pop();
				x=y;
			}
			continue;
		}
		wh_idx[x][y]=net[x].size();
		wh_idx[y][x]=net[y].size();
		net[x].pb(y);
		net[y].pb(x);
	}
	vc++;
	for(i=1;i<=n;i++){
		if(visited[i]==vc)	continue;
		tree_dp(i,-1);
	}
	return 0;
}
