#include<bits/stdc++.h>
using namespace std;
int n,len,a[2005],ans;
char s[2005],in_s[2005];
int main(){
	int i,r,p;
	scanf("%s",in_s);
	len=strlen(in_s);
	for(i=0;i<len;i++){
		s[++n]=in_s[i];
		s[++n]='*';
	}
	r=0;
	p=0;
	for(i=1;i<=n;i++){
		if(i<=r)	a[i]=max(a[2*p-i],r-i);
		else	a[i]=0;
		while(i-a[i]-1>0 && i+a[i]+1<=n && s[i-a[i]-1]==s[i+a[i]+1])	a[i]++;
		if(r<i+a[i])	r=i+a[i],p=i;
	}
	for(i=1;i<=n;i++){ans=(ans+(a[i]+!(i%2))/2+i%2)%10007;printf("%d : %d\n",i,a[i]);}
	printf("%d\n",ans);
	return 0;
}
