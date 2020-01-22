#include<bits/stdc++.h>
#define MAX_N 1000005
#define pb push_back
using namespace std;
struct node{
	int x,s,d;
};
struct cmps{
	bool operator()(const node x,const node y){
		if(x.s==y.s)	return x.x<y.x;
		return x.s<y.s;
	}
};
struct cmpd{
	bool operator()(const node x,const node y){
		if(x.d==y.d)	return x.x<y.x;
		return x.d<y.d;
	}
};
priority_queue<node,vector<node>,cmps> Ss;
priority_queue<node,vector<node>,cmpd> Sd;
bool chk[MAX_N];
vector<int> lst,net[MAX_N];
int n,l,from[MAX_N],num[MAX_N],vc,ans,visited[MAX_N];
bool is_root[MAX_N];
queue<int> Q;
int make_num(int x){
    int y,sz;
    num[x]=1;
    while(!Q.empty())	Q.pop();
    Q.push(x);
    visited[x]=++vc;
    from[x]=-1;
    while(!Q.empty()){
        x=Q.front();Q.pop();
        sz=net[x].size();
        while(sz--){
            y=net[x][sz];
		    if(is_root[y] || visited[y]==vc)	continue;
            visited[y]=vc;
            num[y]=num[x]+1;
            from[y]=x;
            Q.push(y);
        }
    }
    return x;
}
void add_lst(int x){
    while(x!=-1){
        lst.pb(x);
        x=from[x];
    }
}
void update_lst(){
	int x,y,z,p;
	int sz=lst.size(),ssz;
	while(sz--){
		y=lst[sz];
		is_root[y]=true;
	}
	sz=lst.size();
	while(sz--){
		y=lst[sz];
		ssz=net[y].size();
		while(ssz--){
			z=net[y][ssz];
			if(is_root[z])	continue;
			vc++;
			from[z]=-1;
			x=make_num(z);
			p=num[x];
			vc++;
			
			x=make_num(x);
			Sd.push({z,p,num[x]});Ss.push({z,p,num[x]});
		}
	}
	lst.resize(0);
}
int main(){
	freopen("input.txt","r",stdin);
	int i,x,y;
	scanf("%d %d",&n,&l);
	for(i=1;i<n;i++){
		scanf("%d %d",&x,&y);
		net[x].pb(y);net[y].pb(x);
	}
	if(!l)	return !printf("0\n");
	x=make_num(1);
	y=num[x];
	
	x=make_num(x);
	Ss.push({x,y,num[x]});Sd.push({x,y,num[x]});//idx,s,d
	node p,q,r;
	while(l-- && !Sd.empty() && !Ss.empty()){

		//p=Sd.;
		while(1){
			p=Sd.top();
			if(!chk[p.x])	break;
			Sd.pop();
		}
		while(1){
			q=Ss.top();
			if(!chk[q.x])	break;
			Ss.pop();
		}
		Ss.pop();
		while(1){
			r=Ss.top();
			if(!chk[r.x])	break;
			Ss.pop();
		}
		if(Ss.empty()){
			chk[p.x]=true;
			Sd.pop();
			ans+=p.d;
			x=make_num(p.x);
		
			y=make_num(x);
			add_lst(y);
		}else{
			r=Ss.top();
			if(q.s+r.s<p.d){
				chk[p.x]=true;
				Sd.pop();
				Ss.push(q);
			
				ans+=p.d;
				x=make_num(p.x);
			
				y=make_num(x);
				add_lst(y);
			}else{
				Ss.pop();
				chk[q.x]=chk[r.x]=true;
			
				ans+=q.s+r.s;
				x=make_num(q.x);
			
				add_lst(x);
				x=make_num(r.x);
				add_lst(x);
			}
		}
		update_lst();
	}
	printf("%d\n",ans);
	return 0;
}
