#include<bits/stdc++.h>
#define MAX_N 1048579
#define MAX_M 300005
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))
#define fi first
#define se second
#define LL_inf (1LL<<60)
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
#define inf 0x3fffffff
#define MOD 1000000007LL
#define cpx_mod(x) (((LD)(((LL)x.real())%MOD)),((LD)(((LL)x.imag())%MOD)))
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
typedef long double LD;
int n,ans,V[MAX_N];
int loc[MAX_N];
vector<int> L,R,lst;
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)	scanf("%d",&V[i]);
	int e=(1<<n);
	for(int i=0;i<=20;i++)	loc[(1<<i)]=i;
	for(int i=1;i<e;i++){
		reset(lst);
		reset(L);L.eb(0);
		reset(R);R.eb(0);
		for(int j=i;j>0;j-=(j&-j))	lst.eb(V[loc[j&-j]]);
		int m=lst.size();
		int sumx=0;
		for(int j=0;j<m/2;j++){
			int sz=L.size();
			for(int k=0;k<sz;k++)	L.eb(L[k]+lst[j]);
			sumx+=lst[j];
		}
		sort(L.begin(),L.end());
		int sumy=0;
		for(int j=m/2;j<m;j++)	sumy+=lst[j];
		if((sumx-sumy)%2)	continue;
		if(sumx==sumy){ans++;continue;}
		for(int j=m/2;j<m;j++){
			int sz=R.size(),k;
			for(k=0;k<sz;k++){
				R.eb(R[k]+lst[j]);
				int z=R[k]+lst[j]-(sumy-sumx)/2;
				if(z>=0 && binary_search(L.begin(),L.end(),z)){ans++;break;}
			}
			if(k!=sz)	break;
		}
	}
	printf("%d\n",ans);
	return 0;
}
