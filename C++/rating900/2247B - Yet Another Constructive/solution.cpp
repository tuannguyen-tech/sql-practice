
#include <iostream>
using namespace std;

void solve() {
    int n, k, m;
    cin >> n >> k >> m;

    if (k > m) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;

    int p = 0;

    while (p < n) {
        for (int i = 0; i < k - 1; i++) {
            cout << 1 << " ";
            p++;

            if (p >= n) {
                cout << "\n";
                return;
            }
        }

        cout << m - (k - 1) << " ";
        p++;

        if (p >= n) {
            cout << "\n";
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int testCases;
    cin >> testCases;

    while (testCases--) {
        solve();
    }

    return 0;
}
