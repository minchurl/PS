#include<bits/stdc++.h>
#define MAX_N 100005
#define pb push_back
using namespace std;
struct node{
	int x,y,c;
	bool operator < (const node d){
		return c<d.c;
	};
}con[MAX_N],Q[MAX_N];
vector<int> net[MAX_N],lst[MAX_N];
int n,m,q,C[MAX_N],pa[MAX_N],num[MAX_N],st[MAX_N],en[MAX_N];
int find_root(int x){return x==pa[x]?x:pa[x]=find_root(pa[x]);}
void connect(int x,int y){
	if(x==y)	return;
	pa[y]=x;num[x]+=num[y];
}
void reset(){
	for(int i=1;i<=n;i++){pa[i]=i;num[i]=1;}
	for(int i=1;i<=m;i++){lst[i].resize(0);}
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y,idx;
	bool z;
	scanf("%d %d",&n,&m);
	for(i=1;i<=m;i++)	scanf("%d %d %d",&con[i].x,&con[i].y,&con[i].c);
	sort(con+1,con+m+1);
	scanf("%d",&q);
	for(i=1;i<=q;i++)	scanf("%d %d",&Q[i].x,&Q[i].y);
	for(i=1;i<=q;i++){
		st[i]=1;
		en[i]=m+1;
	}
	z=true;
	while(z){
		reset();
		z=false;
		for(i=1;i<=q;i++){
			if(st[i]>=en[i])	continue;
			lst[(st[i]+en[i])>>1].pb(i);
		}
		for(i=1;i<=m;i++){
			connect(find_root(con[i].x),find_root(con[i].y));
			while(lst[i].size()){
				z=true;
				idx=lst[i].back();lst[i].pop_back();
				if(find_root(Q[idx].x)==find_root(Q[idx].y)){
					en[idx]=i;
					C[idx]=num[find_root(Q[idx].x)];
				}else	st[idx]=i+1;
			}
		}
	}
	for(i=1;i<=q;i++){
		if(st[i]==m+1)	printf("-1\n");
		else	printf("%d %d\n",con[st[i]].c,C[i]);
	}
	return 0;
}

