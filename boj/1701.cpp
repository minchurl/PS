#include<bits/stdc++.h>
#define MAX_N 5005
using namespace std;
int n,len,f[MAX_N],ans;
char s[MAX_N],a[MAX_N];
void make_f(){
	int i=0,j=-1;
	f[i]=j;
	while(i<=n){
		while(j+1 && s[i]!=s[j])	j=f[j];
		i++;j++;
		f[i]=j;
		ans=max(ans,j);
	}
}
int main(){
	freopen("input.txt","r",stdin);
	int i,j;
	scanf("%s",a);
	len=strlen(a);
	for(i=0;i<len;i++){
		n=0;
		for(j=i;j<=len;j++)	s[n++]=a[j];
		make_f();
	}
	printf("%d\n",ans);
	return 0;
}
