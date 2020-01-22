#include<bits/stdc++.h>
#define MAX_N 1000005
using namespace std;
int n,m;
int arr[MAX_N],temp[MAX_N];
void Xor(int x){
	int i;
	x%=n;
	for(i=0;i<n;i++)	temp[i]=arr[i]^arr[(i+x)%n];
	for(i=0;i<n;i++)	arr[i]=temp[i];
}
int main(){
	int i;
	scanf("%d %d",&n,&m);
	for(i=0;i<n;i++)	scanf("%d",&arr[i]);
	for(i=0;i<=30;i++){
		if(m&(1<<i))	Xor((1<<i));
	}
	for(i=0;i<n;i++)	printf("%d\n",arr[i]);
	return 0;
}
