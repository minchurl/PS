#include<bits/stdc++.h>
#define MAX_N 1005
#define pb push_back
using namespace std;
struct node{
	int y,cost;
};
struct T{
	int x,cost,idx,k;
	bool sl;
};
struct cmp{
	bool operator()(T x,T y){
		if(x.cost==y.cost)	return x.x<y.x;
		return x.cost<y.cost;
	}
};
priority_queue<T,vector<T>,cmp> Q;
vector<node> net[MAX_N];
T Next[MAX_N][MAX_N];
vector<int> lst;
int n,k,t[2][MAX_N][MAX_N];
bool visited[MAX_N];
void dfs(int x){
	int i,sz=net[x].size();
	node l;
	T y,z;
	visited[x]=true;
	while(sz--){
		l=net[x][sz];
		if(visited[l.y])	continue;
		dfs(l.y);
	}
	//select
	while(!Q.empty())	Q.pop();
	sz=net[x].size();
	while(sz--){
		l=net[x][sz];
		if(visited[l.y])	continue;
		t[1][x][1]+=l.cost;
		Q.push({l.y,max(t[0][l.y][1],t[1][l.y][1]-l.cost),sz,1,t[0][l.y][1]<=t[1][l.y][1]-l.cost});//x,cost,idx,k,sl
	}
	for(i=2;i<=k;i++){
		if(Q.empty())	break;
		y=Q.top();Q.pop();
		t[1][x][i]=t[1][x][i-1]+y.cost;
		z=y;
		z.k++;
		z.cost=max(t[0][z.x][z.k],t[1][z.x][z.k]-net[x][z.idx].cost)-y.cost;
		if(z.cost<=0)	continue;
		Q.push(z);
	}
	//non-select
	while(!Q.empty())	Q.pop();
	sz=net[x].size();
	while(sz--){
		l=net[x][sz];
		if(visited[l.y])	continue;
		Q.push({l.y,max(t[0][l.y][1],t[1][l.y][1]+l.cost),sz,1,t[0][l.y][1]<=t[1][l.y][1]+l.cost});//x,cost,idx,k
	}
	for(i=1;i<=k;i++){
		if(Q.empty())	break;
		y=Q.top();Q.pop();
		t[0][x][i]=t[0][x][i-1]+y.cost;
		
		z=y;
		z.k++;
		z.cost=max(t[0][z.x][z.k],t[1][z.x][z.k]+net[x][z.idx].cost)-y.cost;
		if(z.cost<=0)	continue;
		Q.push(z);
	}
	visited[x]=false;
}
void make_lst(int Z,int x,int p){
	int i,sz=net[x].size();
	node l;
	T y,z;
	visited[x]=true;
	sz=net[x].size();
	while(sz--){
		l=net[x][sz];
		if(visited[l.y])	continue;
		Next[x][sz].k=-1;
	}
	if(Z==1){//select
		lst.pb(x);
		while(!Q.empty())	Q.pop();
		sz=net[x].size();
		while(sz--){
			l=net[x][sz];
			if(visited[l.y])	continue;
			t[1][x][1]+=l.cost;
			Q.push({l.y,max(t[0][l.y][1],t[1][l.y][1]-l.cost),sz,1,t[0][l.y][1]<=t[1][l.y][1]-l.cost});//x,cost,idx,k,sl
		}
		for(i=2;i<=p;i++){
			if(Q.empty())	break;
			y=Q.top();Q.pop();
			t[1][x][i]=t[1][x][i-1]+y.cost;
			Next[x][y.idx]=y;
			z=y;
			z.k++;
			z.cost=max(t[0][z.x][z.k],t[1][z.x][z.k]-net[x][z.idx].cost)-y.cost;
			if(z.cost<=0)	continue;
			Q.push(z);
		}
	}else{//non-select
		while(!Q.empty())	Q.pop();
		sz=net[x].size();
		while(sz--){
			l=net[x][sz];
			if(visited[l.y])	continue;
			Q.push({l.y,max(t[0][l.y][1],t[1][l.y][1]+l.cost),sz,1,t[0][l.y][1]<=t[1][l.y][1]+l.cost});//x,cost,idx,k
		}
		for(i=1;i<=p;i++){
			if(Q.empty())	break;
			y=Q.top();Q.pop();
			t[0][x][i]=t[0][x][i-1]+y.cost;
			Next[x][y.idx]=y;
			z=y;
			z.k++;
			z.cost=max(t[0][z.x][z.k],t[1][z.x][z.k]+net[x][z.idx].cost)-y.cost;
			if(z.cost<=0)	continue;
			Q.push(z);
		}
	}
	sz=net[x].size();
	while(sz--){
		l=net[x][sz];
		if(visited[l.y])	continue;
		if(Next[x][sz].k==-1)	continue;
		make_lst(Next[x][sz].sl,Next[x][sz].x,Next[x][sz].k);
	}
	visited[x]=false;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,sum=0;
	node p;
	scanf("%d %d",&n,&k);
	for(i=2;i<=n;i++){
		scanf("%d %d %d",&x,&p.y,&p.cost);
		sum+=p.cost;
		net[x].pb(p);
		swap(x,p.y);net[x].pb(p);
	}
	dfs(1);
	printf("%d\n",sum-max(t[0][1][k],t[1][1][k]));
	if(t[0][1][k]>t[1][1][k])	make_lst(0,1,k);
	else	make_lst(1,1,k);
	sort(lst.begin(),lst.end());
	int sz=lst.size();
	for(i=0;i<sz;i++)	printf("%d ",lst[i]);
	printf("\n");
	return 0;
}
