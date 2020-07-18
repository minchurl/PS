#include<bits/stdc++.h>
#define MAX_N 2000005
#define inf 0x3fffffff
using namespace std;
struct node{
    int s, e;
}tree[4 * MAX_N];
void merge(int x, int s, int e){
    if(e <= tree[x].s){
        tree[x].s = e;
        tree[x].e = e;
        return;
    }else if(s >= tree[x].e){
        tree[x].s = s;
        tree[x].e = s;
        return;
    }
    tree[x].s = max(tree[x].s, s);
    tree[x].e = min(tree[x].e, e);
    return;
}
void spread(int x){
    merge(2 * x, tree[x].s, tree[x].e);
    merge(2 * x + 1, tree[x].s, tree[x].e);
    tree[x].s = 0;
    tree[x].e = inf;
}
void update(int x, int l, int r, int s, int e, int op, int v){
    if(e < l || s > r)  return;
    if(l != r){
        spread(x);
    }
    if(s <= l && r <= e){
        merge(x, ((op == 1) ? v : 0), ((op == 1) ? inf : v));
        return;
    }
    int mid = (l + r) >> 1;
    update(2 * x, l, mid, s, e, op, v);
    update(2 * x + 1, mid + 1, r, s, e, op, v);
}
int read(int x, int l, int r, int p){
    if(l != r){
        spread(x);
    }
    if(l == r){
        return tree[x].s;
    }
    int mid = (l + r) >> 1;
    if(p <= mid){
        return read(2 * x, l, mid, p);
    }else{
        return read(2 * x + 1, mid + 1, r, p);
    }
}
int main(){
    freopen("input.txt","r",stdin);
    int q, n, i;
    int op, l, r, v;
    scanf("%d %d",&n,&q);
    for(i=1;i<=4*n;i++){
        tree[i].s = 0;
        tree[i].e = inf;
    }
    while(q--){
        scanf("%d %d %d %d",&op, &l, &r, &v);
        update(1, 0, n - 1, l, r, op, v);
    }
    for(i=0;i<n;i++){
        printf("%d\n",read(1, 0, n - 1, i));
    }
    return 0;
}