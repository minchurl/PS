#include<bits/stdc++.h>
using namespace std;
int main() {
    int x = 1500;
    for (int i = 1; i <= 4; i++) {
        int y;
        scanf("%d", &y);
        x -= y;
    }
    printf("%s\n", x >= 0 ? "Yes": "No");
    return 0;
}