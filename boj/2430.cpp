#include<bits/stdc++.h>
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define pb push_back
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pil;
const int MAXN = 35;

struct HashTree {
    int size;
    LL hashValue;
    HashTree() {
        size = 0;
        hashValue = 0;
    }
    void merge(const HashTree &d) {
        hashValue = (hashValue << d.size) + d.hashValue;
        size = size + d.size;
    }
    void lift() {
        hashValue = (hashValue + (1LL << size)) << 1;
        size = size + 2;
    }

    bool operator == (const HashTree &d) const{
        return (size == d.size && hashValue == d.hashValue);
    }
    bool operator < (const HashTree &d) const{
        if (size == d.size) {
            return hashValue < d.hashValue;
        }
        return size < d.size;
    }
};

int tn;
int weight[MAXN];
vector<pair<HashTree, HashTree> > constellation;
vector<int> adj[MAXN];

void init(int n) {
    for (int i = 0; i < n; i++) {
        weight[i] = 0;
        adj[i].clear();
    }
}


void generateWeight(int u, int p) {
    weight[u] = 1;
    for (int v: adj[u]) {
        if (v == p) {
            continue;
        }
        generateWeight(v, u);
        weight[u] += weight[v];
    }
}
void generateWeight(int root) {
    generateWeight(root, -1);
}

pii findCentroid(int u, int p, int root) {
    for (int v: adj[u]) {
        if (v == p) {
            continue;
        }
        if (weight[root] / 2 < weight[v])  {
            return findCentroid(v, u, root);
        }
        else if (weight[root] % 2 == 0 && weight[root] / 2 == weight[v]) {
            return pii(u, v);
        }
    }
    return pii(u, u);
}
pii findCentroid(int root) {
    return findCentroid(root, -1, root);
}

HashTree getHashTree(int u, int p) {
    vector<HashTree> childHashValue;
    for (int v: adj[u]) {
        if (v == p) {
            continue;
        }
        HashTree child = getHashTree(v, u);
        child.lift();
        childHashValue.pb(child);
    }
    sort(all(childHashValue));
    HashTree res;
    for (HashTree childTree: childHashValue) {
        res.merge(childTree);
    }
    return res;
}
HashTree getHashTree(int root) {
    return getHashTree(root, -1);
}

int main() {
    freopen("input.txt","r",stdin);
    scanf("%d", &tn);
    for (int i = 0; i < tn; i++) {
        int n;
        scanf("%d", &n);
        init(n);
        for (int j = 1; j < n; j++) {
            int x, y;
            scanf("%d %d", &x, &y);
            adj[x].pb(y);
            adj[y].pb(x);
        }
        generateWeight(0);
        pii cen = findCentroid(0);
        pair<HashTree, HashTree> hash = pair<HashTree, HashTree>(getHashTree(cen.fi), getHashTree(cen.se));
        if (hash.se < hash.fi) {
            swap(hash.fi, hash.se);
        }
        constellation.pb(hash);
    }
    sort(all(constellation));constellation.erase(unique(all(constellation)), constellation.end());

    printf("%d\n", constellation.size());
    return 0;
}