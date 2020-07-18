#include<bits/stdc++.h>
#define MAX_Q 500005
using namespace std;
struct node{
	int v;
	node *l, *r;
	node(int v, node *l, node *r): v(v), l(l), r(r){}
	node* update(int idx, int p){
		if(idx < 0)	return new node(v + 1, NULL, NULL);
		if(p>>idx&1)	return new node(v + 1, l, r->update(idx - 1, p));
		return new node(v + 1, l->update(idx - 1, p), r);
	}
};
int n;
node *root[MAX_Q];
int xorQ(int idx, node *l, node *r, int p){
	if(idx < 0)	return 0;
	if((p>>idx&1 && r->l->v - l->l->v) || r->r->v - l->r->v == 0)	return xorQ(idx - 1, l->l, r->l, p);
	return xorQ(idx-1, l->r, r->r, p)|(1<<idx);
}
int nQ(int idx, node *l, node *r, int p){
	if(idx < 0)	return r->v - l->v;
	if(p>>idx&1)	return r->l->v - l->l->v + nQ(idx - 1, l->r, r->r, p);
	return nQ(idx-1, l->l, r->l, p);
}
int kQ(int idx, node *l, node *r, int p){
	if(idx < 0)	return 0;
	if(r->l->v - l->l->v < p)	return kQ(idx - 1, l->r, r->r, p - r->l->v + l->l->v)|(1<<idx);
	return kQ(idx-1, l->l, r->l, p);
}
int main(){
	freopen("input.txt","r",stdin);
	int q,ty;
	int L, R, x, y, k;
	scanf("%d",&q);
	root[0] = new node(0, NULL, NULL);
	root[0]->l = root[0];
	root[0]->r = root[0];
	n = 1;
	while(q--){
		scanf("%d",&ty);
		if(ty == 1){
			scanf("%d",&x);
			root[n] = root[n-1]->update(18, x);
			n++;
		}else if(ty == 2){
			scanf("%d %d %d",&L,&R,&x);
			printf("%d\n",xorQ(18, root[L-1], root[R], x));
		}else if(ty == 3){
			scanf("%d",&k);
			n -= k;
		}else if(ty == 4){
			scanf("%d %d %d",&L,&R,&k);
			printf("%d\n",nQ(18, root[L-1], root[R], k));
		}else if(ty == 5){
			scanf("%d %d %d",&L,&R,&k);
			printf("%d\n",kQ(18, root[L-1], root[R], k));
		}
	}
	return 0;
}