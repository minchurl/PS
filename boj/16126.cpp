//fefe
#include<bits/stdc++.h>
//#include<inttypes.h>//__int64,__int128(?)
#define MAX_N 105
#define MAX_M 105
//vector&pair
#define pb push_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
//math
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))//Regardless of type
//for pair
#define fi first
#define se second
//infinit
#define LL_inf (1LL<<60)
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
#define inf 0x3fffffff
//MOD
#define MOD 1000000007LL
#define mod(x,m) (((x)%(m)+(m))%(m)) //-+-+
//operator(such as complex)
#define cpx_mod(x) (((LD)(((LL)x.real())%MOD)),((LD)(((LL)x.imag())%MOD)))

using namespace std;
//type
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef long double LD;
typedef complex<LD> Complex;
struct node{
	int s,e,f,sidx,eidx;
};
int n,m,arr[MAX_N][MAX_M];
int all_source,all_sink,from[MAX_N*MAX_M];
int chk[MAX_N*MAX_M],c;
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
queue<int> Q;
vector<node> net[MAX_N*MAX_M];
bool is_available(int x,int y){
	if(!x || !y || x>n || y>m)	return false;
	return true;
}
void make_edge(int s,int e,int f){
	int sidx=net[s].size(),eidx=net[e].size();
	net[s].pb({s,e,f,sidx,eidx});
	net[e].pb({e,s,0,eidx,sidx});
}
void make_vertex(int x,int y){
	if((x+y)%2){
		make_edge(m*(x-1)+y,n*m+1,4-arr[x][y]);
		all_sink+=4-arr[x][y];
	}else{
		make_edge(0,m*(x-1)+y,4-arr[x][y]);
		all_source+=4-arr[x][y];
	}
}
bool SPFA(){
	int x;
	while(Q.size())	Q.pop();
	chk[0]=c;
	Q.push(0);
	while(Q.size()){
		x=Q.front();Q.pop();
		if(x==n*m+1)	return true;
		for(node e:net[x]){
			if(chk[e.e]==c || !e.f)	continue;
			chk[e.e]=c;
			from[e.e]=e.eidx;
			Q.push(e.e);
		}
	}
	return false;
}
void change_edge(){
	int s,e=n*m+1,sidx,eidx;
	while(e){
		eidx=from[e];
		s=net[e][eidx].e;
		sidx=net[e][eidx].eidx;
		net[s][sidx].f--;
		net[e][eidx].f++;
		e=s;
	}
}
bool max_flow(){
	c++;
	bool y;
	while(1){
		if(!SPFA())	break;
		c++;
		all_sink--;
		change_edge();
	}
	return !all_sink;
}
int main(){
	freopen("input.txt","r",stdin);
	int i,j,k,x,y;
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			scanf("%d",&arr[i][j]);
			if(arr[i][j]<2)	return !printf("HOMELESS\n");
			make_vertex(i,j);
		}
	}
	for(i=1;i<=n;i++){
		for(j=1+(i+1)%2;j<=m;j+=2){
			for(k=0;k<4;k++){
				x=i+dx[k];y=j+dy[k];
				if(is_available(x,y) && (arr[i][j]!=2 || arr[x][y]!=2))	make_edge(m*(i-1)+j,m*(x-1)+y,1);
			}		
		}
	}
	if(all_source!=all_sink)	return !printf("HOMELESS\n");
	printf("%s\n",max_flow()?"HAPPY":"HOMELESS");
	return 0;
}
//end
