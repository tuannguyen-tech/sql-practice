#include <iostream>
#include<vector>
using namespace std;
void solve() {
    int n;
    cin >> n;

    if (n == 1) {
        cout << 1 << '\n';
        return;
    }

    if (n == 2) {
        cout << -1 << '\n';
        return;
    }

    vector<long long> a = {1, 2, 3};

    long long sum = 6;

    while (a.size() < n) {
        a.push_back(sum);
        sum *= 2;
    }

    for (long long x : a) {
        cout << x << " ";
    }

    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
