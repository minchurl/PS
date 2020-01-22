#include<stdio.h>
int main(){
	int n,i,j,x,chk[500]={0,};
	chk[0]=true;
	for(i=0;i<3;i++){scanf("%d",&x);for(j=0;j<=300;j++)	chk[j+x]|=chk[j];}
	scanf("%d",&n);printf("%d\n",chk[n]);
}
