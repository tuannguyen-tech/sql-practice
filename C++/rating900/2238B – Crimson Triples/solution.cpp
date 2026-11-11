#include<iostream>
using namespace std;

void solve(){
    long long n;
    cin>>n;
    long long ans =0;

    for (int b=1; b<=n;b++){
        ans+ = (n/b)*(n/b)
    }

    cout<<ans<<endl;
    
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

