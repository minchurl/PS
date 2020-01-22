#include<bits/stdc++.h>
#define MAX_N 300005
using namespace std;
int n,s,q,arr[MAX_N],loc[MAX_N];
int main(){
	freopen("input.txt","r",stdin);
	int i,x;
	scanf("%d %d",&n,&q);
	for(i=1;i<=n;i++){
		scanf("%d",&arr[i]);
		loc[i]=i;
	}
	for(i=2;i<=n;i++){
		if(arr[i-1]<arr[i])	arr[i]=arr[i-1];
	}
	for(i=1;i<=n/2;i++){swap(arr[i],arr[n-i+1]);swap(loc[i],loc[n-i+1]);}
	s=1;
	for(i=1;i<=q;i++){
		scanf("%d",&x);
		if(x>arr[n])	break;
		s=lower_bound(arr+s,arr+n+1,x)-arr;
		s++;
	}
	if(i!=q+1)	return !printf("0\n");
	printf("%d\n",loc[s-1]);
	return 0;
}
