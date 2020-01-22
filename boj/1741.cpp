#include<bits/stdc++.h>
#define MAX_N 100005
#define pb push_back
#define inf 0x3fffffff
using namespace std;
struct D{
	int idx,deg;
	bool operator < (D d) const{
		return deg<d.deg;
	};
}degree[MAX_N];
struct node{
	int idx;
	int left,right;
}arr[MAX_N];
vector<int> net[MAX_N],lst;
queue<int> Q;
int n,m,Z,chk[MAX_N],ans[MAX_N],ansn,fi;
bool visited[MAX_N];
void ER(int x){
	if(x==fi)	fi=arr[x].right;
	arr[arr[x].left].right=arr[x].right;
	arr[arr[x].right].left=arr[x].left;
}
void bfs(){
	int i,x,y,z,k,sz;
	while(!Q.empty()){
		z=k=Q.size();
		while(k--){
			x=Q.front();Q.pop();
			ans[ansn]++;
			sz=net[x].size();
			while(sz--){
				y=net[x][sz];
				if(visited[y])	continue;
				chk[y]++;
			}
		}
		x=fi;
		while(x!=n+1){
			if(chk[x]==z){chk[x]=0;x=arr[x].right;continue;}
			Q.push(x);
			visited[x]=true;
			ER(x);
			x=arr[x].right;
		}

	}
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y;
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++)	degree[i].idx=i;
	fi=Z=1;
	for(i=1;i<=n;i++){
		arr[i].idx=i;
		arr[i].left=i-1;
		arr[i].right=i+1;
	}
	for(i=0;i<m;i++){
		scanf("%d %d",&x,&y);
		net[x].pb(y);
		net[y].pb(x);
		degree[x].deg++;degree[y].deg++;
	}
	sort(degree+1,degree+n+1);
	for(i=1;i<=n;i++){
		if(visited[degree[i].idx])	continue;
		Q.push(degree[i].idx);
		ER(degree[i].idx);
		visited[degree[i].idx]=true;
		bfs();
		ansn++;
	}
	sort(ans,ans+ansn);
	printf("%d\n",ansn);
	for(i=0;i<ansn;i++)	printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
