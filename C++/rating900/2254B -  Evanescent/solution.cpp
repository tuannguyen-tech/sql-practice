#include<iostream>
using namespace std;
void solve() {
    int n;
    cin>>n;
    string s;
    cin>>s;

    int compressedLength = 1;
    for(int i=1;i<n;i++) {
        if (s[i] !=s[i-1]){
            compressedLength++;
        }
    }
    int maxReduction = 0;
    for(int i=1; i<=n-2;i++){
        if (s[i]!=s[i+1] && s[i-1] ==s[i+1]){
            maxReduction=2;
            break;
        }
        if (s[i]!=s[i+1] && s[i-1] !=s[i]) {
            maxReduction=1;
        }
    }

    cout<<compressedLength-maxReduction<<endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int testCases;
    cin>>testCases;
    while(testCases--) {
        solve();
    }

    return 0;
}