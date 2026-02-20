#include<bits/stdc++.h>
#define abs(x) ((x) > 0 ? (x) : (-(x)))
using namespace std;
typedef long long LL;

const int MAXN = 200005;
struct Building {
    int loc;
    bool is_blue;
    int matching_idx;
};
Building house[MAXN], store[MAXN];
int n, r;
LL total_dst;

LL get_distance_of_matching(int house_idx) {
    int matching_store_idx = house[house_idx].matching_idx;
    return abs(house[house_idx].loc - store[matching_store_idx].loc);
}

void construct_matching(int house_idx, int store_idx) {
    house[house_idx].matching_idx = store_idx;
    store[store_idx].matching_idx = house_idx;
    // printf("construct matching : house %c %d : store %c %d: %lld\n", house[house_idx].is_blue ? 'B' : 'R', house[house_idx].loc, store[store_idx].is_blue ? 'B' : 'R', store[store_idx].loc, get_distance_of_matching(house_idx));
    total_dst += get_distance_of_matching(house_idx);
}

void swap_matching(int house_x_idx, int house_y_idx) {
    total_dst -= get_distance_of_matching(house_x_idx) + get_distance_of_matching(house_y_idx);

    int store_x_idx = house[house_x_idx].matching_idx;
    int store_y_idx = house[house_y_idx].matching_idx;

    construct_matching(house_x_idx, store_y_idx);
    construct_matching(house_y_idx, store_x_idx);

}

int main() {
    int T;
    scanf("%d", &T);
    for (int TC = 1; TC <= T; TC++) {
        printf("Case #%d\n", TC);
        scanf("%d %d", &n, &r);

        // blue house
        for (int i = 1; i <= n - r; i++) {
            int loc;
            scanf("%d", &loc);
            house[i].loc = loc;
            house[i].is_blue = true;
        }
        // red house
        for (int i = n - r + 1; i <= n; i++) {
            int loc;
            scanf("%d", &loc);
            house[i].loc = loc;
            house[i].is_blue = false;
        }

        // blue store
        for (int i = 1; i <= n - r - 1; i++) {
            int loc;
            scanf("%d", &loc);
            store[i].loc = loc;
            store[i].is_blue = true;
        }
        // red store
        for (int i = n - r; i <= n; i++) {
            int loc;
            scanf("%d", &loc);
            store[i].loc = loc;
            store[i].is_blue = false;
        }

        sort(house + 1, house + n + 1, [&](const Building x, const Building y) {
            if (x.loc == y.loc) {
                if (x.matching_idx == y.matching_idx) {
                    return x.is_blue < y.is_blue;
                }
                return x.matching_idx < y.matching_idx;
            }
            return x.loc < y.loc;
        });

        sort(store + 1, store + n + 1, [&](const Building x, const Building y) {
            if (x.loc == y.loc) {
                if (x.matching_idx == y.matching_idx) {
                    return x.is_blue < y.is_blue;
                }
                return x.matching_idx < y.matching_idx;
            }
            return x.loc < y.loc;
        });
        // set betrayer as the first blue house
        int betrayer_blue_house_idx;
        for (int i = 1; i <= n; i++) {
            if (house[i].is_blue) {
                betrayer_blue_house_idx = i;
                break;
            }
        }
        

        // get total distance if the first blue house is betrayer
        // construct matching idx
        total_dst = 0;
        // red
        int store_idx = 1;
        for (int house_idx = 1; house_idx <= n; house_idx++) {
            if (house[house_idx].is_blue && house_idx != betrayer_blue_house_idx) {
                continue;
            }
            while (store_idx <= n && store[store_idx].is_blue) {
                store_idx++;
            }
            construct_matching(house_idx, store_idx);
            store_idx++;
        }
        // blue
        store_idx = 1;
        for (int house_idx = 1; house_idx <= n; house_idx++) {
            if (!house[house_idx].is_blue || house_idx == betrayer_blue_house_idx) {
                continue;
            }
            while (store_idx <= n && !store[store_idx].is_blue) {
                store_idx++;
            }
            construct_matching(house_idx, store_idx);
            store_idx++;
        }

        // printf("betrayer_bule_house_idx : %d : %d :: %lld\n", betrayer_blue_house_idx, house[betrayer_blue_house_idx].loc, total_dst);

        LL res = total_dst;

        // move betrayer one by one
        for (int i = 1; i < n - r; i++) {
            int j = betrayer_blue_house_idx + 1;
            while (j <= n && !house[j].is_blue) {
                swap_matching(betrayer_blue_house_idx, j);
                j++;
            }
            swap_matching(betrayer_blue_house_idx, j);
            res = min(res, total_dst);
            betrayer_blue_house_idx = j;
            // printf("betrayer_bule_house_idx : %d : %d :: %lld\n", betrayer_blue_house_idx, house[j].loc, total_dst);
        }

        printf("%lld\n", res);
        fflush(stdout);
    }
    return 0;
}