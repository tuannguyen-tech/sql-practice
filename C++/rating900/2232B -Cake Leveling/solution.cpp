
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

void solve() {
    int n;
    cin >> n;

    long long sum = 0;
    long long ans = LLONG_MAX;

    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;

        sum += x;

        long long avg = sum / i;

        ans = min(avg, ans);

        cout << ans << " ";
    }

    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;

    while (testCases--) {
        solve();
    }

    return 0;
}
