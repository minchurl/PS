#include<bits/stdc++.h>
#define inf 0x3fffffff
using namespace std;
struct node{
	int t[2][2];
	node *l,*r;
	node(int tt[2][2],node *l,node *r){
		int i,j;
		for(i=0;i<2;i++){
			for(j=0;j<2;j++)	t[i][j]=tt[i][j];
		}
		l=l;
		r=r;
	}
};
node *root;
int arr[200005][2],ttt[2][2]={{1,1},{1,1}},ud[2][2];
void make_ud(int x,int y){
	int i,j;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++)	ud[i][j]=(arr[x][i]<=arr[y][j]?1:0);
	}
}
node* make_tree(int idx){
	node *x;
	x=new node(ttt,NULL,NULL);
	if(idx<0)	return x;
	x->l=make_tree(idx-1);
	x->r=make_tree(idx-1);
	return x;
}
void Copy(node *x){
	int i,j;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++)	x->t[i][j]=ud[i][j];
	}
}
void mul_copy(node *x){
	int i,j,k;
	node *l,*r;
	l=x->l;
	r=x->r;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			x->t[i][j]=0;
			for(k=0;k<2;k++)	x->t[i][j]|=((l->t[i][k])*(r->t[k][j]));
		}
	}
}
void update(int idx,node* x,int p){
	if(idx<0){Copy(x);return;}
	if(p>>idx&1)	update(idx-1,x->r,p);
	else	update(idx-1,x->l,p);
	mul_copy(x);
	return;
}
bool is_ok(){
	int i,j;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++)	if(root->t[i][j])	return true;
	}
	return false;
}
int main(){
	freopen("input.txt","r",stdin);
	int n,i,x,y;
	scanf("%d",&n);
	arr[n+1][0]=arr[n+1][1]=inf;
	for(i=1;i<=n;i++)	scanf("%d %d",&arr[i][0],&arr[i][1]);
	root=make_tree(19);
	for(i=1;i<=n;i++){
		make_ud(i,i+1);
		update(19,root,i);
	}
	scanf("%d",&n);
	while(n--){
		scanf("%d %d",&x,&y);
		swap(arr[x][0],arr[y][0]);swap(arr[x][1],arr[y][1]);
		
		make_ud(x-1,x);update(19,root,x-1);
		make_ud(x,x+1);update(19,root,x);
		
		make_ud(y-1,y);update(19,root,y-1);
		make_ud(y,y+1);update(19,root,y);
		printf("%s\n",(is_ok())?"TAK":"NIE");
	}
	return 0;
}
