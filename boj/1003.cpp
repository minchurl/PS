#include<stdio.h>
long long f[50];
int main(){
    f[0]=0;f[1]=1;
    for(int i=2;i<50;i++)    f[i]=f[i-1]+f[i-2];
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        if(n==0)    printf("1 0\n");
        else    printf("%lld %lld\n",f[n-1],f[n]);
    }
    return 0;
}

