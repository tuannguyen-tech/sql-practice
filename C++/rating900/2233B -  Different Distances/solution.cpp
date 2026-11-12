#include<iostream>
using namespace std;

void solve(){
    int n;
    cin>>n;
    if(n%2==0){
        for(int i=1;i<=n;i+=2){
            cout<<i<<" "<<i+1<<" "<<i<<" "<<i+1<<" ";
            cout<<i+1<<" "<<i<<" "<<i<<" "<<i+1<<" "; 
        }
    }
    if (n%2!=0){
        cout<< "1 1 2 1 2 3 1 3 2 2 3 3 "; 
        for (int i=4;i<=n;i+=2){
            cout<<i<<" "<<i+1<<" "<<i<<" "<<i+1<<" ";
            cout<<i+1<<" "<<i<<" "<<i<<" "<<i+1<<" "; 
        }
    }
    cout<<"\n";
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
