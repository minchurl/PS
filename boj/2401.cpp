#include<bits/stdc++.h>
#define MAX_N 100005
#define pb push_back
using namespace std;
int long_len,len,n,f[MAX_N],t[MAX_N];
char s[MAX_N],long_s[MAX_N];
vector<int> pre[MAX_N];
void make_f(){
	int i,j;
	f[i=0]=j=-1;
	while(i<len){
		while(j+1 && s[i]-s[j])	j=f[j];
		i++;j++;
		f[i]=j;
	}
}
void kmp(){
	int i,j;
	i=j=-1;
	while(i<long_len){
		while(j+1 && long_s[i]-s[j])	j=f[j];
		i++;j++;
		if(j==len){
			j=f[j];
			pre[i].pb(len);
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	int i;
	scanf("%s",long_s);
	long_len=strlen(long_s);
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%s",s);
		len=strlen(s);
		make_f();
		kmp();
	}
	for(i=1;i<=long_len;i++){
		t[i]=t[i-1];
		for(int y:pre[i])	t[i]=max(t[i],t[i-y]+y);
	}
	printf("%d\n",t[long_len]);
	return 0;
}
