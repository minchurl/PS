#include<bits/stdc++.h>
#define fi first
#define se second
#define MAX_N 100005
using namespace std;
char in_s[25];
int pa[MAX_N],num[MAX_N],m;
unordered_map<string,int> vis;
int find_pa(int x){return x==pa[x]?pa[x]:pa[x]=find_pa(pa[x]);}
int include(){
	unordered_map<string,int>::iterator it = vis.find(in_s);
	if(it == vis.end()){
		vis[in_s]=++m;
		pa[m]=m;
		num[m]=1;
	}else	return it->second;
}
int main(){
	int i,j,x,y,TC,n;
	scanf("%d",&TC);
	for(i=0;i<TC;i++){
		scanf("%d",&n);
		m=0;
		for(j=0;j<n;j++){
			scanf("%s",in_s);x=include();
			scanf("%s",in_s);y=include();
			
			x=find_pa(x);
			y=find_pa(y);
			if(x==y){
				printf("%d\n",num[x]);
				continue;
			}
			pa[y]=x;
			num[x]+=num[y];
			printf("%d\n",num[x]);
		}
		vis.clear();
	}
	return 0;
}

