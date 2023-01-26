#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2505;
const int MAXM = 55;
const int MAXK = 55;
const int CODONLENGTH = 3;
const int AMINOLENGTH = 20;
const int MAXAMINO = 837;
struct Amino {
    char codon[CODONLENGTH];
    char amino[AMINOLENGTH];
    int idx;
};
int m, k;
int DNALength;
int generateAmino[MAXK][MAXN]; // generateAmino[idx][st] = ed -> we can generate amino acid idx by using DNA[st, ed]
int dp[MAXAMINO][MAXK][MAXN];
char DNA[MAXN];
Amino aminoList[MAXM];
void constructAminoList() {
    sort(aminoList + 1, aminoList + m + 1, [&](const Amino x, const Amino y) {
        return strcmp(x.amino, y.amino) < 0;
    });

    aminoList[1].idx = ++k;
    for (int i = 2; i <= m; i++) {
        if (strcmp(aminoList[i - 1].amino, aminoList[i].amino) != 0) {
            ++k;
        }
        aminoList[i].idx = k;
    }
}
void constructGenerateAmino() {
    for (int i = 1; i <= m; i++) {
        Amino *a = &aminoList[i];
        for (int st = 1; st <= DNALength; st++) {
            int l = 0;
            int ed;
            for (ed = st; ed <= DNALength && l < 3; ed++) {
                if (DNA[ed] == a -> codon[l]) {
                    l++;
                }
            }
            if (l != 3) {
                generateAmino[a -> idx][st] = 0;
            }
            else {
                generateAmino[a -> idx][st] = ed;
            }
        }
    }
}
void constructDP() {
    // dp[# of amino][latest animo idx][latest DNA idx]
    int res = 0;
    dp[0][1][0] = 1;
    for (int i = 0; i < DNALength / 3; i++) {
        for (int preIdx = 1; preIdx <= k; preIdx++) {
            for (int j = 0; j < DNALength; j++) {
                if (dp[i][preIdx][j] == 0) {
                    continue;
                }
                for (int currIdx = 1; currIdx <= k; currIdx++) {
                    if (generateAmino[currIdx][j + 1] == 0) {
                        continue;
                    }
                    dp[i + 1][currIdx][generateAmino[currIdx][j + 1]] += dp[i][preIdx][j];
                    res += dp[i][preIdx][j];
                }
            }
        }
    }
    printf("%d\n", res);
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%s", DNA + 1);
    DNALength = strlen(DNA + 1);

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%s %s", aminoList[i].codon, aminoList[i].amino);
    }

    constructAminoList();
    constructGenerateAmino();
    constructDP();
    return 0;
}
