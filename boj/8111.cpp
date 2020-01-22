#include<bits/stdc++.h>
#define MAX_N 105
using namespace std;
int n,t[MAX_N],chk[2000005],Z;
int update(int st){
	while(t[st]>=10){
		t[st+1]+=t[st]/10;
		t[st]%=10;
		st++;
	}
	if(st>=n){
		if(t[st]==0)	n=st;
		else	n=st+1;
	}
	int i=0,Y=0,e=0;
	while(i<n && t[i]<2)	i++;
	for(;i<n;i++)	Y=Y*10+t[i];
	return Y;
}
void add(int st,int x,bool z,int y){
	int i,m;
	int temp[MAX_N]={0,};
	/*printf("%d %d %d\n",st,n,y);
	for(i=n-1;i>=0;i--)	printf("%d",t[i]);
	printf("\n");*/
	if(st==n){
		Z=true;
		return;
	}
	if(st && t[st]<=1){
		add(st+1,x,true,y);
		return;
	}
	for(i=0;i<10;i++){
		if((t[st]+x*i)%10<=1 && z|i){
			for(int j=0;j<=n;j++)	temp[j]=t[j];
			t[st]+=x*i;
			m=n;
			y=update(st);
			if(y<=1 || !chk[y]){
				chk[y]=true;
				add(st+1,x,true,y);
				chk[y]=false;
				if(Z)	return;
			}
			for(int j=0;j<=n;j++)	t[j]=temp[j];
			n=m;
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	int test,x,i;
	scanf("%d",&test);
	while(test--){
		scanf("%d",&x);
		n=1;
		for(i=0;i<=105;i++)	t[i]=0;
		Z=false;
		add(0,x,false,0);
		for(i=n-1;i>=0;i--)	printf("%d",t[i]);
		printf("\n");
	}
	return 0;
}
