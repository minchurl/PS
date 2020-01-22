#include<bits/stdc++.h>
#define MAX_N 10005
#define abs(x) ((x)>0?(x):(-(x)))
#define inv(x) ((x)>N?(x)-N:(x)+N)
#define pb push_back
using namespace std;
int N,M,finished[2*MAX_N],cnt,num[2*MAX_N],nn,ans[MAX_N],deg[2*MAX_N];
vector<int> net[2*MAX_N],nnet[2*MAX_N],V[2*MAX_N];
stack<int> st;
queue<int> Q;
int scc(int x){
	finished[x]=++cnt;
	st.push(x);
	int z=cnt,temp;
	for(int y:net[x]){
		if(finished[y]){
			if(!num[y])	z=min(z,finished[y]);
			continue;
		}
		temp=scc(y);
		z=min(z,temp);
	}
	if(z==finished[x]){
		nn++;
		while(st.top()!=x){num[st.top()]=nn;st.pop();}
		st.pop();
		num[x]=nn;
	}
	return z;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y;
	scanf("%d %d",&N,&M);
	while(M--){
		scanf("%d %d",&x,&y);
		if(x<0)	x=inv(abs(x));
		if(y<0)	y=inv(abs(y));
		net[inv(x)].pb(y);
		net[inv(y)].pb(x);
	}
	for(i=1;i<=2*N;i++){
		if(!num[i])	x=scc(i);
	}
	for(i=1;i<=2*N;i++){
		if(num[i]==num[inv(i)])	return !printf("0\n");
		V[num[i]].pb(i);
	}
	for(i=1;i<=2*N;i++){
		for(int z:net[i]){
			if(num[i]==num[z])	continue;
			nnet[num[i]].pb(num[z]);
			deg[num[z]]++;
		}
	}
	for(i=1;i<=nn;i++){
		if(!deg[i])	Q.push(i);
		finished[i]=0;
	}
	while(!Q.empty()){
		x=Q.front();Q.pop();
		for(int z:V[x]){
			if(!num[(z-1)%N+1])	ans[(z-1)%N+1]=(z>N?0:1);
			num[(z-1)%N+1]=0;
		}
		for(int z:nnet[x]){
			deg[z]--;
			if(!deg[z])	Q.push(z);
		}
	}
	printf("1\n");
	return 0;
	for(i=1;i<=N;i++)	printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
