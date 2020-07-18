#include<bits/stdc++.h>
#define MAX_N 10005
#define MAX_M 100005
#define MAX_H 55
#define MAX_W 55
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(V) (V).begin(),(V).end()
#define reset(V) (V).clear();(V).resize(0);
#define rev(x) ((x)^1)
#define sq(x) ((x)*(x))
#define abs(x) ((x)>0?(x):(-(x)))
#define fi first
#define se second
#define LL_inf (1LL<<60)
#define full_inf 0x7fffffff
#define half_inf 0x3fffffff
#define inf 0x3fffffff
#define MOD 1000000007LL
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL,LL> pil;
typedef pair<LL,string> pls;
typedef complex<LD> Complex;
typedef long double LD;
struct node{
    int h,w;
};
node num[MAX_H][MAX_W];
int n;
int h, w;
int dfn[2 * MAX_H * MAX_W], dn;
int cmp[2 * MAX_H * MAX_W], cn;
int sat_cmp[2 * MAX_H * MAX_W], sat_cn;
int chk[2 * MAX_H * MAX_W];
char in_s[MAX_H][MAX_W];
vector<int> adj[2 * MAX_H * MAX_W], scc_adj[2 * MAX_H * MAX_W], sat_adj[2 * MAX_H * MAX_W];
stack<int> st;
int make_scc(int u){
    int low = dfn[u] = ++dn;
    st.push(u);
    for(int v:adj[u]){
        if(dfn[v] && !cmp[v])   low = min(low, dfn[v]);
        else if(!dfn[v])    low = min(low, make_scc(v));
    }
    if(dfn[u] == low){
        cn++;
        while(st.size() && dfn[st.top()] >= dfn[u]){
            cmp[st.top()] = cn;
            st.pop();
        }
    }
    return low;
}
void dfs(int u, int z){
    chk[u] += z;
    for(int v:scc_adj[u]){
        sat_adj[2 * v - 1].eb(2 * u - 1);
        dfs(v, z);
    }
}
int make_sat_scc(int u){
    int low = dfn[u] = ++dn;
    st.push(u);
    for(int v:sat_adj[u]){
        if(dfn[v] && !sat_cmp[v])   low = min(low, dfn[v]);
        else if(!dfn[v])    low = min(low, make_sat_scc(v));
    }
    if(dfn[u] == low){
        sat_cn++;
        while(st.size() && dfn[st.top()] >= dfn[u]){
            sat_cmp[st.top()] = sat_cn;
            st.pop();
        }
    }
    return low;
}
int main(){
    freopen("input.txt","r",stdin);
    int i,j,x,y;
    scanf("%d %d",&h,&w);
    for(i=1;i<=h;i++){
        scanf("%s",in_s[i]);
        for(j=w;j>0;j--){
            in_s[i][j] = in_s[i][j-1];
        }
    }
    n = 1;
    for(i=1;i<=h;i++){
        for(j=1;j<=w;j++){
            if(in_s[i][j] == '#'){
                n++;
                continue;
            }
            num[i][j].w = n;
        }
        n++;
    }
    for(j=1;j<=w;j++){
        for(i=1;i<=h;i++){
            if(in_s[i][j] == '#'){
                n++;
                continue;
            }
            num[i][j].h = n;
        }
        n++;
    }

    for(i=1;i<=h;i++){
        for(j=1;j<=w;j++){
            if(in_s[i][j] == '#')   continue;
            if(num[i][j].w != num[i][j-1].w || num[i][j].w != num[i][j+1].w)    adj[num[i][j].w].eb(num[i][j].h);
            if(num[i][j].h != num[i-1][j].h || num[i][j].h != num[i+1][j].h)    adj[num[i][j].h].eb(num[i][j].w);
        }
    }

    for(i=1;i<=n;i++){
        if(dfn[i])  continue;
        make_scc(i);
    }

    for(int u=1;u<=n;u++){
        for(int v:adj[u]){
            if(cmp[u] == cmp[v])    continue;
            scc_adj[cmp[u]].eb(cmp[v]);
        }
    }
    for(i=1;i<=cn;i++){
        sort(all(scc_adj[i]));scc_adj[i].erase(unique(all(scc_adj[i])), scc_adj[i].end());
        for(int u:scc_adj[i]){
            for(int v:scc_adj[i]){
                if(u == v)  continue;
                sat_adj[2 * u - 1].eb(2 * v - 2);
            }
        }
    }

    for(i=1;i<=h;i++){
        for(j=1;j<=w;j++){
            if(in_s[i][j] == 'O'){
                dfs(x = cmp[num[i][j].h], 1);
                dfs(y = cmp[num[i][j].w], 2);
            }
            if(in_s[i][j] == '*'){
                sat_adj[2 * cmp[num[i][j].h] - 2].eb(2 * cmp[num[i][j].w] - 1);
                sat_adj[2 * cmp[num[i][j].w] - 2].eb(2 * cmp[num[i][j].h] - 1);
            }
        }
    }
    sat_adj[2 * x - 2].eb(2 * y - 1);
    sat_adj[2 * y - 2].eb(2 * x - 1);
    for(i=1;i<=n;i++)   dfn[i] = 0;
    for(i=1;i<=cn;i++){
        if(chk[i] == 0){
            sat_adj[2 * x - 1].eb(2 * i - 2);
            sat_adj[2 * y - 1].eb(2 * i - 2);
        }
    }
    dn = 0;
    for(i = 0 ; i < 2 * cn ; i++){
        if(dfn[i])  continue;
        make_sat_scc(i);
    }
    for(i = 0 ; i < cn ; i++){
        if(sat_cmp[2 * i] == sat_cmp[2 * i + 1])    break;
    }
    printf("%s\n",i == cn?"YES":"NO");
    return 0;
}
