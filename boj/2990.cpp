#include<bits/stdc++.h>
using namespace std;

const int MAXWORDCNT = 30000;
const int MAXWORDLENGTH = 30;


struct node {
    int val, cnt;
    bool isEndpoint;
    int child[26];

    node () {
        val = cnt = 0;
        isEndpoint = false;

        for (int i = 0; i < 26; i++) {
            child[i] = 0;
        }
    }
}trie[MAXWORDCNT * MAXWORDLENGTH + 5];

int lastIdx;

int calc(int idx, int i, char word[], int val, bool isRecoded) {
    if (isRecoded) {
        trie[idx].cnt++;
    }
    val += trie[idx].cnt;

    if (word[i] == 0) {
        if (isRecoded) {
            trie[idx].val  = val;
            trie[idx].isEndpoint = true;
            return val;
        }
        else {
            return trie[idx].isEndpoint ? trie[idx].val : val;
        }
    }

    int &nxt = trie[idx].child[word[i] - 'a'];
    if (nxt == 0) {
        if (!isRecoded) {
            return val;
        }
        nxt = lastIdx++;
    }

    return calc(nxt, i + 1, word, val, isRecoded);
}

int main() {
    freopen("input.txt", "r", stdin);
    int n, q;
    char word[35];
    lastIdx = 1;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        calc(0, 0, word, 0, true);
    }
    
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%s", word);
        printf("%d\n", calc(0, 0, word, 0, false));
    }
    return 0;
}