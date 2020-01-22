#include<bits/stdc++.h>
#define MAX_N 205
#define MAX_I 10
#define MAX_S 25
using namespace std;
int n,m,k,idx[MAX_I],f[2*MAX_N],ans;
char in_s[MAX_I][MAX_S],arr[2*MAX_N];
bool chk[MAX_N];
void connect(){m=0;for(int i=0;i<n;i++)	for(int j=0;in_s[idx[i]][j];j++)	arr[m++]=in_s[idx[i]][j];}
void make_f(){
	int i,j;
	i=0;j=-1;
	f[i]=j;
	while(i<2*m){
		while(j!=-1 && arr[i]!=arr[j])	j=f[j];
		i++;j++;
		f[i]=j;
	}
}
int solve(){
	int i,l,c=k;
	for(i=m;i<2*m;i++)	arr[i]=arr[i-m];
	make_f();
	for(l=m+1;l<=2*m;l++)	if(f[l]>=m)	break;
	l-=m;l%=m;
	for(i=0;i<m;i++)	chk[i]=false;
	chk[0]=true;
	i=l;c--;
	while(!chk[i]){
		chk[i]=true;
		i+=l;i%=m;
		c--;
	}
	return !c;
}
void make_arr(int c){
	if(c==n){
		connect();
		ans+=solve();
		return;
	}
	for(int i=c;i<n;i++){
		swap(idx[c],idx[i]);
		make_arr(c+1);
		swap(idx[c],idx[i]);
	}
}
int main(){
	freopen("input.txt","r",stdin);
	int i;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%s",in_s[i]);
		idx[i]=i;
	}
	scanf("%d",&k);
	make_arr(0);
	printf("%d\n",ans);
	return 0;
}
