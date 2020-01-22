#include<stdio.h>
#define sq(x) ((x)*(x))
int main(){
    int t,a,b,p,c,d,q;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d %d %d %d %d",&a,&b,&p,&c,&d,&q);
        if(a==c && b==d){printf("%d\n",(p==q)?-1:0);continue;}
        int x=sq(a-c)+sq(b-d);
        int y=sq(p+q);
        int z=sq(p-q);
        if(x<z || x>y){
        	printf("0\n");
        	continue;
        }
        if(x==z || x==y)	printf("1\n");
        else	printf("2\n");
    }
    return 0;
}
