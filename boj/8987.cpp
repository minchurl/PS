#include<bits/stdc++.h>
#define MAX_N 300005
#define pb push_back
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pil;
struct node{
	LL s,e,y,idx;
}arr[MAX_N];
struct Tree{
	LL maxx,ch_val,from;
}tree[4*MAX_N];
struct Range{
	LL s,e;
}range[MAX_N];
LL n,m,k;
LL val[MAX_N],h[MAX_N],pa[MAX_N],V[MAX_N];
LL E,cnt,ans;
bool chk[MAX_N];
stack<LL> st;
vector<LL> net[MAX_N];
void update(LL x,LL l,LL r,LL ps,LL pe,LL v,LL F){
	if(pe<l || ps>r)	return;
	if(l>r)	return;
	LL mid=(l+r)>>1;
	if(ps<=l && r<=pe){
		tree[x].ch_val+=v;
		tree[x].maxx+=v;
		if(ps==pe && F!=k+2)	tree[x].from=F;
		return;
	}
	update(2*x,l,mid,ps,pe,v,F);
	update(2*x+1,mid+1,r,ps,pe,v,F);
	tree[x].from=tree[2*x].from;
	if(tree[2*x].maxx<tree[2*x+1].maxx)	tree[x].from=tree[2*x+1].from;
	tree[x].maxx=max(tree[2*x].maxx,tree[2*x+1].maxx)+tree[x].ch_val;
}
void dfs(LL x){
	range[x].s=++cnt;
	chk[x]=true;
	V[x]=V[pa[x]]+val[x];
	for(LL y:net[x]){
		if(chk[y])	continue;
		dfs(y);
	}
	range[x].e=cnt;
}
int main(){
	freopen("input.txt","r",stdin);
	LL i,x,y;
	scanf("%lld",&n);
	scanf("%*d %*d");
	m=0;
	for(i=2;i<n;i+=2){
		m++;
		scanf("%lld %lld",&arr[m].s,&arr[m].y);
		scanf("%lld %*d",&arr[m].e);
		arr[m].y++;
	}
	scanf("%*d %*d");
	E=arr[m].e;
	
	st.push(0);
	k=0;
	for(i=1;i<=m;i++){
		while(!st.empty() && arr[st.top()].y>arr[i].y)	st.pop();
		if(arr[i].y==arr[st.top()].y){
			arr[i].idx=arr[st.top()].idx;
			val[arr[i].idx]+=(arr[i].e-arr[st.top()].e);
			st.pop();
		}else{
			arr[i].idx=++k;
			val[arr[i].idx]=(arr[i].e-arr[st.top()].e);
			h[arr[i].idx]=arr[i].y;
			pa[arr[i].idx]=arr[st.top()].idx;
		}
		st.push(i);
	}
	while(!st.empty())	st.pop();
	
	arr[m+1].s=arr[m+1].e=E;
	st.push(m+1);
	for(i=m;i>=1;i--){
		while(!st.empty() && arr[st.top()].y>=arr[i].y)	st.pop();
		if(h[pa[arr[i].idx]]<arr[st.top()].y)	pa[arr[i].idx]=arr[st.top()].idx;

		if(!chk[arr[i].idx])val[arr[i].idx]+=arr[st.top()].s-arr[i].e;
		chk[arr[i].idx]=true;
		st.push(i);
	}
	while(!st.empty())	st.pop();
	

	for(i=0;i<=k;i++){
		chk[i]=false;
		val[i]*=(h[i]-h[pa[i]]);
	}
	
	for(i=1;i<=k;i++)	net[pa[i]].pb(i);
	cnt=0;
	dfs(0);
	
	for(i=0;i<=k;i++)	update(1,1,cnt,range[i].s,range[i].s,V[i],i);
	
	scanf("%lld",&m);
	if(!m)	return !printf("0\n");
	while(m--){
		x=tree[1].maxx;
		y=tree[1].from;
		ans+=x;
		while(y && chk[y]){
			chk[y]=false;
			update(1,1,cnt,range[y].s,range[y].e,-val[y],k+2);
			y=pa[y];
		}
	}
	printf("%lld\n",ans-E);
	return 0;
}
