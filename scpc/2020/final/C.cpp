#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 50005;
char S[3][MAXN];
int k;
vector<string> lst[4];
string pal_candidate;
bool is_pal() {
    int sz = pal_candidate.size();
    for (int i = 0; i < sz / 2; i++) {
        if (pal_candidate[i] != pal_candidate[sz - i - 1]) {
            return false;
        }
    }
    return true;
}
void construct_lst(int idx) {
    lst[idx].clear();
    int n = strlen(S[idx]);
    for (int s = 0; s < n; s++) {
        pal_candidate.clear();
        for (int e = s; e < n; e++) {
            pal_candidate += S[idx][e];
            if (is_pal()) {
                lst[idx].pb(pal_candidate);
            }
        }
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    int TC;
    scanf("%d", &TC);
    for (int TI = 1; TI <= TC; TI++) {
        printf("Case #%d\n", TI);
        bool is_in_case_1 = true;
        for (int i = 0; i < 3; i++) {
            scanf("%s", S[i]);
            if (strlen(S[i]) > 500) {
                is_in_case_1 = false;
            }
        }
        scanf("%d", &k);
        if (is_in_case_1 == false) {
            printf("-1\n");
            continue;
        }
        for (int i = 0; i < 3; i++) {
            construct_lst(i);
            sort(all(lst[i]));
            lst[i].erase(unique(all(lst[i])), lst[i].end());
        }
        lst[3].clear();
        for (auto x: lst[0]) {
            if (binary_search(all(lst[1]), x) ^ binary_search(all(lst[2]), x)) {
                lst[3].pb(x);
            }
        }
        for (auto x: lst[1]) {
            if (!binary_search(all(lst[0]), x) && binary_search(all(lst[2]), x)) {
                lst[3].pb(x);
            }
        }
        sort(all(lst[3]));
        lst[3].erase(unique(all(lst[3])), lst[3].end());
        if (k > lst[3].size()) {
            printf("-1\n");
        }
        else {
            printf("%s\n", lst[3][k - 1].c_str());
        }
    }
    return 0;
}