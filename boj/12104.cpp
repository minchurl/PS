#include<bits/stdc++.h>
#define MAX_N 200005
using namespace std;
int n,ans,f[MAX_N];
char a[MAX_N],b[MAX_N];
void make_f(){
	int i=0,j=-1;
	f[i]=j;
	while(i<n){
		while(j+1 && a[i]-a[j])	j=f[j];
		i++;j++;
		f[i]=j;
	}
}
void kmp(){
	int i=-1,j=-1;
	while(i<2*n-1){
		while(j+1 && b[i]-a[j])	j=f[j];
		i++;j++;
		if(j==n){ans++;j=f[j];}
	}
}
int main(){
	int i;
	scanf("%s",a);scanf("%s",b);n=strlen(a);
	for(i=n;i<2*n;i++)	b[i]=b[i-n];
	make_f();
	kmp();
	printf("%d\n",ans);
	return 0;
}
