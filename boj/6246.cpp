#include<bits/stdc++.h>
using namespace std;
int n,q,ans;
int chk[10005];
int main(){
	int i,s,x;
	scanf("%d %d",&n,&q);
	while(q--){
		scanf("%d %d",&s,&x);
		while(s<=n){
			chk[s]=1;
			s+=x;
		}
	}
	ans=n;
	for(i=1;i<=n;i++)	ans-=chk[i];
	printf("%d\n",ans);
	return 0;
}
