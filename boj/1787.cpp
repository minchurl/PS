#include<bits/stdc++.h>
#define MAX_N 1000005
using namespace std;
int n,f[MAX_N];
long long ans;
char s[MAX_N],a[MAX_N];
void make_f(){
	int i,j;
	i=0,j=-1;
	f[i]=j;
	while(i<n){
		while(j+1 && s[i]!=s[j])	j=f[j];
		i++;j++;
		f[i]=j;
	}
}
int kmp(){
	int i,j;
	i=0,j=-1;
	while(i<n){
		while(j+1 && s[i]!=s[j])	j=f[j];
		i++;j++;
		if(i==n){
			return 0;
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	int i;
	scanf("%d",&n);
	scanf("%s",s);
	make_f();
	for(i=1;i<=n;i++){
		while(f[f[i]]>0)	f[i]=f[f[i]];
		ans+=(long long)(f[i]?1:0)*((long long)(i-f[i]));
	}
	printf("%lld\n",ans);
	return 0;
}
