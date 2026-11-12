#include<iostream>
using namespace std;

void solve() {
    string  s;
    cin>>s;
    int ans =0;

    for(int i=0; i<s.size()-1;i++){
        if(s[i]==s[i+1]){
            ans++;
        }
    }
    if (ans<=2){
        cout<<"YES\n";
    }
    else{
        cout<<"NO\n";
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
