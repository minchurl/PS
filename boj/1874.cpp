#include<bits/stdc++.h>
#define MAX_N 100005
#define pb push_back
using namespace std;
int n,st[MAX_N],stn,V[MAX_N],vn;
vector<int> ans;
int main(){
	int i,x;
	scanf("%d",&n);
	stn=vn=0;
	for(i=1;i<=n;i++){
		scanf("%d",&x);
		while(vn<x){
			stn++;vn++;
			st[stn]=vn;
			ans.pb(1);
		}
		if(st[stn]!=x)	return !printf("NO\n");
		stn--;
		ans.pb(0);
	}
	for(int y:ans)	printf("%c\n",y?'+':'-');
	return 0;
}
