#include<bits/stdc++.h>
#define eb emplace_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef pair<int, int> pii;
// second 1 -> 시작, 2 -> 종료
int n, h;
vector<pii> calc_log;
vector<int> rest_time;
vector<int> sum_rest_time;
int main() {
    scanf("%d %d", &n, &h);
    for (int i = 1; i <= n; i++) {
        int st, ed;
        scanf("%d %d", &st, &ed);
        calc_log.eb(st, 1);
        calc_log.eb(ed, 2);
    }

    sort(all(calc_log));
    int curr_job = 0;
    int last_job_done = 0;
    rest_time.eb(0);
    for (pii event: calc_log) {
        if (event.second == 1) {
            // execute new job
            curr_job++;
            if (curr_job == 1) {
                rest_time.eb(event.first - last_job_done - 1);
            }
        } else {
            // terminate job
            curr_job--;
            if (curr_job == 0) {
                last_job_done = event.first;
            }
        }
    }
    rest_time.eb(h - last_job_done);
    sort(all(rest_time));
    int sum = 0;
    for (int t: rest_time) {
        sum += t;
        sum_rest_time.eb(sum);
    }
    int q;
    scanf("%d", &q);
    int m = rest_time.size();
    while (q--) {
        int t;
        scanf("%d", &t);
        int i = lower_bound(all(rest_time), t) - rest_time.begin();
        printf("%d\n", sum - sum_rest_time[i - 1] - (m - i) * (t - 1));
    }
    return 0;
}