#include<bits/stdc++.h>
#define MAX_N 1000005
using namespace std;
int n;
int f[MAX_N];
char s[MAX_N];
void make_f(){
	int i,j;
	i=0;j=-1;
	f[0]=-1;
	while(i<n){
		while(j+1 && s[i]!=s[j])	j=f[j];
		i++;j++;
		f[i]=j;
	}
}
int main(){
	scanf("%d",&n);
	scanf("%s",s);
	make_f();
	printf("%d\n",n-f[n]);
	return 0;
}
