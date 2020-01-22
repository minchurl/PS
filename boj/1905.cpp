#include<bits/stdc++.h>
using namespace std;
struct node{
	int val;
	node *l,*r;
	node(int val,node *l,node *r):val(val),l(l),r(r){}
}*root[1005];
int Lx,Ly,q;
int ans;
node *make(int idx){
	if(idx<0)	return new node(0,NULL,NULL);
	return new node(0,make(idx-1),make(idx-1));
}
int read(int idx,node *x,int s,int e){
	if(idx<0 || (!s && e==(1<<(idx+1))-1))	return x->val;
	if(((e>>idx)&1)==0)	return read(idx-1,x->l,s,e);
	else if(s>>idx&1)	return read(idx-1,x->r,s-(1<<idx),e-(1<<idx));
	else{
		int p,q;
		p=read(idx-1,x->l,s,(1<<(idx))-1);
		q=read(idx-1,x->r,0,e-(1<<(idx)));
		return max(p,q);
	}
}

void update(int idx,node *x,int s,int e,int z){
	x->val=max(x->val,z);
	if(idx<0 || (!s && e==(1<<(idx+1))-1)){
		if(idx<0)return;
	}
	
	if(((e>>idx)&1)==0)	update(idx-1,x->l,s,e,z);
	else if(s>>idx&1)	update(idx-1,x->r,s-(1<<idx),e-(1<<idx),z);
	else{
		update(idx-1,x->l,s,(1<<(idx))-1,z);
		update(idx-1,x->r,0,e-(1<<(idx)),z);
	}
}
int main(){
	freopen("input.txt","r",stdin);
	int i,lx,ly,lz,px,py,x,y;
	scanf("%d %d %d",&Lx,&Ly,&q);
	for(i=0;i<=Lx+3;i++)	root[i]=make(9);
	while(q--){
		scanf("%d %d %d %d %d\n",&lx,&ly,&lz,&px,&py);
		y=0;
		for(i=px;i<=px+lx-1;i++){x=read(9,root[i],py,py+ly-1);y=max(x,y);}
		for(i=px;i<=px+lx-1;i++)	update(9,root[i],py,py+ly-1,y+lz);
		ans=max(ans,y+lz);
	}
	printf("%d\n",ans);
	return 0;
}

