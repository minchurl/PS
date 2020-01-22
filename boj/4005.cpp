#include<bits/stdc++.h>
#define MAX_N 1000005
#define counter(x) (n+m+(x))
using namespace std;
int n,m,k,pa[5*MAX_N];
int find_pa(int x){return x==pa[x]?x:pa[x]=(find_pa(pa[x]));}
void do_union(int x,int y){pa[find_pa(x)]=find_pa(y);}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y,c;
	scanf("%d %d %d",&n,&m,&k);
	for(i=1;i<=2*(n+m);i++)	pa[i]=i;
	while(k--){
		scanf("%d %d %d",&x,&y,&c);
		c^=(x&y&1);y+=n;
		if(!c){do_union(x,counter(y));do_union(y,counter(x));}
		else{do_union(x,y);do_union(counter(x),counter(y));}
	}
	int ans=1,cnt=0;
	for(i=1;i<=2*(n+m);i++){
		if(find_pa(i)==find_pa(counter(i)))	return !printf("0\n");
		if(find_pa(i)==i)	cnt++;
	}
	cnt/=2;
	for(i=0;i<cnt-1;i++)	ans=(ans*2)%((int)1e9);
	printf("%d\n",ans);
	return 0;
}
