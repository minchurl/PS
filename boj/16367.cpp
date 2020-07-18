#include<bits/stdc++.h>
#define MAX_N 10005
#define MAX_K 5005
#define eb emplace_back
using namespace std;
struct Predict{
    int idx, c;
}user[MAX_N][3];
int k,n;
int dn,cn;
int cmp[2 * MAX_K],dfn[2 * MAX_K];
vector<int> adj[2 * MAX_K];
stack<int> st;
void add_graph(int x){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i==j)    continue;
            adj[2 * user[x][i].idx - 2 + !user[x][i].c].eb(2 * user[x][j].idx - 2 + user[x][j].c);
        }
    }
}
int make_scc(int u){
    int low;
    low = dfn[u] = ++dn;
    st.push(u);
    for(int v:adj[u]){
        if(dfn[v] && !cmp[v])   low = min(low, dfn[v]);
        else if(!dfn[v])    low = min(low, make_scc(v));
    }
    if(dfn[u] == low){
        cn ++;
        while(st.size() && dfn[st.top()] >= low){
            cmp[st.top()] = cn;
            st.pop();
        }
    }
    return low;
}
int main(){
    freopen("input.txt","r",stdin);
    int i,j;
    char s[5];
    scanf("%d %d",&k,&n);
    for(i=1;i<=n;i++){
        for(j=0;j<3;j++){
            scanf("%d %s",&user[i][j].idx,s);
            user[i][j].c = (s[0] == 'R');
        }
        add_graph(i);
    }
    for(i=0;i<2*k;i++){
        if(!dfn[i])  make_scc(i);
    }
    for(i=0;i<k;i++){
        if(cmp[2 * i] == cmp[2 * i + 1])    return !printf("-1\n");
    }
    for(i=0;i<k;i++){
        printf("%c",(cmp[2 * i] < cmp[2 * i + 1]) ? 'B' : 'R');
    }
    printf("\n");
    return 0;
}