#include<bits/stdc++.h>
#define MOD 1000000007LL
#define LL long long
using namespace std;
LL pow(LL x,LL y){
	if(y==0)	return 1;
	if(y==1)	return x;
	LL z=pow(x,y/2);
	z*=z;z%=MOD;
	if(y%2){z*=x;z%=MOD;}
	return z;
}
int main(){
	freopen("input.txt","r",stdin);
	LL a,b,x,y,n,m,p,q,r;
	scanf("%lld %lld",&a,&b);
	scanf("%lld",&n);
	while(n--){
		scanf("%lld %lld %lld",&x,&y,&m);
		r=(pow(a,x-y)*pow(b,y-1))%MOD;
		if(a==b){
			if(a==1){
				if(m%2)	p=((((m+1)/2)%MOD)*(m%MOD))%MOD;
				else	p=(((m+1)%MOD)*((m/2)%MOD))%MOD;
				printf("%lld\n",p);
				continue;
			}
			p=(((pow(a,m)-1+MOD)%MOD)*(pow(a-1,MOD-2))%MOD);
			p=(((pow(a,m)*(m%MOD))%MOD)+p)%MOD;
			p=(p*(pow(a-1,MOD-2)))%MOD;
			p=(p*r)%MOD;
			printf("%lld\n",p);
			continue;
		}
		
		
		if(a==1)	p=m%MOD;
		else{p=(pow(a,m+1)-a+MOD)%MOD;p=(pow(a-1,MOD-2)*p)%MOD;}
		
		if(b==1)	q=m%MOD;
		else{q=(pow(b,m+1)-b+MOD)%MOD;q=(pow(b-1,MOD-2)*q)%MOD;}
		
		
		p=(p-q+MOD)%MOD;
		p=(pow(((a-b+MOD)%MOD),MOD-2)*p)%MOD;
		p=(p*r)%MOD;
		printf("%lld\n",p);
	}
	return 0;
}
