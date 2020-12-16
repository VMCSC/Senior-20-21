#include <bits/stdc++.h>
using namespace std;

const int MAXT = 10005;
int arr[MAXT];
bool dpOld[MAXT*MAXT],dpNew[MAXT*MAXT];

int main() {
    //c1p7
    int T;
    cin >> T;
    int tot = 0;
    for (int i = 1; i <= T; i++) {
        cin >> arr[i];
        tot += arr[i];
    }
    dpOld[0] = true;
    //loop through and fill in dp array (kind of like knapsack)
    for (int i = 1; i <= T; i++) {
        for (int j = 0; j <= tot; j++) {
            dpNew[j] = dpOld[j];
            if (j - arr[i] >= 0 && !dpNew[j]) {
                dpNew[j] = dpOld[j-arr[i]];
            }
        }
        //assign dpOld to dpNew
        for (int j = 0; j <= tot; j++) {
            dpOld[j] = dpNew[j];
        }
    }
    int ans = INT_MAX;
    for (int i = tot/2; i >= 0; i--) {
        if (dpNew[i]) {
            ans = abs(tot-2*i);
            break;
        }
    }
    cout << ans << "\n";

}