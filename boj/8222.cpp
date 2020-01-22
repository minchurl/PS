#include<bits/stdc++.h>
#define inf 100000
#define MAX_N 1000005
using namespace std;
int n,pn;
int dst[MAX_N],ans_dst[MAX_N],num[MAX_N],arr[MAX_N],prime[MAX_N],ans[MAX_N];
queue<int> Q,R;
void make_prime(){
	int i,j;
	prime[pn++]=2;
	for(i=3;i<=1000;i+=2){
		for(j=1;j<pn;j++){
			if(i%prime[j]==0)	break;
		}
		if(j==pn)	prime[pn++]=i;
	}
}
int main(){
	freopen("input.txt","r",stdin);
	int i,j,x,y,z=0;
	scanf("%d",&n);
	make_prime();
	for(i=1;i<=1000000;i++)	dst[i]=ans_dst[i]=ans[i]=inf;
	for(i=1;i<=n;i++){
		scanf("%d",&arr[i]);
		dst[arr[i]]=0;
		if(num[arr[i]]){
			ans[i]=num[arr[i]];
			if(ans[num[arr[i]]]==inf)	ans[num[arr[i]]]=i;
			ans_dst[i]=ans_dst[num[arr[i]]]=0;
		}else	num[arr[i]]=i;
	}
	for(j=1;j<=n;j++){
		x=arr[j];
		for(i=0;i<pn;i++){
			if(x%prime[i]==0){
				y=x/prime[i];
				if(num[y] && num[x]-num[y]){
					if(ans_dst[num[y]]>dst[x]+dst[y]+1 || (ans_dst[num[y]]==dst[x]+dst[y]+1 && num[x]<ans[num[y]])){
						ans_dst[num[y]]=dst[x]+dst[y]+1;
						ans[num[y]]=num[x];
					}
					if(ans_dst[num[x]]>dst[x]+dst[y]+1 || (ans_dst[num[x]]==dst[x]+dst[y]+1 && num[y]<ans[num[x]])){
						ans_dst[num[x]]=dst[x]+dst[y]+1;
						ans[num[x]]=num[y];
					}
				}else if(dst[y]>dst[x]+1){
					num[y]=num[x];
					dst[y]=dst[x]+1;
					Q.push(y);
				}
			}
			if((long long)x*(long long)prime[i]<=1000000){
				y=x*prime[i];
				if(num[y] && num[x]-num[y]){
					if(ans_dst[num[y]]>dst[x]+dst[y]+1){
						ans_dst[num[y]]=dst[x]+dst[y]+1;
						ans[num[y]]=num[x];
						if(ans_dst[num[x]]>dst[x]+dst[y]+1){
							ans_dst[num[x]]=dst[x]+dst[y]+1;
							ans[num[x]]=num[y];
						}
					}
				}else if(dst[y]>dst[x]+1){
					num[y]=num[x];
					dst[y]=dst[x]+1;
					Q.push(y);
				}
			}
		}

		x=arr[j];
		for(i=0;i<pn;i++){
			while(x%prime[i]==0)	x/=prime[i];
			if(x==1)	break;
		}
		if(x==1)	continue;
		x=arr[j]/x;
		//printf("%d %d : %d %d %d %d\n",x,j,dst[x],num[x],ans_dst[j],ans[j]);
		if(num[x] && num[x]-i){
			if(dst[x]+1<ans_dst[j] || (dst[x]+1==ans_dst[j] && ans[j]>num[x])){
				ans[j]=num[x];
				ans_dst[j]=dst[x]+1;
			}
			if(dst[x]+1<ans_dst[num[x]] || (dst[x]+1==ans_dst[num[x]] && ans[num[x]]>j)){
				ans[num[x]]=j;
				ans_dst[num[x]]=dst[x]+1;
			}
		}else if(dst[x]==inf){
			dst[x]=1;
			num[x]=j;
			Q.push(j);
		}
	}
	while(!Q.empty()){
		x=Q.front();Q.pop();
		
		//printf("%d : %d\n",x,dst[x]);
		for(i=0;i<pn;i++){
			if(x%prime[i]==0){
				y=x/prime[i];
				if(num[y] && num[x]-num[y]){
					if(ans_dst[num[y]]>dst[x]+dst[y]+1 || (ans_dst[num[y]]==dst[x]+dst[y]+1 && num[x]<ans[num[y]])){
						ans_dst[num[y]]=dst[x]+dst[y]+1;
						ans[num[y]]=num[x];
					}
					if(ans_dst[num[x]]>dst[x]+dst[y]+1 || (ans_dst[num[x]]==dst[x]+dst[y]+1 && num[y]<ans[num[x]])){
						ans_dst[num[x]]=dst[x]+dst[y]+1;
						ans[num[x]]=num[y];
					}
				}else if(dst[y]>dst[x]+1){
					num[y]=num[x];
					dst[y]=dst[x]+1;
					Q.push(y);
				}
			}
			if((long long)x*(long long)prime[i]<=1000000){
				y=x*prime[i];
				if(num[y] && num[x]-num[y]){
					if(ans_dst[num[y]]>dst[x]+dst[y]+1){
						ans_dst[num[y]]=dst[x]+dst[y]+1;
						ans[num[y]]=num[x];
						if(ans_dst[num[x]]>dst[x]+dst[y]+1){
							ans_dst[num[x]]=dst[x]+dst[y]+1;
							ans[num[x]]=num[y];
						}
					}
				}else if(dst[y]>dst[x]+1){
					num[y]=num[x];
					dst[y]=dst[x]+1;
					Q.push(y);
				}
			}
		}
	}

	for(i=1;i<=n;i++)	printf("%d\n",ans[i]);
	return 0;
}
