
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    long long n, k;
    cin >> n >> k;

    // Kiem tra dieu kien hop le
    if (k < n || k >= 2 * n) {
        cout << -1 << "\n";
        return;
    }

    // Khoi tao ma tran (n + 1) x (n + 1)
    vector<vector<long long>> matrix(
        n + 1, vector<long long>(n + 1)
    );

    // 1. Dien gia tri vao ma tran
    long long nextValue = n + 1;

    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {

            if (row == col) {
                matrix[row][col] = row;
            }
            else {
                matrix[row][col] = nextValue;
                nextValue++;
            }
        }
    }

    // 2. Hoan doi de dat du so luong minimum
    long long remainingSwaps = k - n;
    int row = 2;

    while (remainingSwaps > 0 && row <= n) {
        swap(matrix[row][1], matrix[row][row]);

        remainingSwaps--;
        row++;
    }

    // 3. In ma tran ket qua
    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {
            cout << matrix[row][col]
                 << (col == n ? "" : " ");
        }
        cout << "\n";
    }
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
