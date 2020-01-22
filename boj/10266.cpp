#include<bits/stdc++.h>
#define MAX_N 200005
using namespace std;
int n,m,k;
int in_s[MAX_N],a[MAX_N],b[2*MAX_N],f[MAX_N];
bool z;
void make_f(){
	int i,j;
	f[i=0]=j=-1;
	while(i<m){
		while(j+1 && a[i]-a[j])	j=f[j];
		i++;j++;
		f[i]=j;
	}
}
void kmp(){
	int i,j;
	i=j=-1;
	while(i<k){
		while(j+1 && b[i]-a[j])	j=f[j];
		i++;j++;
		if(j==m){
			z=true;
			return;
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	int i;
	scanf("%d",&n);
	for(i=0;i<n;i++)	scanf("%d",&in_s[i]);
	sort(in_s,in_s+n);
	m=0;
	for(i=1;i<n;i++)	a[m++]=in_s[i]-in_s[i-1];
	a[m++]=in_s[0]+360000-in_s[n-1];
	
	for(i=0;i<n;i++)	scanf("%d",&in_s[i]);
	sort(in_s,in_s+n);
	k=0;
	for(i=1;i<n;i++)	b[k++]=in_s[i]-in_s[i-1];
	b[k++]=in_s[0]+360000-in_s[n-1];
	for(i=k;i<2*k;i++)	b[i]=b[i-k];
	k*=2;
	make_f();
	kmp();
	printf("%s\n",z?"possible":"impossible");
	return 0;
}
