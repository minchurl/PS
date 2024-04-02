#include<bits/stdc++.h>

#define pb push_back
#define all(v) (v).begin(), (v).end()

using namespace std;
typedef long long LL;
typedef pair<LL, LL> pll;

const int MAXN = 105;
const int MAXLINELEN = 256;
const int MAXLINENUM = 10005;
const int MAXLETTERNUM = 1000005;
const char endLine[10] = "***END***";

const LL mod[2] = {(LL)1e9 + 3, (LL)1e9 + 7};
const LL base = 127;

char name[MAXN][MAXLINELEN];
vector<int> target[MAXN];
vector<int> patten;
int n;
int sn, tn;
struct node {
    map<char, int> nxt;
    int symbol;
    // if end not exist -> symbol = 0
};

node tree[MAXLETTERNUM]; // root -> 0

LL power[MAXLINENUM][2];
vector<pll> target_hash[MAXN];

int get_symbol(int i, char *in, bool is_registration) {
    if (*in == '\0') {
        if (tree[i].symbol == 0) {
            if (is_registration == false) {
                return 0;
            }
            tree[i].symbol = ++sn;
        }
        return tree[i].symbol;
    }

    if (tree[i].nxt.find(*in) == tree[i].nxt.end()) {
        if (is_registration == false) {
            return 0;
        }
        tree[i].nxt[*in] = ++tn;
    }
    char *nxt_in = in + 1;
    while (*in == ' ' && *nxt_in == ' ') {
        nxt_in++;
    }
    return get_symbol(tree[i].nxt[*in], nxt_in, is_registration);
}

char* strip(char *in) {
    while (*in == ' ') {
        in++;
    }
    char *end = in;
    while (*end != '\0') {
        end++;
    }

    while (end != in && *(end - 1) == ' ') {
        end--;
    }
    *end = '\0';
    return in;
}


int ans_val;
vector<int> ans_list;

bool chk[MAXN];


void adjust_hash(LL val[], LL in_val, LL out_val, LL len) {
    for (int i = 0; i < 2; i++) {
        val[i] = (val[i] * base + in_val - out_val * power[len][i]) % mod[i];
        val[i] = (val[i] + mod[i]) % mod[i];
    }
}

bool is_valid(int len) {
    // init chk
    for (int i = 0; i < n; i++) {
        chk[i] = false;
        target_hash[i].clear();
    }

    if (len == 0) {
        return true;
    }

    int patten_len = patten.size();

    // get target_hash
    for (int i = 0; i < n; i++) {
        int target_len = target[i].size();
        LL hash[2] = {0, 0};
        for (int j = 0; j < target_len; j++) {

            adjust_hash(hash, target[i][j], (j < len) ? 0 : target[i][j - len], len);
            if (j < len - 1) {
                continue;
            }
            target_hash[i].pb(pll(hash[0], hash[1]));
        }
        sort(all(target_hash[i]));
    }

    LL patten_hash[2] = {0, 0};
    for (int i = 0; i < patten_len; i++) {
        adjust_hash(patten_hash, patten[i], (i < len) ? 0 : patten[i - len], len);
        if (i < len - 1) {
            continue;
        }

        for (int j = 0; j < n; j++) {
            if (!chk[j] && binary_search(all(target_hash[j]), pll(patten_hash[0], patten_hash[1]))) {
                chk[j] = true;
            }
        }

    }


    for (int i = 0; i < n; i++) {
        if (chk[i]) {
            return true;
        }
    }
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);

    power[0][0] = power[0][1] = 1;
    for (int i = 1; i < MAXLINENUM; i++) {
        for (int j = 0; j < 2; j++) {
            power[i][j] = (power[i - 1][j] * base) % mod[j];
        }
    }

    char origin_in[MAXLINELEN];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", name[i]);
        while (true) {
            char *in = origin_in;
            cin.getline(in, MAXLINELEN);
            in = strip(in);
            if (*in == '\0') {
                continue;
            }
            if (strcmp(in, endLine) == 0) {
                break;
            }
            target[i].pb(get_symbol(0, in, true));
        }
    }
    while (true) {
        char *in = origin_in;
        cin.getline(in, MAXLINELEN);
        in = strip(in);
        if (*in == '\0') {
            continue;
        }
        if (strcmp(in, endLine) == 0) {
            break;
        }
        patten.pb(get_symbol(0, in, false));
    }

    int l = 0;
    int r = patten.size();

    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (is_valid(mid)) {
            l = mid;
        }
        else {
            r = mid - 1;
        }
    }

    is_valid(l);
    printf("%d ", l);

    for (int i = 0; i < n; i++) {
        if (chk[i]) {
            printf("%s ", name[i]);
        }
    }
    printf("\n");
    return 0;
}