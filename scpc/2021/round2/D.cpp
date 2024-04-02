#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 2000005;
const int MAXL = 505;
struct Trie {
    unordered_map<int, Trie*> go;
    Trie *fail;
    LL sum;
    int l;
    Trie(int _l) {
        fail = NULL;
        sum = 0;
        l = _l;
    }

    ~Trie() {
        go.clear();
        fail = NULL;
        sum = 0;
        l = 0;
    }

    void insert(int patten[], int len, int i, int idx) {
        if (i > len) {
            sum += idx;
            return;
        }

        if (go.find(patten[i]) == go.end()) {
            go[patten[i]] = new Trie(l + 1);
        }
        go[patten[i]] -> insert(patten, len, i + 1, idx);
    }

    void init_trie() {
        for (auto it: go) {
            (it.second) -> init_trie();
            delete it.second;
        }
        go.clear();
    }
};
Trie *root;
void init() {
    root -> init_trie();
    root -> sum = 0;
}
queue<Trie*> Q;
void construct_fail() {
    for (auto it: root -> go) {
        int key = it.first;
        Trie* nxt = it.second;
        nxt -> fail = root;
        Q.push(nxt);
    }

    while (Q.size()) {
        Trie *p = Q.front();
        Q.pop();
        for (auto it: p -> go) {
            Trie *q = p -> fail;
            int key = it.first;
            Trie* nxt = it.second;
            while (q != root && (q -> go).find(max(key - (p -> l - q -> l), 0)) == (q -> go).end()) {
                q = q -> fail;
            }
            nxt -> fail = (q -> go)[max(key - (p -> l - q -> l), 0)];
            nxt -> sum += (nxt -> fail) -> sum;
            Q.push(nxt);
        }
    }
}
LL calc(Trie *curr, int text[], int len) {
    LL res = 0;
    for (int i = 0; i < len; i++) {
        res += curr -> sum;
        while (curr != root && (curr -> go).find(max(text[i + 1] - (i - (curr -> l)), 0)) == (curr -> go).end()) {
            curr = curr -> fail;
        }
        curr = (curr -> go)[max(text[i + 1] - (i - (curr -> l)), 0)];
    }
    res += curr -> sum;
    return res;
}
int last[30];
void init_last() {
    for (int i = 0; i < 26; i++) {
        last[i] = 0;
    }
}
void convert_str_to_int(char s[], int len, int res[]) {
    init_last();
    for (int i = 1; i <= len; i++) {
        res[i] = last[s[i] - 'a'];
        last[s[i] -'a'] = i;
    }
}
char in_s[MAXN];
int text[MAXN];
int patten[MAXL];
int main() {
    freopen("input.txt", "r", stdin);
    root = new Trie(0);
    root -> fail = root;
    int TC;
    scanf("%d", &TC);
    int n, k;
    for (int TI = 1; TI <= TC; TI++) {
        printf("Case #%d\n", TI);
        init();
        scanf("%d %d", &n, &k);
        scanf("%s", in_s + 1);
        convert_str_to_int(in_s, n, text);
        for (int idx = 1; idx <= k; idx++) {
            scanf("%s", in_s + 1);
            int len = strlen(in_s + 1);
            convert_str_to_int(in_s, len, patten);
            root -> insert(patten, len, 1, idx);
        }
        construct_fail();
        printf("%lld\n", calc(root, text, n));
    }
    return 0;
}