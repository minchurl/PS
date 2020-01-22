#include<stdio.h>
#define distance(x,y,z,k) ((x-z)*(x-z)+(y-k)*(y-k))
int main(){
	int T,p,q,r,s,n,i,R,x,y,ans;
	freopen("input.txt","r",stdin);
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d %d",&p,&q,&r,&s);
		scanf("%d",&n);
		ans=0;
		for(i=0;i<n;i++){
			scanf("%d %d %d",&x,&y,&R);
			ans+=(distance(p,q,x,y)>R*R)^(distance(r,s,x,y)>R*R);
		}
		printf("%d\n",ans);
	}
	return 0;
}
