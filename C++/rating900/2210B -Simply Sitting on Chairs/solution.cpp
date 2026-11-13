#include<iostream>

using namespace std;

void solve() {
   int n;
   cin>>n;
   int ans=0;

   for(int i=1;i<=n;i++){
    int x;
    cin>>x;
    if (x<=i){
        ans++;
    }
   }
   cout<<ans<<"\n";
     
  
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
